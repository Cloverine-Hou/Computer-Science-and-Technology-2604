/*
【问题描述】编写一个函数char *str_bin(char*str1,char*str2)，str1、str2是两个有序字符串（其中字符按ASCII码从小到大排序），
将str2合并到字符串str1中，要求合并后的字符串仍是有序的，允许字符重复。在main函数中测试该函数：
从键盘输入两个有序字符串，然后调用该函数，最后输出合并后的结果。str_bin函数的返回值就是该结果串的起始地址。
【输入形式】分行从键盘输入两个有序字符串（不超过100个字符）
【输出形式】输出合并后的有序字符串
【输入样例】
aceg
bdfh
【输出样例】
abcdefgh
【样例说明】
输入两个有序字符串aceg和bdfh，输出合并后的有序字符串abcdefgh
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
char* str_bin(char* str1, char* str2) {
    static char result[205]; 
    int i=0,j=0,k=0;
    while (str1[i]!=0 && str2[j] !=0) {
        if (str1[i]<=str2[j]){
            result[k++]=str1[i++];
        } else {
            result[k++]=str2[j++];
        }
    }
    while(str1[i]!=0){
        result[k++]=str1[i++];
    }
    while(str2[j]!=0){
        result[k++]=str2[j++];
    }
    result[k]='\0';
    return result;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char str1[105],str2[105];
    cin>>str1>>str2;
    cout<<str_bin(str1,str2);
    return 0;
}