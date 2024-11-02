#include "mymap.h"

namespace mymap {
    // 构造函数，构建指定长宽的地图大小
    MyMap::MyMap(const int map_xlength, const int map_ylength): 
    map_xlength_(map_xlength), map_ylength_(map_ylength) 
    {
        //对二维vector初始化大小
        map_.resize(map_ylength_);
        for (auto& e : map_) {
            e.resize(map_xlength_);
        }

        //缩放因子
        int x_scale = map_xlength_ / 5;
        int y_scale = map_ylength_ / 5;
        
        //地图边界
        SetObsLineX(0, map_xlength_ - 1, 0);
        SetObsLineX(0, map_xlength_ - 1, map_ylength_ - 1);
        SetObsLineY(0, map_ylength_ - 1, 0);
        SetObsLineY(0, map_ylength_ - 1, map_xlength_ - 1);

        //地图内部边界
        SetObsLineX(x_scale, x_scale * 2, y_scale * 3);
        SetObsLineX(x_scale * 3, x_scale * 4, y_scale * 2);
        SetObsLineX(0, x_scale, y_scale * 2);
        SetObsLineX(x_scale * 4, x_scale * 5, y_scale * 3);
        SetObsLineY(0, y_scale * 3, x_scale * 2);
        SetObsLineY(y_scale * 2, y_scale * 5, x_scale * 3);
    }

    void MyMap::SetObsLineX(const int x_begin, const int x_end, const int y) {
        for (int i = x_begin; i <= x_end; ++i) {
            map_[i][y] = unfree;
        }
    }

    void MyMap::SetObsLineY(const int y_begin, const int y_end, const int x) {
        for (int i = y_begin; i <= y_end; ++i) {
            map_[x][i] = unfree;
        }
    }

    bool MyMap::GetMapPointState(const int x, const int y) const {
        return map_[x][y];
    }

    void MyMap::set_point_state(const int x, const int y, const int state) {
        map_[x][y] = state;
    }

}  // namespace mymap
