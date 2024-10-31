#pragma once
#include<iostream>
#include<vector>

class Map
{
private:
	int Point_num;
	int Line_num;
	std::vector<std::vector<int>> Adjacency_matrix;  //邻接矩阵
public:
	Map(int num1, int num2) : Point_num(num1), Line_num(num2), Adjacency_matrix(num1, std::vector<int>(num1, 0)) {}

	int Get_point_num(void) const;
	int Get_Line_num(void) const;
	int Get_Adjacency_matrix(int i, int j) const;
	void Adjacency_matrix_Init(); //这里是无向图初始化
	void add_Edge(int point1, int point2);
};

