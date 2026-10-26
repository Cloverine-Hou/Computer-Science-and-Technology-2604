#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
// n: 盘子数
// from: 起始
// aux: 辅助
// to: 目标
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout<<from<<"->"<<n<<"->"<<to<< endl;
        return;
    }
    hanoi(n - 1,from,aux,to);
    cout <<from<<"->"<<n<<"->"<<to<<endl;
    hanoi(n - 1,aux,to,from);
}
signed main() {
    int n;
    char a,b,c;
    cin>>n>>a>>b>>c;
    hanoi(n,'a','b','c');
    return 0;
}