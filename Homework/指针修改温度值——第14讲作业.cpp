#include <iostream>
using namespace std;
#define endl '\n'
void calibrate(float *t,float offset){
    float ans=*t+offset;
    cout<<ans<<endl;
}
int main(){
    float t=0.0,offset=0.0;
    cin>>t>>offset;
    calibrate(&t,offset);
    return 0;
}