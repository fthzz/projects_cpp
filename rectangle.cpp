#include "rectangle.hpp"
#include <iostream>

int Rectangle::rectangle_count = 0;

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4):
	rect_points{ Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4)},
	rect_lines{ Line(x1, y1, x2, y2), Line(x1, y1, x3, y3), Line(x2, y2, x4, y4), Line(x4, y4, x3, y3)}
{
	rectangle_count++;
	perimeter = 0;
	area = 0;
}

Rectangle::~Rectangle() {
	rectangle_count--;
}

Point* Rectangle::Get_points(void) {
    return rect_points;
}

void Rectangle::Show_points(void) {
    std::cout << "矩形的顶点坐标分别是：" << std::endl;
    std::cout << "(" << rect_points[0].Get_x() << "," << rect_points[0].Get_y() << ")" << std::endl;
    std::cout << "(" << rect_points[1].Get_x() << "," << rect_points[1].Get_y() << ")" << std::endl;
    std::cout << "(" << rect_points[2].Get_x() << "," << rect_points[2].Get_y() << ")" << std::endl;
    std::cout << "(" << rect_points[3].Get_x() << "," << rect_points[3].Get_y() << ")" << std::endl;
}

int Rectangle::Get_Rectangle_count(void) {
    std::cout << "矩形的个数：" << rectangle_count << std::endl;
    return rectangle_count;
}

double Rectangle::Get_perimeter(void) {
    double l1, l2;
    l1 = rect_lines[0].Get_length();
    l2 = rect_lines[1].Get_length();

    perimeter = (l1 + l2) * 2;
    return perimeter;
}

double Rectangle::Get_area(void) {
    double a = rect_lines[0].Get_length();
    double b = rect_lines[1].Get_length();

    area = a * b;
    return area;
}

void Rectangle::Show_property(void) {
    std::cout << "矩形的周长：" << Get_perimeter() << std::endl;
    std::cout << "矩形的面积：" << Get_area() << std::endl;
}

void Rectangle::Move(double t_x, double t_y) {
    rect_points[0].Move(t_x, t_y);
    rect_points[1].Move(t_x, t_y);
    rect_points[2].Move(t_x, t_y);
    rect_points[3].Move(t_x, t_y);
}

void Rectangle::Zoom(double k) {
    Point center((rect_points[0].Get_x() + rect_points[1].Get_x()) / 2,
        (rect_points[0].Get_y() + rect_points[2].Get_y()) / 2); // 坐标

    for (int i = 0; i < 3; i++) {
        rect_points[i].Change(center.Get_x() + k * (rect_points[i].Get_x() - center.Get_x()),
            center.Get_y() + k * (rect_points[i].Get_y() - center.Get_y()));
    }
}

void Rectangle::Rorate(double angle) {
    rect_points[0].Rorate(angle);
    rect_points[1].Rorate(angle);
    rect_points[2].Rorate(angle);
    rect_points[3].Rorate(angle);
}

void Rectangle::Mirror_x(void) {
    rect_points[0].Mirror_x();
    rect_points[1].Mirror_x();
    rect_points[2].Mirror_x();
    rect_points[3].Mirror_x();
}

void Rectangle::Mirror_y(void) {
    rect_points[0].Mirror_y();
    rect_points[1].Mirror_y();
    rect_points[2].Mirror_y();
    rect_points[3].Mirror_y();
}

//测试代码
//int main() {
//    Rectangle r1(1, 1, 1, 2, 2, 1, 2, 2);
//    std::cout << "初始状态：" << std::endl;
//    r1.Show_property();
//    r1.Show_points();
//    r1.Get_Rectangle_count();
//
//    std::cout << "移动后：" << std::endl;
//    r1.Move(1, 1);
//    r1.Show_points();
//
//    std::cout << "缩放后：" << std::endl;
//    r1.Zoom(0.5);
//    r1.Show_points();
//
//    std::cout << "旋转后：" << std::endl;
//    r1.Rorate(45);
//    r1.Show_points();
//
//    std::cout << "镜像后：" << std::endl;
//    r1.Mirror_x();
//    r1.Show_points();
//
//    return 0;
//}