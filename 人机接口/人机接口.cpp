#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<windows.h>
#include<time.h>
using namespace std;

typedef struct card {
	char aName[18];     //卡号
	char aPwd[8];       //密码
	int nStatus;        //卡状态（0-未上机；1-正在上机；2-已注销）
	time_t tStart;      //开卡时间
	time_t tEnd;        //卡的截止期
	float fTotalUse;    //累计金额
	time_t tLast;       //最后使用日期
	int nUseCount;      //使用次数
	float fBalance;     //余额
	int nDel;           //删除标识（0-未删除；1-删除）
}card;

void print_menu(); //输入菜单函数

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	cout << "欢迎进入计费管理系统" << endl;
	int choice;
	while (true) {
		print_menu();
		cin >> choice;
		switch (choice) {
			case 1:cout << "添加卡" << endl<<endl; break;
			case 2:cout << "查询卡" << endl<<endl; break;
			case 3:cout << "上机" << endl<<endl; break;
			case 4:cout << "下机" << endl<<endl; break;
			case 5:cout << "充值" << endl<<endl; break;
			case 6:cout << "退费" << endl<<endl; break;
			case 7:cout << "查询统计" << endl<<endl; break;
			case 8:cout << "注销卡" << endl<<endl; break;
			case 0:cout << "退出" << endl<<endl; break;
			default:cout << "错误，请再次输入" << endl<<endl;
		}
		if (choice == 0) break;
	}
	return 0;
}

//输入菜单函数
void print_menu()
{
	cout << "---------- 菜单 ----------" << endl;
	cout << "1. 添加卡" << endl << "2. 查询卡" << endl << "3. 上机" << endl;
	cout << "4. 下机" << endl << "5. 充值" << endl << "6. 退费" << endl;
	cout << "7. 查询统计" << endl << "8. 注销卡" << endl << "0. 退出" << endl;
	cout << "请选择菜单项编号 (0-8):";
}