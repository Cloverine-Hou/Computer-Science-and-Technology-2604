/*
请阅读代码并分析程序功能，总结归纳行指针、列指针的使用方法。
因为ITC判题系统对数组空间的地址未知，所以前9行代码关于地址等的输出被“//”注释掉了。
请同学们在自己的电脑上调试运行，看一看a,a+1,a+2,*a,*(a+1),*(a+0)+3,a[0],*(a+1)+1,*(*(a+1)+1)的输出分别是什么？代表了什么含义。
【要求】请为程序中关键代码加上注释后，再提交。可以添加输出的内容、或代表的含义等。
*/
#include <iostream>
using namespace std;
//计算a+b 存入c
void Add_array(int a[][5], int b[][5], int c[][5], int nrow); //二维数组形式传参
void Add_rowptr(int (*pa)[5], int (*pb)[5], int (*pc)[5], int nrow); //行指针传参
void Add_colptr(int *pa, int *pb, int *pc, int nrow, int ncol); //列指针传参
void Print(int a[][5], int n);
int main()
{
    int a[3][5] = { 1, 2, 3, 4, 5, 
                    6, 7, 8, 9, 10,
                    11, 12, 13, 14, 15};
    // //a是行指针 跨度一整行
    // cout<<"a   is " <<a<<endl; //第一行首地址
    // cout<<"a+1 is "<<a+1<<endl;//第二行首地址
    // cout<<"a+2 is "<<a+2<<endl;//第三行首地址
    // cout<<endl;
    // //*a将行指针解引用 降级为列指针 跨度一个元素
    // cout<<"*a       is "<<*a<<endl; //第一行首地址
    // cout<<"*(a+1)   is "<<*(a+1)<<endl; //第二行首地址
    // cout<<"*(a+0)+3 is "<<*(a+0)+3<<endl; //第一行第4个元素的地址 &a[0][3]
    // cout<<endl;
    // //等价于*a
    // cout<<"a[0]        is " <<a[0]<<endl; //第一行首地址
    // cout<<"*(a+1)+1    is "<<*(a+1)+1<<endl; //第二行第2个元素的地址 &a[1][1]
    // cout<<"*(*(a+1)+1) is "<<*(*(a+1)+1)<<endl; //第二行第2个元素的值 *&a[1][1]==7
    // cout<<endl;
    int b[3][5] = {1, 1, 1, 1, 1};
    int c[3][5];
    //二维数组传参
    Add_array(a, b, c, 3);        //请观察传参的形式
    Print(c,3);
    cout<<endl;
    //行指针传参
    Add_rowptr(a, b, c, 3);       //请观察传参的形式
    Print(c,3);
    cout<<endl;
    //列指针传参
    //传入 *a (即 &a[0][0])，把它当作一维连续内存处理
    Add_colptr(*a, *b, *c, 3, 5);  //请观察传参的形式
    Print(c,3);
    return 0;
}
//参数形式：int a[][5] 编译器会自动将其转化为行指针 int (*a)[5]
void Add_array(int a[][5], int b[][5], int c[][5], int nrow) //请观察参数的形式及使用方法
{
    for(int i=0; i<nrow; i++)
    {
        for(int j=0; j<5; j++)
        {
            c[i][j] = a[i][j]+b[i][j];
        }
    }
}
//参数形式：int (*pa)[5] 行指针 跨度为20字节
void Add_rowptr(int (*pa)[5], int (*pb)[5], int (*pc)[5], int nrow) //请观察参数的形式及使用方法
{
    for(int i=0; i<nrow; i++)
    {
        for(int j=0; j<5; j++)
        {
            // pc+i 跳至第i行 解引用得到第i行首列指针
            // +j 跳至第j列 再解引用取出数据
            *(*(pc+i)+j) = *(*(pa+i)+j) + *(*(pb+i)+j);
        }
    }
}
//参数形式：int *pa 列指针 跨度4字节 二维数组被降维成一维连续内存
void Add_colptr(int *pa, int *pb, int *pc, int nrow, int ncol) //请观察参数的形式及使用方法
{
    for(int i=0; i<nrow; i++)
    {
        for(int j=0; j<ncol; j++)
        {
            //计算偏移量 行号*列数+列号
            *(pc+ncol*i+j) = *(pa+ncol*i+j) + *(pb+ncol*i+j);
        }
    }
}
//参数 int a[][5] 退化为行指针 int (*a)[5]
void Print(int a[][5], int n)  //请观察参数的形式及使用方法
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<5; j++)
        {
            cout<<a[i][j]<<"\t";
        }
        cout<<endl;
    }
}