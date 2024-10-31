#include <iostream>
#include <vector>
#include <queue>

#include "map.h"

int point_num = 4, line_num = 4;
std::vector<bool> visited(point_num, false);  //记录是否被访问过，被访问过值为true
std::queue<int> q;  //采用队列


//广度优先遍历图
void BFS(Map& map, int start) {
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {//如果队列中有元素，就遍历它的邻接点，直到队列为空，即遍历完成
		start = q.front();
		std::cout << start << std::endl;
		q.pop();
		for (int i = 0; i < map.Get_point_num(); ++i) {
			if (!visited[i] && map.Get_Adjacency_matrix(start, i)) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
}

int main() {
	Map m1(point_num, line_num);
	m1.Adjacency_matrix_Init();
	BFS(m1, 0);
	return 0;
}