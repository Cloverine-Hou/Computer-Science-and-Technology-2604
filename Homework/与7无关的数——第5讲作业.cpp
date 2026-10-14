/*
【问题描述】
一个正整数，如果它能被7整除，或者它的十进制表示法中某一位上的数字为7，则称其为与7相关的数。现求所有小于等于n(n<100)与7无关的正整数的平方和。
【输入形式】
输入为一行,正整数n(n < 100)。
【输出形式】
输出一行，包含一个整数，即小于等于n的所有与7无关的正整数的平方和。
【样例输入】
21
【样例输出】
2336
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int n=0,sum=0;
    cin>>n;
    int num[3];
    for(int i=1;i<=n;i++){
        int t=i;
        if(t%7==0){
            continue;
        }
        while(t>0){
            for(int i=0;i<3;i++){
                num[2-i]=t%10;
                t=t/10;
            }
        if(num[0]==7 || num[1]==7 || num[2]==7){
            continue;
        }
        sum+=i*i;
        }
    }
    cout << sum;
    return 0;
}