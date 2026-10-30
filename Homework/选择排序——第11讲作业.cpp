/*
【问题描述】
给定n个整数，使用选择排序进行升序排序。
要求：实现标准选择排序，每一轮在未排序区间找到最小值，和未排序
区间第一个位置交换，逐步扩大前面有序区间，最后输出从小到大排好
的序列。
且将该选择排序功能函数化。
【输入形式】
第一行一个整数n，表示一共有n个数字，1≤n≤50
第二行n个用空格隔开的整数
【输岀形弎】
一行，从小到大排序后的整数，数字之间空格分隔
【样例输入】
6
5 3 8 1 2 7
【样例输岀】
1 2 3 5 7 8
【样例说明】
第一轮在全部元素中找到最小值1，和第一个元素交换；第二轮在剩下元
素里找到最小值2，和第二个元素交换，依次完成排序。
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
//选择排序
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        if (minIdx != i) swap(a[i], a[minIdx]);
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
    selectionSort(a);
    printArray(a);
    return 0;
}