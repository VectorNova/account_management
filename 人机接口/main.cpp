#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<windows.h>
#include "model.h"
#include "menu.h"
using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	cout << "欢迎进入计费管理系统" << endl;
	int choice;
	while (true) {
		OutputMenu();
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

//测试