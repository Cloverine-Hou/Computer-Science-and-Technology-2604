/*
【题目描述】
一条贪吃蛇的身体由一组坐标依次记录。
输入蛇身体的坐标数量 n，随后依次输入 n 组坐标。
请使用头插法建立单链表存储蛇身，然后从头到尾遍历链表，依次输出链表里面每一段身体的坐标。
【输入格式】
第一行一个整数 n，表示蛇身体坐标个数。
接下来 n 行，每行两个整数 x y，代表蛇身一段的坐标。
【输出格式】
每行输出一组坐标，按照链表存储顺序输出。
头插，输入顺序 1,1 → 1,5，链表顺序反过来。
【样例输入】
5 
1 1 
1 2 
1 3 
1 4 
1 5
【样例输出】
1 5 
1 4 
1 3 
1 2 
1 1
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
struct Node{
    int x,y;
    Node *next;
};
Node* head = nullptr;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        Node* newNode = new Node;
        newNode->x=x;
        newNode->y=y;
        newNode->next=head;
        head=newNode;
    }
    Node* cur =head;
    while(cur!=nullptr){
        cout<<cur->x<<" "<<cur->y<<endl;
        cur=cur->next;
    }
    return 0;
}