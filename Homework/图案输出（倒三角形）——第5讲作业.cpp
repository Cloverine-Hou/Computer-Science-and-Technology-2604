/*
【问题描述】编写程序，在屏幕上显示图案。其中，行数n由用户输入。当n=6时，输出图案如下所示。
***********
_*********
_-*******
_-_*****
_-_-***
_-_-_*
【样例输入】
3
【样例输出】
*****
_***
_-*
【注意】符号*之间无空格，第一行左边无空格。左侧的下划线和短横线都是空格，为了突出显示而举例，实际是没有的。
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int n=0;
    cin>>n;
    for (int i = n; i >= 1; i--)
    {
        for (int j = n-i+1; j >=1; j--)
            cout << " ";
        for (int k = 2*i-1; k >=1; k--)
            cout << "*" ;
        cout << endl;
    }
    return 0;
}