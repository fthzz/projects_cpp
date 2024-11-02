#pragma once

#include <map>
#include <string>
#include <vector>

#include "mymap.h"

class Dstar {
public:
	mymap::MyMap map_;
	std::map<std::pair<int, int>, std::string> t_;                // 地图上每个点的状态
	std::map<std::pair<int, int>, double> k_;                     // 地图每个点的k值
	std::map<std::pair<int, int>, double> h_;                     // 地图每个点的h值
	std::map<std::pair<int, int>, std::pair<int, int>> parent_;   // 每个点的父节点
	std::map<std::pair<int, int>, double> open_;                  // 待访问集合，与对应的h
	
	std::pair<int, int> start_point_;                //搜索起始点
	std::pair<int, int> end_point_;                  //搜索终点
	
	std::vector<std::pair<int, int>> path_;          //搜索路径
	std::pair<int, int> end_point_parent_;           //终点的父节点设置为(-1, -1)


	// 构造函数
	Dstar(mymap::MyMap&, std::pair<int, int>&, std::pair<int, int>&);

	
	// D*的重要过程，compute optimal path costs to the goal
	double process_state();
	// 获取opne中最小状态点以及对应的k,放在一起避免找两遍
	std::pair<std::pair<int, int>, double> min_state() const;
	// 获取最小的k值
	double get_k_min() const;
	// 添加状态点到open中
	void insert_state(std::pair<int, int>&, double);
	// 从open中删除状态点
	void delete_state(std::pair<int, int>&);
	// 改变状态点信息，用来表现动态障碍物
	void modify(std::pair<int, int>&);
	void modify_cost(std::pair<int, int>&);
	// 获取周围点
	std::vector<std::pair<int, int>> get_neigbors(std::pair<int, int>&) const;
	// 计算两点之间的代价
	double cost(std::pair<int, int>&, std::pair<int, int>&) const;
	// 两点之间是否可通行
	bool is_collision(std::pair<int, int>&, std::pair<int, int>&) const;
	// 回溯以获取路径点集
	void make_path();

};



