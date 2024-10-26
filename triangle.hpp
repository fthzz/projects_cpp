#pragma once
#include "point.hpp"
#include "line.hpp"

class Triangle
{
private:
    Point tri_points[3];
    Line tri_lines[3];
    double perimeter;
    double area;
    static int triangle_count;
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    ~Triangle();

    Point* Get_points(void);
    void Show_points(void);
    int Get_triangle_count(void);
    double Get_perimeter(void); //周长
    double Get_area(void);
    void Show_property(void);

    void Move(double t_x, double t_y);   //以（0，0）为原点移动,输入值表示移动的距离
    void Zoom(double k); //k为缩放系数,以重心为缩放中心
    void Rorate(double angle); //绕原点旋转任意角度
    void Mirror_x(void);  //关于x轴镜像
    void Mirror_y(void);
};
