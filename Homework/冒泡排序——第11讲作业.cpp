/*
【问题描述】
给定n个整数，使用冒泡排序进行升序排序。
要求：实现标准冒泡，每一轮把当前未排序区间里最大的数交换到区间
末尾，最后输出从小到大排好的序列。
且将该冒泡排序功能函数化。
【输入形式】
第一行一个整数n，表示一共有n个数字，1≤n≤50
第二行n个用空格隔开的整数
【输出形式】
一行，从小到大排序后的整数，数字之间空格分隔
【样例输入】
6
5 3 8 1 2 7
【样例输岀】
1 2 3 5 7 8
【样例说明】
第一轮冒泡把最大值8换到最后；第二轮把7换到倒数第二个位置，依次完成升序。
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
//冒泡排序
void bubbleSort(vector<int>& a){
    int n=a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
//打印数组
void printArray(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    vector<int>a;
    for(int i=0;i<n;i++){
        int x=0;
        cin>>x;
        a.push_back(x);
    }
    bubbleSort(a);
    printArray(a);
    return 0;
}