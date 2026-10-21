/*
【问题描述】
输入一个非负整数 n，使用递归函数计算并输出 n!（0! = 1）。
要求：必须定义递归函数 long long fact(int n) 实现，不得用循环。
【输入形式】
键盘输入一个非负整数 n。
【样例输入1】
5
【样例输出1】
120
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
int Fact(int n){
    if(n<=1){
        return 1;
    }
    return n*Fact(n-1);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    cout<<Fact(n);
    return 0;
}