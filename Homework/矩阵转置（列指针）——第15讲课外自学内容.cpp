/*
【问题描述】请写一函数，将一个m*n的整型矩阵转置。
注意：请将转置后的数据存储到二维数组中以后，再对二维数组进行输出。
要求使用如下函数进行转置：
void Transpose(int *a, int *at, int m, int n):
测试样例保证矩阵元素x（-1000<X<1000)，且为整数，二维矩阵维数64<N,M<64
【输入形式】矩阵长度和宽度及矩阵元素值
【输出形式】调用函数转置后的矩阵
【样例输入】
3 4
1 2 3 4
4 5 6 7
7 8 9 0
【样例输岀】
1 4 7
2 5 8
3 6 9
4 7 0
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
void Transpose(int*a,int*at,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            at[j*70+i]=a[i*70+j];
        }
    }
}
int main(){
    int m,n;
    cin>>m>>n;
    int a[70][70];
    int at[70][70];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    Transpose(&a[0][0],&at[0][0],m,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<at[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}