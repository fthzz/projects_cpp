#pragma once
#include "point.hpp"

class Circle{
private:
    double r;
    Point center;
    static int circle_count;
    double perimeter;
    double area;
public:
    Circle(double a, double b, double r);
    ~Circle();

    double Get_r(void);
    Point Get_center(void);
    void Show_r(void);
    void Show_center(void);
    int Get_circle_count(void);
    double Get_perimeter(void); //周长
    double Get_area(void);
    void Show_property(void);

    void Move(double t_x1, double t_y1);   //以（0，0）为原点移动,输入值表示移动的距离
    void Zoom(double k); //k为缩放系数
    void Rorate(double angle); //绕原点旋转任意角度
    void Mirror_x(void);  //关于x轴镜像
    void Mirror_y(void);
};