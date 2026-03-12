#include "service.h"
#include "card_service.h"
#include<iostream>
#include<string>
using namespace std;

//处理业务函数
void do_service(const string& choice) {
	if (choice == "1") adding_card();
	else if (choice == "2") searching_card();
	else if (choice == "3") cout << "上机" << endl << endl;
	else if (choice == "4") cout << "下机" << endl << endl;
	else if (choice == "5") cout << "充值" << endl << endl;
	else if (choice == "6") cout << "退费" << endl << endl;
	else if (choice == "7") cout << "查询统计" << endl << endl;
	else if (choice == "8") cout << "注销卡" << endl << endl;
	else if (choice == "0") cout << "退出" << endl << endl;
	else cout << "错误，请再次输入" << endl << endl;
}