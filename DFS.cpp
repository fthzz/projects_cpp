#include <iostream>
#include <vector>
#include "map.h"

int point_num = 4, line_num = 4;
std::vector<bool> visited(point_num, false);  //记录是否被访问过，被访问过值为true

//深度优先遍历图
void DFS(Map& map, int start) {
	visited[start] = true;

	std::cout << start << std::endl;

	for (int i = 0; i < map.Get_point_num(); ++i) {
		if (!visited[i] && map.Get_Adjacency_matrix(start, i)) {//如果没被访问过，且两点之间有连线
			DFS(map, i);
		}
	}
}

//int main() {
//	Map m1(point_num, line_num); 
//	m1.Adjacency_matrix_Init();
//	DFS(m1, 0);
//	return 0;
//}