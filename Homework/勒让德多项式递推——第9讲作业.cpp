#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
double LRDDXS1(int n,double x){
    if(n==0){
        return 1.0;
    }
    if(n==1){
        return x;
    }
    return ((2.0*n-1.0)/n)*x*LRDDXS1(n-1,x)-((n-1.0)/n)*LRDDXS1(n-2,x);
}
double LRDDXS2(int n,double x) {
    if(n==0){
        return 1.0;
    }
    if(n==1){
        return x;
    }
    double p0=1.0;
    double p1=x;
    double pn=0.0;
    for(int i=2;i<=n;i++){
        pn=((2.0*i-1.0)/i)*x*p1-((i-1.0)/i)*p0;
        p0=p1;
        p1=pn;
    }
    return pn;
}
signed main(){
    int n=0;
    double x=0.0;
    cin>>n>>x;
    printf("%.2lf\n",LRDDXS1(n,x));
    printf("%.2lf\n",LRDDXS2(n,x));
    return 0;
}
/*
迭代版本运行更快
纯递推版本存在大量的重复计算 时间复杂度O(2^n)
迭代版本只需保留要求的项的前面两项不断往后算即可 时间复杂度O(n)

递归版本n过大可能会导致TLE与栈溢出

可用数组或vector将算过的项存起来
一步一步往后推 最后直接返回最后一项
*/