//编写程序求出下式中n的最大值：22＋42＋62＋…＋N2<1500
#include <iostream>
using namespace std;
int main(){
    int n=2,sum=0,N=0;
    while(sum<1500){
        n+=20;
        sum+=n;
        N+=2;
        if(sum>=1500){
            N-=2;
            break;
        }
    }
    cout << N;
    return 0;
}