/*
【问题描述】编写程序计算 1！+2！+……+n!的值，即计算从1到n的阶乘之和。
【输入形式】输入一个小于100的整数n。
【输出形式】一个整数，即计算结果。
【样例输入】3
【样例输出】9
【样例说明】1！+2！+3！=9
【注意】使用单重循环或双重循环实现上述计算均可，注意对比差异。
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n;
    cin >> n;
    int fact = 1;
    int sum = 0;
    for (int i=1;i<= n;i++) {
        fact *=i;
        sum += fact;
    }
    cout << sum << endl;
    return 0;
}