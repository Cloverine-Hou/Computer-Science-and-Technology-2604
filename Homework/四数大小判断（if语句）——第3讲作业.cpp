/*
【问题描述】输入四个整型数据，请按从小到大的顺序将其输出。
【输入形式】四个整型数
【输出形式】从小到大顺序输出
【样例输入】5 4 2 6
【样例输出】2 4 5 6
*/
#include <iostream>
using namespace std;
int main(){
    int a,b,c,d;
    int temp=0;
    cin >> a >> b >> c >> d;
    int arr[4]={a,b,c,d};
    for(int i=0;i<3;i++){
        for (int j = 0; j < 3 - i; j++) {
        if(arr[j]>arr[j+1]){
            temp = arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
        }
    }
    }
    for(int i=0;i<4;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}