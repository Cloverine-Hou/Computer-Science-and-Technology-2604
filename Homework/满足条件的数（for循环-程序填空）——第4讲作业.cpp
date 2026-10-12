/*
【问题描述】找出1000-2000之间所有整数中满足如下条件的数：
该数的高端两位数字的和与低端两位数字的和值相等，如1001, 1120。程序能输出所有满足条件的数以及它们的总个数。
【输入形式】无输入
【输出形式】满足条件的数以及它们的总个数
【样例输入】无
【样例输出】此处省略
*/
#include <iostream>
using namespace std;
int main(){
    int num[4];
    for(int i=0;i<4;i++){
        num[i]=0;
    }
    int cnt2=0;
    for(int n=1000;n<2000;n++){
    int cnt1=3;
    int t=n;
        while(t>0){
            for(int i=0;i<4;i++){
                num[cnt1]=t%10;
                cnt1--;
                break;
            }
                t=t/10;
        }
        if(num[0]+num[1]==num[2]+num[3]){
            cnt2++;
            printf("%d ",n);
        }
    }
    printf("\n%d",cnt2);
}