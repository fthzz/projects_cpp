#include <iostream>
#include "math.h"
#include "line.hpp"

int Line::line_count=0;

Line::Line(double s_x, double s_y, double e_x, double e_y): start(s_x, s_y), end(e_x, e_y) {
    length=sqrt((s_x-e_x)*(s_x-e_x)+(s_y-e_y)*(s_y-e_y));
    line_count++;
}

Line::~Line(){
    line_count--;
}

Point Line::Get_start(void){
    return start;
}

Point Line::Get_end(void){
    return end;
}

void Line::Show_start(void){
    std::cout<<"线段的起点：("<<start.Get_x()<<","<<start.Get_y()<<")"<<std::endl;
}

void Line::Show_end(void){
    std::cout<<"线段的终点：("<<end.Get_x()<<","<<end.Get_y()<<")"<<std::endl;
}

int Line::Get_line_count(void){
    std::cout<<"线段的数量："<<line_count<<std::endl;
    return line_count;
}

double Line::Get_length(void){
    return length;
}

void Line::Show_property(void){
    std::cout<<"线段的长度："<<Get_length()<<std::endl;
}

void Line::Move(double t_x1, double t_y1) {
    start.Move(t_x1, t_y1);
    end.Move(t_x1, t_y1);
}

void Line::Zoom(double k) {
    double m_x = (start.Get_x() + end.Get_x()) / 2;
    double m_y = (start.Get_y() + end.Get_y()) / 2;
    
    double tempx1, tempx2, tempy1, tempy2;
    tempx1 = m_x - start.Get_x();
    tempx2 = -m_x + end.Get_x();
    tempy1 = m_y - start.Get_y();
    tempy2 = -m_y +  end.Get_y();

    start.Change(m_x - tempx1 * k, m_y - tempy1 * k);
    end.Change(m_x + tempx2 * k, m_y + tempy2 * k);
}

void Line::Rorate(double angle) {
    start.Rorate(angle);
    end.Rorate(angle);
}
void Line::Mirror_x(void) {
    start.Mirror_x();
    end.Mirror_x();
}
void Line::Mirror_y(void) {
    start.Mirror_y();
    end.Mirror_y();
}

// 测试代码
// int main(){
    //Line l1(-1, -1, 2, 2);
    //std::cout << "初始状态：" << std::endl;
    //l1.Show_property();
    //l1.Get_line_count();

    //std::cout << "移动后：" << std::endl;
    //l1.Move(1, 1);
    //l1.Show_start();
    //l1.Show_end();

    //std::cout << "缩放后：" << std::endl;
    //l1.Zoom(0.5);
    //l1.Show_start();
    //l1.Show_end();

    //std::cout << "旋转后：" << std::endl;
    //l1.Rorate(45);
    //l1.Show_start();
    //l1.Show_end();

    //std::cout << "镜像后：" << std::endl;
    //l1.Mirror_x();
    //l1.Show_start();
    //l1.Show_end();
// }