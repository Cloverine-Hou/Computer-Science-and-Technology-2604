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
    int rows=0,cols=0;
    cin>>rows>>cols;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[0].size(); j++) {
            int x=0;
            cin>>x;
            grid[i][j]=x;
        }
    }
    vector<int> rowMax(rows,LLONG_MIN),colMin(cols,LLONG_MAX);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(grid[i][j]>rowMax[i]){
                rowMax[i]=grid[i][j];
            }
            if(grid[i][j]<colMin[j]){
                colMin[j]=grid[i][j];
            }
        }
    }
    bool found=false;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++)
            if(grid[i][j]==rowMax[i]&&grid[i][j]==colMin[j]){
                cout<<grid[i][j]<<" "<<i+1<<" "<<j+1<<endl;
                found=true;
            }
    }
    if(!found){
        cout<<"No answer"<<endl;
    }
    return 0;
}