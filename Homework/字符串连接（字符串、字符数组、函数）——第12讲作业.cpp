/*

【问题描述】在实际应用中，通常需要将几个不同的字符串连接成一个字符串。请用字
符指针实现两个字符串的连接。
要求：用函数void MyStrcat(char dststr[],char srcstr[])完成。
【输入形式】两个字符串。
【输出形式】连接后的字符串。请在主函数完成字符串的输入和结果的输出。
【样例输入】
I am a student.
I am from Hubei.
【样例输出】
I am a student.l am from Hubei.
【注意】禁止使用系统自带的库函数，禁止直接cout一个一个字符输出。否则记为0
分。
【思考】使用字符数组做参数，在子函数修改字符数组的内容，回到主函数，该字符数
组发生变化了吗？
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
char dststr[100],srcstr[100];
void Mystrcat(char dststr[],char srcstr[]){
    fgets(dststr,100,stdin);
    fgets(srcstr,100,stdin);
// dststr[0]='A';
    dststr[strcspn(dststr, "\n")] = 0;
    srcstr[strcspn(srcstr, "\n")] = 0;
    strcat(dststr,srcstr);
    fputs(dststr,stdout); 
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Mystrcat(dststr,srcstr);
    return 0;
}
//会改变