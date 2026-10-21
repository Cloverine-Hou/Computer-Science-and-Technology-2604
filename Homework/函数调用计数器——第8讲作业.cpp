/*
【问题描述】
实现一个程序，包含以下三个函数，并按要求输出结果：
int next_id()：每次调用返回一个递增的编号，第一次调用返回 1，第二次返回 2，依此类推。要求使用静态局部变量实现。
int add(int x)：返回全局累加和 sum 加上参数 x 的结果，并将 x 累加到全局变量 sum 中。要求使用全局变量实现。
int local_counter()：内部定义一个普通局部变量 cnt，初始化为 0，cnt++ 后返回 cnt。用于验证局部变量每次调用都会重新初始化。
主函数按以下流程执行：
读入一个整数 n（1 ≤ n ≤ 100）；
循环 n 次，每次读入一个整数 a_i，依次调用：
int id = next_id()
int s = add(a_i)
int lc = local_counter()
输出一行：id s lc 的值
循环结束后，再单独输出一行全局变量 sum 的最终值。
【输入形式】
第一行输入一个正整数 n；
第二行输入 n 个整数 a_1 a_2 ... a_n。
【样例输入】
3
5 10 20
【样例输出】
1 5 1
2 15 1
3 35 1
35
【样例说明】
next_id() 用静态局部变量，跨调用保持，输出 1、2、3；
add() 用全局变量 sum 累加，输出 5、15、35；
local_counter() 用普通局部变量，每次调用都重新从 0 开始，所以恒为 1；
最后 sum 为 35。
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
int sum=0;
int next_id(){
    static int x=0;
    return ++x;
}
int add(int i){
    sum+=i;
    return sum;
}
int local_counter(){
    int cnt=0;
    cnt++;
    return cnt;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int x=0;
        cin>>x;
        cout<<next_id()<<" ";
        cout<<add(x)<<" ";
        cout<<local_counter()<<endl;
    }
    cout<<sum<<endl;
    return 0;
}