/*
【问题描述】
完成成绩输入后，给成绩评定等级。   
小于100且大于等于90为优秀，
小于90且大于等于80为良好，
小于80且大于等于70为中等，
小于70且大于等于60为及格，
小于60且大于等于0为不及格。
分数大于100或小于0提示输入错误。
务必使用if+switch语句完成本题。禁止全部使用if语句完成。
【样例输入】
65
【样例输出】
及格
*/
#include <iostream>
using namespace std;
int main() {
    int score;
    cin >> score;
    if (score < 0 || score > 100) {
        cout << "输入错误" << endl;
    } else {
        switch (score / 10) {
            case 10:
            case 9:
                cout << "优秀" << endl;
                break;
            case 8:
                cout << "良好" << endl;
                break;
            case 7:
                cout << "中等" << endl;
                break;
            case 6:
                cout << "及格" << endl;
                break;
            default:
                cout << "不及格" << endl;
                break;
        }
    }
    return 0;
}