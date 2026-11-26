/*
【问题描述】 
设计并测试一个名为 Point 的类，表示农田监测的平面坐标点： 
（1）私有数据成员为横坐标 x、纵坐标 y（2 个 int 型数据成员）； 
（2）编写 3 个重载构造函数，使用初始化列表初始化：
无参构造：默认坐标 (0,0)； 
单参数构造：传入一个整数，x、y 都赋值为该值；
 双参数构造：分别传入 x、y； 
（3）编写析构函数，输出：
坐标 (x,y) 资源释放； 
（4）编写公有成员函数 void show ()，输出坐标信息，格式为坐标 (x,y)。
【输入形式】 
第一行输入一个整数 n，表示待创建坐标点对象的数量。 
后续 n 行，每行开头一个整数 k（0、1、2），代表构造参数个数： k=0，无额外数据； k=1，后跟一个整数； k=2，后跟两个整数。
【输出形式】
 按创建顺序，依次调用 show 输出每个点信息；对象销毁时，析构函数自动打印资源释放提示。
 【样例输入】 
3 
0 1 
10 2 
5 8
【样例输出】 
坐标(0,0)
坐标(0,0)资源释放
坐标(10,10)
坐标(10,10)资源释放
坐标(5,8)
坐标(5,8)资源释放
*/
#include <bits/stdc++.h>
using namespace std;
#define long long ll;
#define endl '\n'
class Point{
    private:
    int x,y;
    public:
    Point(){
        x=0;
        y=0;
    }
    Point(int num){
        x=num;
        y=num;
    }
    Point(int xVal,int yVal){
        x=xVal;
        y=yVal;
    }
    ~Point(){
        cout<<"坐标("<<x<<","<<y<<")资源释放"<<endl;
    }
    void show(){
        cout<<"坐标("<<x<<","<<y<<")"<<endl;
    }
};
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int k;
        cin>>k;
        if(k==0)
        {
            Point p;
            p.show();
        }
        else if(k==1)
        {
            int a;
            cin>>a;
            Point p(a);
            p.show();
        }
        else if(k==2)
        {
            int a,b;
            cin>>a>>b;
            Point p(a,b);
            p.show();
        }
    }
    return 0;
}
