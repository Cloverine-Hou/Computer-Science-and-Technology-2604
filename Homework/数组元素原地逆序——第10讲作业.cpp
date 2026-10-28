/*
【问题描述】 输入 n 以及 n 个整数，存入一维数组，将数组内元素原地逆序，最后输出逆序之后的数组。不能新开一个数组存放结果。
【输入形式】 第一行一个整数 n，1<=n<=20 第二行 n 个整数
【输出形式】 一行，逆序后的所有数字，数字之间空格隔开，末尾换行
【样例输入】
5
1 2 3 4 5 
【样例输出】 
5 4 3 2 1
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=n-1;i>=0;i--){
        cout<<arr[i]<<" ";
    }
    return 0;
}