#include <iostream>
using namespace std;
struct Node {
    int x, y;       // 坐标
    Node* next;     // 指向下一个节点的指针
};
int main() {
    int n;
    if (!(cin >> n)) return 0;
    Node* head = nullptr; // 初始化头指针为空
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        Node* newNode = new Node;
        newNode->x = x;
        newNode->y = y;
        newNode->next = head; // 新节点的 next 指向当前头节点
        head = newNode;       // 头指针移动到新节点
    }
    int tx, ty;
    cin >> tx >> ty;
    bool found = false;
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->x == tx && cur->y == ty) {
            found = true;
            break;
        }
        cur = cur->next;
    }
    if (found) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}