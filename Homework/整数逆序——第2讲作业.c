#include <stdio.h>
int main(){
    long long x=0;
    scanf("%lld",&x);
    long long a=x;
    do {
        a=x%10;
        x=x/10;
        int b=a;
        if(b!=0){
            printf("%d",b);
            break;
        }
        }while(x>0);
    while(x>0){
        a=x%10;
        x=x/10;
        int b=a;
        printf("%d",b);
    }
    return 0;
}
