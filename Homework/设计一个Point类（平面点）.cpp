/*
【问题描述】
设计并测试一个名为Point的类，表示平面直角坐标系中的一个点：
（1）其私有数据成员为点的横坐标和纵坐标（2个int型数据成员x,y）；
（2）声明2个公有的成员函数分别访问点的坐标，例如int Getx();
（3）设计1个公有成员函数void Set(int,int)，用于对点的坐标赋值；
（4）设计1个公有成员函数int Distance2(Point p)，计算当前点与参数点p之间距离的平方（即(x-p.x)^2+(y-p.y)^2），返回int型结果；
（5）设计1个公有成员函数void Move(int dx,int dy)，将当前点的横坐标增加dx、纵坐标增加dy。
【输入形式】
第一行输入两个整数，表示第一个点的坐标x1 y1，声明一个Point类对象并调用Set赋值；
第二行输入两个整数，表示第二个点的坐标x2 y2，声明第二个Point类对象并调用Set赋值；
第三行输入两个整数dx dy，表示对第一个点进行平移的偏移量。
【输出形式】
第一行输出第一个点的坐标（x y，空格分隔）；
第二行输出第二个点的坐标（x y，空格分隔）；
第三行输出第一个点与第二个点距离的平方；
第四行对第一个点调用Move(dx,dy)后，输出平移后第一个点的坐标（x y，空格分隔）。
【样例输入】
0 
3 4
2 -1
【样例输出】
0 0
3 4
25
2 -1
*/
#include <iostream>
using namespace std;
#define endl '\n'
class Point{
    private:
    int x,y;
    public:
    int GetX(){
        return x;
    }
    int GetY(){
        return y;
    }
    void Set(int xVal,int yVal){
        x=xVal;
        y=yVal;
    }
    int Distance2(Point p){
        return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
    }
    void Move(int dx,int dy){
       x+=dx;
       y+=dy; 
    }
};
int main(){
    int x1,y1;
    Point p1;
    cin>>x1>>y1;
    p1.Set(x1,y1);
    int x2,y2;
    Point p2;
    cin>>x2>>y2;
    p2.Set(x2,y2);
    int dx,dy;
    cin>>dx>>dy;
    cout<<p1.GetX()<<" "<<p1.GetY()<<endl;
    cout<<p2.GetX()<<" "<<p2.GetY()<<endl;
    cout<<p1.Distance2(p2)<<endl;
    p1.Move(dx,dy);
    cout<<p1.GetX()<<" "<<p1.GetY()<<endl;
}