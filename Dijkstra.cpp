#include <iostream>
#include <string>
#include <cstring>
#define MAX 10000
#define vexnum_MAX 100
using namespace std;

typedef struct{
    int vex_num, arc_num; //vex点的数量，arc边的数量
    int arcs[vexnum_MAX][vexnum_MAX];
    char vexs[vexnum_MAX];
} AMGraph; //邻接矩阵 

//查找指定节点在数组中的下标
int find_index(char* list, char goal){
    for (int i = 0; i < vexnum_MAX;i++){
        if(goal==list[i]){
            // std::cout << goal << "的序号是" << i << std::endl;
            return i;
        }
    }
}

//初始化
void Init_AMGraph(AMGraph &G){
    cin >> G.vex_num >> G.arc_num;

    for (int i = 0; i < G.vex_num;i++){
        std::cin >> G.vexs[i];
    }
    for (int i = 0; i < G.vex_num; i++)
    {
        for (int j = 0; j < G.vex_num; j++)
        {
            G.arcs[i][j] = MAX;
        }
    }
    for (int k = 0; k < G.arc_num;k++){
        char v1, v2;
        int weight=0;
        int i = 0, j = 0;
        cin >> v1 >> v2 >> weight;
        i = find_index(G.vexs, v1);
        j = find_index(G.vexs, v2);
        G.arcs[i][j] = weight;
    }

    //打印
    // for (int i = 0; i < G.vex_num;i++){
    //     for (int j = 0; j < G.vex_num;j++){
    //         std::cout << G.arcs[i][j]<<"  ";
    //     }
    //     std::cout << std::endl;
    // }
}

//打印最短路径
void show_short_path(AMGraph &G, char *path, char goal, char v0)
{
    char list[vexnum_MAX] = {goal};
    char temp;
    int count = 0;
    if (goal == v0)
        std::cout << 0;
    for (int i = 1; i < vexnum_MAX; i++)
    {
        if (goal != v0)
        {
            list[i] = path[find_index(G.vexs, goal)];
            goal = list[i];
            count++;
        }
        else
        {
            break;
        }
    }

    while (count >= 0)
    {
        std::cout << list[count]<<' ';
        count--;
    }
    std::cout <<std::endl;
}

void Dijikstra(AMGraph &G, char v0,char vk){
    int n = 0;
    n = G.vex_num;
    
    //记录起点到vi是否已经确定最短路径
    bool S[n];
    //记录起点到终点vi最短路径上的直接前驱节点
    char path[n];
    //记录起点到终点vi最短路径的权重
    int D[n];
    //初始化
    for (int i = 0; i < n;i++){
        S[i] = false;
        D[i] = G.arcs[find_index(G.vexs, v0)][i];
        if(D[i]<MAX){
            path[i] = v0;
        }
        else{
            path[i] ='e';
        }
    }
    S[find_index(G.vexs, v0)] = true;
    D[find_index(G.vexs, v0)] = 0;

    for (int i = 1; i < n;i++){//遍历除了起始点外所有未遍历的点，因为只剩下n-1个点是false了
        int min = MAX;
        char v;
        
        //D记录起点到终点vi最短路径的权重
        for (int j = 0; j < n; j++)
        {
            //找到所有相连的节点中代价最短的一个节点
            if(!S[j] && D[j]<min){
                v = G.vexs[j];
                min = D[j];
            }
        }
        S[find_index(G.vexs, v)] = true; 
        

        for (int j = 0; j < n; j++)
        {
            // D[find_index(G.vexs, v)] + G.arcs[find_index(G.vexs, v)][j]  从起点开始，经过加入刚到S的这一点，到达goal_point的距离
            // D[j] 直接从起点到goal_point的距离
            //遍历所有点，判断这两个数值哪个更小
            if (!S[j] && (D[find_index(G.vexs, v)] + G.arcs[find_index(G.vexs, v)][j] < D[j]))
            {//更新
                D[j] = D[find_index(G.vexs, v)] + G.arcs[find_index(G.vexs, v)][j];
                path[j] = v;
            }
        }
    }

    
    std::cout << D[find_index(G.vexs, vk)] <<  std::endl; //打印最短路径的距离
    show_short_path(G, path, vk, v0); //打印最短路径
}


int  main(){
    AMGraph G;
    Init_AMGraph(G);

    char v0, vk;
    std::cin >> v0 >> vk;
    Dijikstra(G, v0, vk);

    return 0;
}