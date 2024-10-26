#pragma once
#include "point.hpp"

class Line{
private:
    Point start,end;
    static int line_count;
    double length;
public:
    Line(double s_x, double s_y, double e_x, double e_y);
    ~Line();

    Point Get_start(void);
    Point Get_end(void);
    void Show_start(void);
    void Show_end(void);
    int Get_line_count(void);
    double Get_length(void); 
    void Show_property(void);

    void Move(double t_x1, double t_y1);   //以（0，0）为原点移动,输入值表示移动的距离
    void Zoom(double k); //以中点为中心缩放，k为缩放系数
    void Rorate(double angle); //绕原点旋转任意角度
    void Mirror_x(void);  //关于x轴镜像
    void Mirror_y(void);
};