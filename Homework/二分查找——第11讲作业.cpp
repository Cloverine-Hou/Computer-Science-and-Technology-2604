/*
【问题描述】
给定n个已经升序排好的整数，再给出一个待查找的目标数x。
使用二分查找，判断x是否在序列中。
如果存在，输出它的下标（下标从0开始）；
如果不存在，输出-1。
请将查找功能设计为一个独立的函数。
【输入形式】
第一行一个整数n，表示一共有n个数字，1≤n≤50
第二行n个用空格隔开的升序整数第三行一个整数x，表示要查找的
数
【输岀形式】
一个整数，找到输出下标，找不到输出-1
【样例输入】
6
1 2 3 5 7 8
5
【样例输岀】
3
【样例说明】
数组下标从0开始:a[0]=1,a[1]=2,a[2]=3,a[3]=5,a[4]=7,a[5]=8,
数字5在下标3的位置。
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
int BinSearch(int n, vector<int>& a, int find) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid=left+(right-left)/2;
        if (a[mid]==find) {
            return mid;
        } else if (a[mid] > find) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int>a;
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int x=0;
        cin>>x;
        a.push_back(x);
    }
    int find=0;
    cin>>find;
    cout<<BinSearch(n,a,find);
    return 0;
}