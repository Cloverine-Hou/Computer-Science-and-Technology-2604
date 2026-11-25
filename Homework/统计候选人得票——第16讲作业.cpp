/*
【问题描述】编程统计候选人的得票数。
设计有3个候选人zhang，li，wang，且不区分大小写，
10个选民，选民每次输入一个得票的候选人的名字，
若选民输错候选人选民，则按废票处理。
选民投票结束后程序自动显示各候选人的得票结果和废票信息。
要求用结构体数组candidate表示3个候选人的姓名和得票结果。
【样例输入】
zhang
li
wang
Wang
Li
Zhang
zhang
ZHANG
deng
Deng
【样例输出】
zhang 4
li 2
wang 2
Error 2
【提示】
struct Candidate{
    char name[20];
    int num;
}candidate[3];
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
struct Canditate{
    string name;
    int vote_n=0;
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    struct Canditate vote[3];
    int error=0;
    vote[0].name="zhang";
    vote[1].name="li";
    vote[2].name="wang";
    for(int j=0;j<10;j++){
        bool found=false;
        string temp;
        cin>>temp;
        for(char &c:temp){
            c=tolower(c);
        }
        for(int i=0;i<3;i++){
            if(temp==vote[i].name){
                found=true;
                vote[i].vote_n++;
                break;
            }
        }
        if(found==false){
            error++;
        }
    }
    for(int i=0;i<3;i++){
        cout<<vote[i].name<<" "<<vote[i].vote_n<<endl;
    }
    if(error!=0){
        cout<<"Error "<<error<<endl;
    }
    return 0;
}
