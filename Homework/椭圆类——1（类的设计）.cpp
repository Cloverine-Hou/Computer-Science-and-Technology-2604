/*
【问题描述】
设计并测试一个名为Ellipse的椭圆类：
（1）其私有数据成员为外切矩形的左上角与右下角两个点的坐标（4个int型数据成员x1,y1,x2,y2）；
（2）声明4个公有的成员函数分别访问椭圆的外切矩形的顶点坐标，例如int Getx1();
（3）设计1个公有成员函数void Set(int,int,int,int)，对椭圆的外切矩形的顶点坐标赋值；
（4）设计1个公有成员函数Area()计算椭圆的面积。
椭圆面积公式：设外切矩形宽为w=|x2-x1|，高为h=|y2-y1|，则椭圆半轴a=w/2.0，b=h/2.0，面积S=π*a*b=π*w*h/4。取π=3.14159，结果保留4位小数。
【输入形式】
在主函数里输入外切矩形左上角与右下角坐标x1 y1 x2 y2，声明一个Ellipse类的对象，先调用Set赋值。
【输出形式】
在主函数里调用该对象的成员函数输出外切矩形的顶点坐标（x1 y1 x2 y2，空格分隔），然后计算并输出椭圆的面积（保留4位小数）。 
【样例输入】 
-3 1 3 -1
【样例输出】
-3 1 3 -1
9.4248
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const double PI = 3.14159;
class Ellipse{
    private:
    int x1,x2,y1,y2;
    public:
    void Set(int x1Val,int y1Val,int x2Val,int y2Val){
        x1=x1Val;
        x2=x2Val;
        y1=y1Val;
        y2=y2Val;
    }
    int Getx1(){
        return x1;
    }
    int Getx2(){
        return x2;
    }
    int Gety1(){
        return y1;
    }
    int Gety2(){
        return y2;
    }
    void Area(){
        printf("%.4lf\n",PI*(abs(x2-x1))*(abs(y2-y1))/4.0);
    }
};
int main(){
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    Ellipse e;
    e.Set(x1,y1,x2,y2);
    cout<<e.Getx1()<<" "<<e.Gety1()<<" "<<e.Getx2()<<" "<<e.Gety2()<<endl;
    e.Area();
    return 0;
}