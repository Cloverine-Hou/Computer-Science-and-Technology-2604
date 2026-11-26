/*
【问题描述】 
设计并测试一个名为 Rice 的类，用于数字农业系统记录水稻信息：
（1）私有数据成员：品种 variety（字符数组，最多存储 19 个字符）、株高 height（float）、稻穗数 panicle_num（int）； 
（2）编写 4 个重载构造函数，使用初始化列表初始化数值成员： 
无参构造：默认品种为 "通用稻"，株高 5，稻穗数 0； 
单参数构造：传入品种，株高 5，稻穗数 0； 
双参数构造：传入品种、株高，稻穗数 0； 
三参数构造：传入品种、株高、稻穗数； 
（3）编写析构函数，输出品种名 + "水稻对象销毁"； 
（4）编写公有成员函数 void show ()，按格式输出：
品种:xxx, 株高:xx, 稻穗数:xx。
【输入形式】 
第一行输入一个整数 n，表示待创建水稻对象的数量。 
后续 n 行，每行开头一个整数 k（0、1、2、3），代表构造参数个数，后面跟随对应数据：
 k=0，无额外数据；
 k=1，后跟字符串（品种名称）；
 k=2，后跟字符串、株高； 
 k=3，后跟字符串、株高、稻穗数。
【输出形式】 
按创建顺序，依次调用 show 输出每个水稻对象信息；
对象销毁时，析构函数自动打印销毁提示。
【样例输入】
4 0 
1 湘早籼 45 号 
2 湘早籼 45 号 25 
3 湘早籼 45 号 68 3
【样例输出】 
品种:通用稻,株高:5.0,稻穗数:0
通用稻 水稻对象销毁
品种:湘早籼45号,株高:5.0,稻穗数:0
湘早籼45号 水稻对象销毁
品种:湘早籼45号,株高:25.0,稻穗数:0
湘早籼45号 水稻对象销毁
品种:湘早籼45号,株高:68.0,稻穗数:3
湘早籼45号 水稻对象销毁
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
class Rice{
    private:
    char variety[20];
    float height;
    int panicle_num;
    public:
    Rice(){
        strcpy(variety,"通用稻");
        height=5.0f;
        panicle_num=0;
    }
    Rice(const char* var){
        strcpy(variety,var);
        height=5.0f;
        panicle_num=0;
    }
    Rice(const char* var,float h){
        strcpy(variety,var);
        height=h;
        panicle_num=0;
    }
    Rice(const char* var,float h,int num){
        strcpy(variety,var);
        height=h;
        panicle_num=num;
    }
    ~Rice() {
        cout<<variety<<" 水稻对象销毁"<<endl;
    }
    void show(){
        cout<<"品种:"<<variety<<","<<"株高:"<<fixed<<setprecision(1)<<height<<","<<"稻穗数:"<<panicle_num<<endl;
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
            Rice r;
            r.show();
        }
        else if(k==1)
        {
            char s[20];
            cin>>s;
            Rice r(s);
            r.show();
        }
        else if(k==2)
        {
            char s[20];
            float h;
            cin>>s>>h;
            Rice r(s,h);
            r.show();
        }
        else if(k==3)
        {
            char s[20];
            float h;
            int p;
            cin>>s>>h>>p;
            Rice r(s,h,p);
            r.show();  
        }
    }
    return 0;
}