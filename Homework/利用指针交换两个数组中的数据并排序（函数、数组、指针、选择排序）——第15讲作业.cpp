/*
1.int Read（int*x)：读取数组元素，输入0表示录入结束；函数返回实际录入的元素个数。
2.void Print(int *x，int n)：输出数组的全部元素，参数n为数组有效元素个数。
3.void Swap(int *x,int *m,int y, int n)：交换主函数中两个整型数组的全部数据，同时交换两个数组的元素个数（m、n分别保存两组数组的元素数量）。
4.void SelectSort(int*x,intn)：使用选择排序，将数组元素按从小到大升序排列。
主函数流程：调用Read分别读入两组数据，调用Swap交换两个数组，先依次打印交
换完成后的两个数组；再分别对两个数组执行选择排序，依次打印排序后的两个数组。
【输入形式】
两行整数，每行以0作为该行数据输入结束标记。
【输出形式】
一共四行：
第1、2行：交换之后两个数组的元素；
第3、4行：对应两个数组冒泡升序排序后的元素。
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
//x y数组名 n m 数组中元素个数
//将变量输入进数组 输入0时截止
int Read(int*x){
    int n=0;
    while(cin>>x[n] && x[n]!=0){
        n++;
    }
    return n;
}
//打印数组
void Print(int *x,int n){
    for(int i=0;i<n;i++){
        cout<<x[i]<<" ";
    }
    cout<<endl;
}
//交换两个数组 注意以较长的那个数组为基准 不然就交换不全
void Swap(int *x,int *m,int *y,int *n){
    int temp=*m;
    *m=*n;
    *n=temp;
    int max_len = max(*m,*n);
    for (int i=0;i<max_len;i++) {
        int temp=x[i];
        x[i]=y[i];
        y[i]=temp;
    }
}
//选排 不解释
void SelectSort(int *x,int n){
    for (int i=0;i<n-1;i++){
        int min_idx=i;
        for(int j=i+1;j<n;j++){
            if(x[j]<x[min_idx]){
                min_idx=j;
            }
        }
        if(min_idx!=i){
            swap(x[i],x[min_idx]);
        }
    }
}
//主函数目标：先交换 分别打印 再排序 再分别打印
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int arr1[100],arr2[100];
    int len1=Read(arr1);
    int len2=Read(arr2);
    Swap(arr1,&len1,arr2,&len2);
    Print(arr1,len1);
    Print(arr2,len2);
    SelectSort(arr1,len1);
    SelectSort(arr2,len2);
    Print(arr1,len1);
    Print(arr2,len2);
    return 0;
}