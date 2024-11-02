#pragma once
#include <vector>

using std::vector;
namespace mymap {
	class MyMap {
	private:
		vector<vector<int>> map_;   // 地图矩阵
		int map_xlength_; // 地图列数，长
		int map_ylength_; // 地图行数，宽
		int unfree = 1;   // 地图点状态
		int free = 0;
	public:
		// 构造函数
		MyMap() {};
		MyMap(const int map_xlength, const int map_ylength);
		
		// 设置平行与X轴的一排障碍物，[x_begin, x_end]
		void SetObsLineX(const int x_begin, const int x_end, const int y);
		// 设置平行与Y轴的一排障碍物，[y_begin, y_end]
		void SetObsLineY(const int y_begin, const int y_end, const int x);
		
		// 获取(x, y)处的地图状态，1为有障碍物，0为无障碍物
		bool GetMapPointState(const int x, const int y) const;
		 
		// 获取成员变量接口
		void set_point_state(const int x, const int y, const int state);
		
		//获取地图信息
		vector<vector<int>> map() const { return map_; };
		int map_xlength() const { return map_xlength_; };
		int map_ylength() const { return map_ylength_; };
		// 获取(x, y)处的地图状态，1为有障碍物，0为无障碍物
		bool GetMapPointState(const int x, const int y) const;
	};
}  // namespace mymap



