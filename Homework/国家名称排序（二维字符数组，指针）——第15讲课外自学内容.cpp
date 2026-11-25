/*
【问题描述】 有一个二维字符数组，用来存储若干个国家的英文名称。
另外定义字符指针数组，指针数组的每个元素指向二维字符数组中的一条国家名字符串。
利用指针完成排序，将国家名称按照字典序从小到大排列。
排序时只交换指针数组中的指针，不修改二维字符数组内原始字符串的内容。
在主函数中完成测试，输入若干国家名称，以 # 作为输入结束标记，调用排序函数之后输出排序结果。
【输入形式】 
每行输入一个国家名称，以 # 作为输入结束标记，单个国家名称长度不超过 20，国家总数不超过 50。
【输出形式】 
逐行输出字典序升序排列后的国家名称。
【样例输入】 
China 
America 
Brazil 
Japan
#
【样例输出】 
America 
Brazil 
China 
Japan
【提示】 
国家原始数据保存在二维字符数组中；
借助字符指针数组进行排序，排序只交换指针，不改动二维数组里面存储的原始字符串；
字符串比较使用 strcmp 函数。
#define MAX_COUNTRY 50 
#define MAX_LEN 20   
// 二维字符数组：存放原始国家名称，不改动
char country[MAX_COUNTRY][MAX_LEN];
// 指针数组：每个指针指向二维数组中的一行字符串
char *p[MAX_COUNTRY];
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
#define MAX_COUNTRY 50
#define MAX_LEN 21
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
bool cmp(char*a,char*b){
    return strcmp(a,b)<0; 
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char country[MAX_COUNTRY][MAX_LEN];
    char *p[MAX_COUNTRY];  
    int n=0;
    while(cin>>country[n]){
        if(strcmp(country[n],"#")==0)break;
        p[n]=country[n];
        n++;
    }
    sort(p,p+n,cmp);
    for (int i=0;i<n;i++){
        cout<<p[i]<<endl;
    }
    return 0;
}