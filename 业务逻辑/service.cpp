#include "service.h"
#include "card_service.h"
#include "billing_service.h"
#include "money_service.h"
#include<iostream>
#include<string>
using namespace std;

//处理业务函数
void do_service(const string& choice) {
	if (choice == "1") adding_card();
	else if (choice == "2") searching_card();
	else if (choice == "3") log_on();
	else if (choice == "4") log_out();
	else if (choice == "5") recharge();
	else if (choice == "6") refund();
	else if (choice == "7") cout << "查询统计" << endl << endl;
	else if (choice == "8") cancel_card();
	else if (choice == "0") cout << "退出" << endl << endl;
	else cout << "错误，请再次输入" << endl << endl;
}