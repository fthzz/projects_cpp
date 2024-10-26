#pragma once
class Point
{
private:
    double x;
    double y;
    static int point_count; //计数
public:
    Point(double x, double y);
    ~Point();

    int Get_point_count(void);
    double Get_x(void);
    double Get_y(void);
    void Show_XY(void);

    void Move(double t_x, double t_y);   //以（0，0）为原点移动,输入值表示移动的距离
    void Change(double t_x, double t_y);
    void Rorate(double angle); //绕原点旋转任意角度
    void Mirror_x(void);  //关于x轴镜像
    void Mirror_y(void);
};
