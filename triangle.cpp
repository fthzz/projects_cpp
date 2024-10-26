#include <iostream>
#include "math.h"
#include "triangle.hpp"

int Triangle::triangle_count = 0;

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3):
    tri_points{Point(x1, y1), Point(x2, y2), Point(x3, y3)},
    tri_lines{Line(x1, y1, x2, y2), Line(x1, y1, x3, y3), Line(x2, y2, x3, y3)}
{
    perimeter = 0;
    area = 0;
    triangle_count++;
}

Triangle::~Triangle(){
    triangle_count--;
}

Point* Triangle::Get_points(void){
    return tri_points;
}

void Triangle::Show_points(void){
    std::cout<<"三角形的顶点坐标分别是："<<std::endl;
    std::cout<<"("<<tri_points[0].Get_x()<<","<<tri_points[0].Get_y()<<")"<<std::endl;
    std::cout<<"("<<tri_points[1].Get_x()<<","<<tri_points[1].Get_y()<<")"<<std::endl;
    std::cout<<"("<<tri_points[2].Get_x()<<","<<tri_points[2].Get_y()<<")"<<std::endl;
}

int Triangle::Get_triangle_count(void){
    std::cout<<"三角形的个数："<<triangle_count<<std::endl;
    return triangle_count;
}

double Triangle::Get_perimeter(void){
    double l1,l2,l3;
    l1 = tri_lines[0].Get_length();
    l2 = tri_lines[1].Get_length();
    l3 = tri_lines[2].Get_length();
    perimeter = l1+l2+l3;
    return perimeter;
}

double Triangle::Get_area(void){
    double a = tri_lines[0].Get_length();
    double b = tri_lines[1].Get_length();
    double c = tri_lines[2].Get_length();

    double s = (a + b + c) / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

void Triangle::Show_property(void){
    std::cout<<"三角形的周长："<<Get_perimeter()<<std::endl;
    std::cout<<"三角形的面积："<<Get_area()<<std::endl;
}

void Triangle::Move(double t_x, double t_y) {
    tri_points[0].Move(t_x, t_y);
    tri_points[1].Move(t_x, t_y);
    tri_points[2].Move(t_x, t_y);
}

void Triangle::Zoom(double k) {
    Point center((tri_points[0].Get_x() + tri_points[1].Get_x() + tri_points[2].Get_x()) / 3,
        (tri_points[0].Get_y() + tri_points[1].Get_y() + tri_points[2].Get_y()) / 3); // 重心坐标
    
    for (int i = 0; i < 3; i++) {
        tri_points[i].Change(center.Get_x() + k * (tri_points[i].Get_x() - center.Get_x()), 
            center.Get_y() + k * (tri_points[i].Get_y() - center.Get_y()));
    }
}

void Triangle::Rorate(double angle){
    tri_points[0].Rorate(angle);
    tri_points[1].Rorate(angle);
    tri_points[2].Rorate(angle);
}

void Triangle::Mirror_x(void) {
    tri_points[0].Mirror_x();
    tri_points[1].Mirror_x();
    tri_points[2].Mirror_x();
}

void Triangle::Mirror_y(void) {
    tri_points[0].Mirror_y();
    tri_points[1].Mirror_y();
    tri_points[2].Mirror_y();
}


//测试代码
//int main() {
//    Triangle t1(1, 1, 1, 2, 2, 1);
//    std::cout << "初始状态：" << std::endl;
//    t1.Show_property();
//    t1.Show_points();
//    t1.Get_triangle_count();
//
//    std::cout << "移动后：" << std::endl;
//    t1.Move(1, 1);
//    t1.Show_points();
//
//    std::cout << "缩放后：" << std::endl;
//    t1.Zoom(0.5);
//    t1.Show_points();
//
//    std::cout << "旋转后：" << std::endl;
//    t1.Rorate(45);
//    t1.Show_points();
//
//    std::cout << "镜像后：" << std::endl;
//    t1.Mirror_x();
//    t1.Show_points();
//}
