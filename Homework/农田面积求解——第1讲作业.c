#include <stdio.h>
#include <math.h>
int main(){
    double a,b,c=0.0;
    int min,medium,max=0;
    scanf("%lf %lf %lf",&a,&b,&c);
    if(a>=b){
        if(a>=c){
            max = a;
            if(b>=c){
            medium = b;
            min = c;
        } else {
            min = b;
            medium = c;
        }
        } else{
            max = c;
            medium = a;
            min = b;
        }
    } else if (a<b){
        if(c<=b){
            max = b;
            if(a>=c){
            medium = a;
            min = c;
        } else {
            min = a;
            medium = c;
        }
        } else{
            max = c;
            medium = b;
            min = a;
        }
    }
    if(min+medium<=max){
        printf("ERROR");
    } else {
    double p=(a+b+c)/2;
    double S=sqrt(p*(p-a)*(p-b)*(p-c));
    printf("%.3lf",S);
    }
}
