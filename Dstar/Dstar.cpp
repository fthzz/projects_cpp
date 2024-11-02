#include "Dstar.h"

#include <climits>
#include <cmath>
Dstar::Dstar(mymap::MyMap& map, std::pair<int, int>& start_point, std::pair<int, int>& end_point)
    : map_(map) 
{
    // 遍历地图上所有点，设置初始状态
    for (int x = 0; x < map_.map_xlength(); x++) {
        for (int y = 0; y < map_.map_ylength(); y++) {
            std::pair<int, int> point = std::make_pair(x, y);
            t_[point] = "NEW";
            k_[point] = 0.0;
            h_[point] = 100000.0;
            //不可通行的代价设为一个大值，初始设置为最大值没有关系，因为是NEW状态，第一次遍历会计算h
        }
    }
    parent_.clear();
    path_.clear();
    open_.clear();
    start_point_ = start_point;
    end_point_ = end_point;
    h_[end_point_] = 0.0;
    parent_[end_point] = end_point_parent_;
}


double Dstar::process_state() {
    // open为空则返回-1
    if (open_.empty()) return -1;
    // 获取最小状态点以及对应的k
    std::pair<std::pair<int, int>, double> state_and_kold = this->min_state();
    // 提取信息
    std::pair<int, int> current_point = state_and_kold.first;
    double kold = state_and_kold.second;
    // 从列表中删除该点，做相应的标记
    this->delete_state(current_point);
    // 获取周围点
    std::vector<std::pair<int, int>> neighbors =
        this->get_neigbors(current_point);

    // -----------------------主要条件过程--------------------------------------
    // rasie状态，该状态表明，由于修改了状态点的可通行状态，即：h（不可通行h很大），
    // 导致该点曾经的优代价k_old已经不在等于h（曾经最优k_old=h），而是k_old小于h
    // 这种点不仅仅是，直接修改的点(faster)，还包括faster扩张后的点，
    // 这些点由于曾经指向faster,导致其h值在faster扩张过程中被变得很大很大。
    // 对于这样的raise点，首先希望他能够从周围点中获取更短的代价路径，
    // 一旦有这样的点，就指向他。然而，一般不存在，因为，曾经的路线本来就是最优的，周围点的代价都是大于k_old的
    // 当然，由于扩展的进行，状态改的越来越多，说不定就有这样的情况发生
    // 以上解释仅供参考
    
    
    
    // 第一步：遍历邻居，看是否有直接满足条件的最优点
    // 需满足的条件：h_[neighbor] <= kold
    //              h_[current_point] >h_[neighbor] + this->cost(neighbor, current_point)
    if (kold < h_[current_point]) {
        for (auto neighbor : neighbors) {
            if (h_[neighbor] <= kold and
                h_[current_point] > h_[neighbor] + this->cost(neighbor, current_point)) 
            {//如果有，当前点指向它
                parent_[current_point] = neighbor;
                h_[current_point] = h_[neighbor] + this->cost(neighbor, current_point);
            }
        }
    }

    //第二步：处理raise和lower
    // k_old = h表示lower，当前状态点已经是最优路径了。既然已经是最优路径的了，那么周围点就可以直接连上去
    if (kold == h_[current_point]) {
        for (auto neighbor : neighbors) {
            if (/* 1.子节点是NEW，直接在父节点的基础上扩展，这对应初始搜索情况(即第一次遍历一直是在执行这个，直到第一遍全部完成)
                ，跟动态添加障碍物没关系*/
                t_[neighbor] == "NEW" or
                /*2.我们可以这样理解：正常情况下，h_[neighbor] == h_[current_point] + this->cost(neighbor, current_point)，
                * 但此时不相等，说明h_[current_point]因为环境发生变化了，所以current_point的子节点也要重新放入open进行更新
                */
                (parent_[neighbor] == current_point and
                 h_[neighbor] != h_[current_point] + this->cost(neighbor, current_point)) or
                // 3.环境变化后，代价h有更小的情况，所以要重新更新
                (parent_[neighbor] != current_point and
                 h_[neighbor] > h_[current_point] + this->cost(neighbor, current_point))
               ) 
            {
                parent_[neighbor] = current_point;
                this->insert_state(neighbor, h_[current_point] + this->cost(neighbor, current_point));
            }
        }
    }
    else {//不相等
        // 注意这个else分支包含k_old > h，k_old < h;
        for (auto neighbor : neighbors) {
            if (t_[neighbor] == "NEW" or
                (parent_[neighbor] == current_point and
                 h_[neighbor] != h_[current_point] + this->cost(neighbor, current_point) )
               ) 
            {
                // 1.子节点是新的节点，这没啥说的
                // 2.周围点与当前点是父子节点关系，那么不管怎么样子节点要继承父节点带来的变化影响
                parent_[neighbor] = current_point;
                this->insert_state(neighbor, h_[current_point] + this->cost(neighbor, current_point));
            }
            else {
                // 以下针对的是曾经不是子节点的周围点，这些点不会受到“修改”的影响，是重新找路径的重要方向
                //这些点在路径中，因为父节点不是raise点，所以不受影响，但它们是可以产生新的路径的点
                if (parent_[neighbor] != current_point and
                    h_[neighbor] > h_[current_point] + this->cost(neighbor, current_point)) {
                    // 周围点的代价可以通过该点降低
                    // 当前状态点能够用来减少路径代价，但是由于其本身k_old ！= h
                    // 其本身的不能立即传播他的影响 所以将其再次添加到open中
                    this->insert_state(current_point, h_[current_point]);
                }
                else {
                    if (parent_[neighbor] != current_point and
                        h_[current_point] > h_[neighbor] + this->cost(neighbor, current_point) and
                        t_[neighbor] == "CLOSED" and h_[neighbor] > kold) {
                        /*
                        这里的理解方法：t_[neighbor] == "CLOSED"说明它相较于current_point是先被拓展的。由之前的思路可知，我们
                        取出来的点是其中k值最小的，所以原本应该h_[neighbor] <= kold, 同时我们可以知道第一次遍历时h_[neighbor]==h_[neighbor]，
                        所以应该是h_[neighbor] <= kold。但现在是大于，说明它受到环境影响了。
                        与此同时h_[current_point] > h_[neighbor] + this->cost(neighbor, current_point)，这个点可以优化current_point，
                        所以要加入到open中
                        */
                        this->insert_state(neighbor, h_[neighbor]);
                    }
                }
            }
        }
    }
    // 返回最小的k
    return this->get_k_min();
}

//查找open中的k最小的点
std::pair<std::pair<int, int>, double> Dstar::min_state() const {
    // 很大的一个初始值
    double kmin = 1000000.0;
    std::pair<int, int> state;
    // 遍历opne
    for (auto element : open_) {
        if (element.second < kmin) {
            kmin = element.second;
            state = element.first;
        }
    }
    return std::make_pair(state, kmin);
}


//获取最小的k
double Dstar::get_k_min() const {
    double kmin = 100000.0;
    for (auto element : open_) {
        if (element.second < kmin) {
            kmin = element.second;
        }
    }
    return kmin;
}

//插入到open中
void Dstar::insert_state(std::pair<int, int>& current_point, double new_h) {
    // 三种状态调整到open的k处理不同
    if (t_[current_point] == "NEW") {
        k_[current_point] = new_h;
    }
    else if (t_[current_point] == "OPEN") {
        k_[current_point] = std::min(k_[current_point], new_h);
    }
    else if (t_[current_point] == "CLOSED") {
        // 状态点为CLOSED，我觉得意味着该点已经完成过传播过程，本身是最优的，此时k与h相等
        // 我修改下面的h写成k得到的效果一样
        k_[current_point] = std::min(h_[current_point], new_h);
    }
    // 调整h,t信息
    h_[current_point] = new_h;
    t_[current_point] = "OPEN";
    // 添加到open中
    open_[current_point] = k_[current_point];
}

//从open中移除
void Dstar::delete_state(std::pair<int, int>& current_point) {
    if (t_[current_point] == "OPEN") {
        t_[current_point] = "CLOSED";
    }
    open_.erase(current_point);
}

//获取邻居
std::vector<std::pair<int, int>> Dstar::get_neigbors(
    std::pair<int, int>& current_point) const {
    std::vector<std::pair<int, int>> neighbors;
    int mid_x = current_point.first;
    int mid_y = current_point.second;
    // 开始生成周围点
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            std::pair<int, int> next_point(mid_x + i, mid_y + j);
            if (mid_x + i >= 0 and mid_x + i < map_.map_xlength() and
                mid_y + j >= 0 and mid_y + i < map_.map_ylength() and
                !this->is_collision(current_point, next_point)) {
                neighbors.push_back(next_point);
            }
        }
    }
    return neighbors;
}



//环境变化
void Dstar::modify(std::pair<int, int>& current_point) {
    // 修改某处的点的状态
    // 首先修改边界代价
    this->modify_cost(current_point);
    // 修改完以后开始重新找路径
    while (true) {
        double kmin = this->process_state();
        if (kmin >= h_[current_point]) {
            break;
        }
    }
}

//修改当前点的代价，并放入open
void Dstar::modify_cost(std::pair<int, int>& current_point) {
    if (t_[current_point] == "CLOSED") {
        this->insert_state(current_point,
            h_[parent_[current_point]] + this->cost(parent_[current_point], current_point)  );
    }
}


//计算cost
double Dstar::cost(std::pair<int, int>& first_point,
    std::pair<int, int>& second_point) const {
    // 不可通行两点代价为最大值
    if (this->is_collision(first_point, second_point)) {
        return 100000.0;
    }
    return std::sqrt(std::pow(first_point.first - second_point.first, 2) +
        std::pow(first_point.second - second_point.second, 2));
}

//判断
bool Dstar::is_collision(std::pair<int, int>& current,
    std::pair<int, int>& next) const {
    // 两个点本身是障碍物
    if (map_.GetMapPointState(current.first, current.second) ||
        map_.GetMapPointState(next.first, next.second)) {
        return true;
    }
    std::pair<int, int> p1, p2;
    // 当两点在反对角线上时
    if (next.first - current.first == current.second - next.second) {
        // 反对角线上的两个点不能为障碍物
        p1 = std::make_pair(std::min(current.first, next.first),
            std::min(current.second, next.second));
        p2 = std::make_pair(std::max(current.first, next.first),
            std::max(current.second, next.second));
    }
    else {
        // 对角线或其他平行情况
        p1 = std::make_pair(std::min(current.first, next.first),
            std::max(current.second, next.second));
        p2 = std::make_pair(std::max(current.first, next.first),
            std::min(current.second, next.second));
    }
    // 创建的p1,p2不能是障碍物
    if (map_.GetMapPointState(p1.first, p1.second) ||
        map_.GetMapPointState(p2.first, p2.second)) {
        return true;
    }
    return false;
}

void Dstar::make_path() {
    // 先清理原来的path
    path_.clear();
    std::pair<int, int> current_point = start_point_;
    while (current_point != end_point_parent_) {
        path_.push_back(current_point);
        current_point = parent_[current_point];
    }
}
