#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows,cols;
    cin>>rows>>cols;
    vector<vector<int>> grid1(rows, vector<int>(cols, 0));
    vector<vector<int>> grid2(cols, vector<int>(rows, 0));
    for (int i = 0; i < (int)grid1.size(); i++) {
        for (int j = 0; j < (int)grid1[0].size(); j++) {
            int x=0;
            cin>>x;
            grid1[i][j]=x;
        }
        cout << endl;
    }
    for (int i = 0; i < (int)grid2.size(); i++) {
        for (int j = 0; j < (int)grid2[0].size(); j++) {
            cout<<grid1[j][i]<<" ";
        }
        cout << endl;
    }
    return 0;
}