#include <vector>

#include "dstar.h"
//#include "matplotlibcpp/*.h"

//namespace plt = matplotlibcpp;

int main() {
    std::pair<int, int> start_point(5, 5);
    std::pair<int, int> end_point(45, 45);
    mymap::MyMap map(51, 51);
    Dstar dstar(map, start_point, end_point);

    std::vector<int> unfree_x;
    std::vector<int> unfree_y;
    std::vector<int> path_x;
    std::vector<int> path_y;

    dstar.insert_state(end_point, 0);
    while (true) {
        dstar.process_state();
        if (dstar.t_[start_point] == "CLOSED") {
            break;
        }
    }
    dstar.make_path();
    //完成第一次遍历


    //plt::figure();
    for (int i = 20; i >= 0; i--) {
        // 所要改变的点的位置
        int x = 25;
        int y = 20 + i;
        // 修改其在地图上的状态
        dstar.map_.set_point_state(x, y, 1);
        std::pair<int, int> temp = start_point;
        while (temp != end_point) {
            //判断新出现的障碍位置，如果没有障碍就continue。是障碍则进入if
            if (dstar.is_collision(temp, dstar.parent_[temp])) {
                dstar.modify(temp);
                continue;
            }
            temp = dstar.parent_[temp];
        }
        //---------------一下为绘图相关---------
    //    dstar.make_path();
    //    unfree_x.clear();
    //    unfree_y.clear();
    //    for (int i = 0; i < dstar.map_.map_xlength(); ++i) {
    //        for (int j = 0; j < dstar.map_.map_ylength(); ++j) {
    //            if (dstar.map_.GetMapPointState(i, j) == 1) {
    //                unfree_x.push_back(i);
    //                unfree_y.push_back(j);
    //            }
    //        }
    //    }
    //    path_x.clear();
    //    path_y.clear();
    //    for (auto p : dstar.path_) {
    //        path_x.push_back(p.first);
    //        path_y.push_back(p.second);
    //    }
    //    plt::clf();
    //    plt::plot(unfree_x, unfree_y, "ko");
    //    plt::plot(path_x, path_y, "ro");
    //    plt::pause(0.1);
    //}
    //plt::show();
}

