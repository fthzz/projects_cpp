#include <iostream>
#include "circle.hpp"

#define PI 3.14159265358979323846

int Circle::circle_count=0;

Circle::Circle(double a, double b, double r): center(a, b), r(r){
    perimeter = 0;
    area = 0;
    circle_count++;
}

Circle::~Circle(){
    circle_count--;
}

double Circle::Get_r(void){
    return r;
}

Point Circle::Get_center(void){
    return center;
}

void Circle::Show_r(void){
    std::cout<<"圆的半径："<<r<<std::endl;
}

void Circle::Show_center(void){
    double temp_x=center.Get_x();
    double temp_y=center.Get_y();
    std::cout<<"圆心的坐标：("<<temp_x<<","<<temp_y<<")"<<std::endl;
}

int Circle::Get_circle_count(void){
    std::cout<<"圆的个数："<<circle_count<<std::endl;
    return circle_count;
}

double Circle::Get_perimeter(void){
    perimeter=2*r*PI;
    return perimeter;
}

double Circle::Get_area(void){
    area=r*r*PI;
    return area;
}

void Circle::Show_property(void){
    std::cout<<"圆的周长："<<Get_perimeter()<<std::endl;
    std::cout<<"圆的面积："<<Get_area()<<std::endl;
}

void Circle::Move(double t_x1, double t_y1) {
    center.Move(t_x1, t_y1);
}

void Circle::Zoom(double k) {
    r *= k;
}

void Circle::Rorate(double angle) {
    center.Rorate(angle);
}
void Circle::Mirror_x(void) {
    center.Mirror_x();
}
void Circle::Mirror_y(void) {
    center.Mirror_y();
}

//测试代码
// int main(){
    //Circle c1(3, 3, 1);
    //std::cout << "初始状态：" << std::endl;
    //c1.Show_property();
    //c1.Show_center();
    //c1.Show_r();
    //c1.Get_circle_count();

    //std::cout << "移动后：" << std::endl;
    //c1.Move(1, 1);
    //c1.Show_center();

    //std::cout << "缩放后：" << std::endl;
    //c1.Zoom(0.5);
    //c1.Show_r();

    //std::cout << "旋转后：" << std::endl;
    //c1.Rorate(45);
    //c1.Show_center();

    //std::cout << "镜像后：" << std::endl;
    //c1.Mirror_x();
    //c1.Show_center();
// }