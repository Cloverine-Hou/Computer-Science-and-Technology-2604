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
    string s;
    string ans;
    cin>>s;
    unordered_set<char>once;
    for(char c:s){
        if(once.insert(c).second){
            ans+=c;
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans<<endl;
    return 0;
}