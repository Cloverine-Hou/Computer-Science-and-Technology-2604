/*
【问题描述】有一个有趣的古典数学问题：有一对兔子，从出生后第3个月起每个月都生1对兔子，小兔子长到第3个月后每个月又生1对兔子。
假设所有兔子都不死，问每个月兔子的总对数为多少？
【提示】不满1个月的为小兔子，满1个月不满2个月的为中兔子，满3个月以上的为老兔子。
每对老兔子每个月会生1对小兔子。因此，每个月的兔子总数依次为1,1,2,3,5,8,13,…。这就是Fibonacci数列。
该数列的递归定义如下：f(n)=1 (n等于0或1)；f(n)= f(n-1)+ f(n-2)  (n>=2)
请编写递归函数long long fib(int n)，求出第n个月兔子的总对数。
【输入形式】输入一个正整数n，表示求第n个月兔子的总对数。
【输出形式】输出为一行，第n个月兔子的总对数。
【样例输入】10
【样例输出】89
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
int Fib(int n) {
    if (n == 0 || n == 1)
        return 1;
    return Fib(n - 1) + Fib(n - 2);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    cout<<Fib(n);
    return 0;
}