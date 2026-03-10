#include "service.h"
#include<iostream>
using namespace std;

//处理业务函数
void do_service(int choice) {
	switch (choice) {
	case 1:cout << "添加卡" << endl << endl; break;
	case 2:cout << "查询卡" << endl << endl; break;
	case 3:cout << "上机" << endl << endl; break;
	case 4:cout << "下机" << endl << endl; break;
	case 5:cout << "充值" << endl << endl; break;
	case 6:cout << "退费" << endl << endl; break;
	case 7:cout << "查询统计" << endl << endl; break;
	case 8:cout << "注销卡" << endl << endl; break;
	case 0:cout << "退出" << endl << endl; break;
	default:cout << "错误，请再次输入" << endl << endl;
	}
}