#include "money_service.h"
#include "card_service.h"
#include<iostream>
using namespace std;

//充值卡功能
void recharge()
{
	//打印菜单
	cout << "\n----------充值----------\n";
	cout << "请输入卡号：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

	//寻找卡
	string card_name;
	cin >> card_name;
	card_node* node = card_head;
	bool is_exist = false;
	while (node != nullptr) {
		if (node->data.aName == card_name) { is_exist = true; break; }
		node = node->next;
	}
	if (!is_exist) {
		cout << "卡号不存在！\n";
		return;
	}

	//检测该卡是否已经注销
	if (node->data.nStatus == 2) {
		cout << "该卡已经注销！\n";
		return;
	}

	//检测密码是否正确
	cout << "请输入密码：________\b\b\b\b\b\b\b\b";
	string password;
	cin >> password;
	if (node->data.aPwd != password) {
		cout << "密码错误！\n";
		return;
	}

	//读取输入金额
	cout << "请输入充值的金额：";
	double recharge_money;
	cin >> recharge_money;
	node->data.fBalance += recharge_money;

	//打印充值信息
	cout << "\n----------充值信息如下----------\n";
	cout << "卡号\t" << "充值数额\t" << "余额\n";
	cout << card_name << '\t' << recharge_money << "\t\t" << node->data.fBalance << endl;
	return;
}

//退费功能
void refund()
{

}