#include <stdio.h>
int main(){
    int x;
    int sum=0;
    scanf("%d",&x);
    while(x>0){
        int a=x%10;
        sum=sum+a;
        x=x/10;
    }
    printf("%d\n",sum );
    if(sum>=15 && sum<=30){
        printf("合法");
    } else {
        printf("不合法");
    }
    return 0;
}
