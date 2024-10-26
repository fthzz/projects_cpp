#include <iostream>
#include <cmath>
#include "point.hpp"

#define PI  3.14159265358979323846

int Point::point_count=0;  //这里不初始化，也是默认为0。且不可多处定义

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
    point_count++;
};

Point::~Point(){
    point_count--;
}

int Point::Get_point_count(void){
    std::cout<<"点的个数："<<point_count<<std::endl;
    return point_count;
}

double Point::Get_x(void){
    return x;
}

double Point::Get_y(void){
    return y;
}

void Point::Show_XY(void){
    std::cout<<"点的坐标：("<<x<<","<<y<<")"<<std::endl;
}

void Point::Move(double t_x, double t_y) {
    x += t_x;
    y += t_y;
}

void Point::Change(double t_x, double t_y) {
    x = t_x;
    y = t_y;
}

void Point::Rorate(double angle) {
    double tempx = x;
    x = x * cos(angle * PI / 180.0) - y * sin(angle * PI / 180.0);
    y = y * cos(angle * PI / 180.0) + tempx * sin(angle * PI / 180.0);
}

void Point::Mirror_x(void) {
    y = -y;
}

void Point::Mirror_y(void) {
    x = -x;
}

//测试代码
//int main(){
//    点
//    Point p1(1, 1);*/
//    Point p2(2, 2);
//    p2.Show_XY();
//    p1.Get_point_count();
//
//    p2.Move(2, 3);
//    p2.Show_XY();
//
//    p1.Rorate(45);
//    p1.Show_XY();
//
//    p1.Mirror_x();
//    p1.Show_XY();
//
//    p1.Mirror_y();
//    p1.Show_XY();
//}