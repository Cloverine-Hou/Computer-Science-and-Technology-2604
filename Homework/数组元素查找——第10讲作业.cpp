/*
【问题描述】 输入正整数 n（1<n<=10），再输入 n 个整数存入数组，接着输入待查找整数 x。
编写函数 int search (int list [], int n, int x)，在数组中查找 x，找到返回最小下标，找不到返回 - 1。
根据函数返回值输出结果：找到输出 index = 下标，找不到输出 Not found。
【输入形式】 第一行：整数 n 第二行：n 个整数 第三行：整数 x
【输出形式】 查找成功，输出 index = 后接下标；查找失败，输出 Not found
【样例输入 1】
3 
1 2 -6 
2 
【样例输出 1】 
index = 1
【样例输入 2】 
5
1 2 2 5 4 
0
【样例输出 2】
Not found
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
int search(int list[],int n,int x){
    for(int i=0;i<n;i++){
        if(list[i]==x){
            return i;
        }
    }
    return -1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0,x=0;
    cin>>n;
    int list[n];
    for(int i=0;i<n;i++){
        cin>>list[i];
    }
    cin>>x;
    int result = search(list, n, x);
    if (result != -1) {
        cout << "index = " << result << endl;
    } else {
        cout << "Not found" << endl;
    }
    return 0;
}