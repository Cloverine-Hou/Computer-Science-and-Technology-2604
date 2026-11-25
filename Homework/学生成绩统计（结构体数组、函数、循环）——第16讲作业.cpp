/*
【问题描述】利用结构体类型编写程序，实现输入5个学生的学号、姓名、性别、四门课程的成绩，然后计算并输出学生的信息及平均成绩。
要求定义如下的函数分别实现结构体数组数据的录入、平均分的计算、输出结构体数组数据及平均分数组数据的功能：
void Input(struct Student s[], int n);
void Func(struct Student *p, int n, int ave[]);
void Output(STUDENT *p, int n, int ave[]);
请注意：STUDENT是用typedef定义的数据类型
【输入形式】学生的信息
【输出形式】学生的信息及平均成绩
【样例输入】
2018001 zhangsan f 90 80 70 60
2018002 lisi m 88 55 69 72
2018003 wangwu f 63 89 78 85
2018004 zhaoliu m 93 69 67 68
2018005 sunqi m 85 87 68 78
【样例输出】
2018001 zhangsan f 90 80 70 60 75
2018002 lisi m 88 55 69 72 71
2018003 wangwu f 63 89 78 85 79
2018004 zhaoliu m 93 69 67 68 74
2018005 sunqi m 85 87 68 78 80
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
typedef struct Student{
    int id;
    string name;
    char sex;
    int score[4];
}STUDENT;
void Input(STUDENT s[],int n){
    for(int i=0;i<n;i++){
        cin>>s[i].id>>s[i].name>>s[i].sex>>s[i].score[0]>>s[i].score[1]>>s[i].score[2]>>s[i].score[3];
    }
}
void Func(STUDENT *p,int n,int ave[]){
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<4;j++){
            sum+=p[i].score[j];
        }
        ave[i]=(sum+2)/4;
    }
}
void Output(STUDENT *p,int n,int ave[]){
    for(int i=0;i<n;i++){
        cout<<p[i].id<<" "<<p[i].name<<" "<<p[i].sex<<" "<<p[i].score[0]<<" "<<p[i].score[1]<<" "<<p[i].score[2]<<" "<<p[i].score[3]<<" "<<ave[i]<<endl;
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    STUDENT stu[5];
    int ave[5];
    Input(stu,5);
    Func(stu,5,ave);
    Output(stu,5,ave);
    return 0;
}