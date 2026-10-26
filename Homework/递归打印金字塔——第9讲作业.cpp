#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
void pyramid(int h,int row){
    if(row>h){
        return;
    }
    if(row<=h){
        for(int i=0;i<h-row;i++){
            cout<<" ";
        }
        for(int i=0;i<2*row-1;i++){
            cout<<"*";
        }
    }
    cout<<endl;
    pyramid(h,row+1);
}
// void pyramid(int h,int row){
//     if(row>h){
//         return;
//     }
//     pyramid(h,row+1);
//     if(row<=h){
//         for(int i=0;i<h-row;i++){
//             cout<<" ";
//         }
//         for(int i=0;i<2*row-1;i++){
//             cout<<"*";
//         }
//     }
//     cout<<endl;
// }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h=0,row=0;
    cin>>h;
    pyramid(h,row);
    return 0;
}
/*
若交换打印与递归调用 则会输出倒三角形
*/