/*
【问题描述】一个数如果恰好等于它的因子之和，这个数就成为“完数”。
例如，6的因子为1、2、3，而6＝1＋2＋3，因此6是“完数”。
编程序打印出1000之内（包括1000）所有的完数，并按如下格式输出其所有因子： 
6 its factors are 1,2,3.
【输入形式】无输入
【输出形式】输出1000以内所有的完数及其因子，每行输出一个完数及其因子。 
6 its factors are 1,2,3.
【提示】完数不止一个哦！而且最后一个数后面的结束标点符号是英文状态的句号。
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    for(int x = 2; x <= 1000; x++){
        int arr[1000] = {0};
        int j = 0;
        int sum = 0;
        for(int i = 1; i <= x / 2; i++){
            if(x % i == 0){
                arr[j] = i;
                j++;
                sum += i;
            }
        }
        if(sum == x){
            printf("%lld its factors are ", x);
            for(int k = 0; k < j; k++){
                if(k == j - 1){
                    printf("%lld.\n", arr[k]);
                } else {
                    printf("%lld,", arr[k]);
                }
            }
        }
    }
    return 0;
}