#include "map.h"
#include <iostream>
#include<vector>


int Map::Get_point_num(void) const{
	return Point_num;
}

int Map::Get_Line_num(void) const {
	return Line_num;
}

int Map::Get_Adjacency_matrix(int i,int j) const {
	return Adjacency_matrix[i][j];
}

void Map::Adjacency_matrix_Init() {
	for (int i = 0; i < Line_num; ++i) {
		int temp1=0, temp2=0;
		std::cout << "请输入相连的两个点的序号" << std::endl;
		std::cin >> temp1 >> temp2;
		add_Edge(temp1, temp2);
	}
	
}
void Map::add_Edge(int point1, int point2) {
	if (point1 != point2) {
		Adjacency_matrix[point1][point2] = 1;
		Adjacency_matrix[point2][point1] = 1;
	}
}
