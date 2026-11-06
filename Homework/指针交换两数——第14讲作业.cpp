#include <iostream>
using namespace std;
#define endl '\n'
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
int main(){
    int a=0,b=0;
    cin>>a>>b;
    swap(&a,&b);
    cout<<a<<" "<<b<<endl;
    return 0;
}