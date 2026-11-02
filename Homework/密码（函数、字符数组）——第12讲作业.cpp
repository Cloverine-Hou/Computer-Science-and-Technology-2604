/*
【问题描述】假设一个比较安全的密码至少应该满足下面两个条件：
（1)密码长度大于等于8，且不要超过16。
（2）密码中的字符应该来自下面“字符类别”中四组中的至少三组。
这四个字符类别分别为：
1. 大写字母：A, B,C...Z;
2. 小写字母：a, b, c... z;
3. 数字:0, 1, 2...9;
4. 特殊符号：,!,@,#,$,%，"；
给你一个密码，你的任务就是判断它是不是一个安全的密码。
请设计函数boolPassword(charstr[)实现之。
【输入形式】测试实例包含一个密码（长度最大为50），密码仅包括上面的四类字符。
【输出形式】对于测试实例，判断这个密码是不是一个安全的密码，是的话输出YES，否则输出NO。
【样例输入】a1b2c3d4
【样例输出】NO
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
bool Password(char str[]){
    int len=strlen(str);
    int hasUpper=0,hasLower=0,hasDigit=0,hasSpecial=0;
    for(int i=0;str[i]!=0;i++){
        char specials[] = "~!@#$%^";
        if(str[i]>='A' && str[i]<='Z'){
            hasUpper=1;
        }else if(str[i]>='a' && str[i]<='z'){
            hasLower=1;
        }else if(str[i]>='1' && str[i]<='9'){
            hasDigit=1;
        }
        for (int j=0;specials[j]!=0;j++) {
            if(str[i]==specials[j]){
                hasSpecial=1;
                break;
            }
        }
    }
    int Safe=hasUpper+hasLower+hasDigit+hasSpecial;
    if(Safe>=3 && (len>=8 && len<=16)){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
    return false;
}
//用C++ String的版本
// bool SafePassword(const string&password){
//     if(password.length()<8||password.length()>16){
//         return false;
//     }
//     string specialChars = "~!@#$%^";
//     bool hasUpper=false;
//     bool hasLower=false;
//     bool hasDigit=false;
//     bool hasSpecial=false;
//     int typeCount = 0;
//     for(char c:password){
//         if (isupper(c) && !hasUpper){
//             hasUpper=true;
//             typeCount++;
//         }
//         else if(islower(c) && !hasLower){
//             hasLower=true;
//             typeCount++;
//         }
//         else if(isdigit(c) && !hasDigit){
//             hasDigit=true;
//             typeCount++;
//         }
//         else if(specialChars.find(c)!=string::npos && !hasSpecial) {
//             hasSpecial=true;
//             typeCount++;
//         }
//         if(typeCount >= 3){
//             return true;
//         }
//     }
//     return false;
// }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // string password;
    // cin>>password;
    char str[100];
    cin>>str;
    Password(str);
    return 0;
}