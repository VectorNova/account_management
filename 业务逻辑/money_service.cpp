#include "money_service.h"
#include "card_service.h"
#include "../数据管理/money_file.h"
#include "../数据管理/card_file.h"
#include<iostream>
#include<iomanip>
#include<sstream>
#include<ctime>
using namespace std;

static string current_date_string() {
	time_t now = time(NULL);
	tm localTm = {};
	localtime_s(&localTm, &now);
	ostringstream oss;
	oss << put_time(&localTm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

money_node* money_head = NULL;

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
		cout << "卡号不存在！\n\n";
		return;
	}

	//检测该卡是否已经注销
	if (node->data.nStatus == 2) {
		cout << "该卡已经注销！\n\n";
		return;
	}

	//检测密码是否正确
	cout << "请输入密码：________\b\b\b\b\b\b\b\b";
	string password;
	cin >> password;
	if (node->data.aPwd != password) {
		cout << "密码错误！\n\n";
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
	cout << card_name << '\t' << recharge_money << "\t\t" << node->data.fBalance << endl << endl;

    //存入充值退费信息链表
	money_node* moneyNew = new money_node;
	moneyNew->data.nStatus = 1;
	moneyNew->data.aCardName = card_name;
	moneyNew->data.time = current_date_string();
	moneyNew->data.amount = recharge_money;
	moneyNew->data.fBalance = node->data.fBalance;
	moneyNew->next = nullptr;

	if (money_head == nullptr) {
		money_head = moneyNew;
	}
	else {
		money_node* tail = money_head;
		while (tail->next != nullptr) tail = tail->next;
		tail->next = moneyNew;
	}

	//将充值信息存到文件中
	save_money_to_file(money_head);
	save_cards_to_file(card_head);

	return;
}

//退费功能
void refund()
{
	//打印菜单
	cout << "\n----------退费----------\n";
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
		cout << "卡号不存在！\n\n";
		return;
	}

	//检测该卡是否已经注销
	if (node->data.nStatus == 2) {
		cout << "该卡已经注销！\n\n";
		return;
	}

	//检测密码是否正确
	cout << "请输入密码：________\b\b\b\b\b\b\b\b";
	string password;
	cin >> password;
	if (node->data.aPwd != password) {
		cout << "密码错误！\n\n";
		return;
	}

	//检测卡是否正在使用
	if (node->data.nStatus == 1) {
		cout << "\n----------退费信息如下----------\n";
		cout << "该卡正在上机！\n";
		cout << "退费失败，返回上级菜单！\n\n";
		return;
	}

	//检测卡的余额是否大于0
	if (node->data.fBalance <= 0) {
		cout << "\n----------退费信息如下----------\n";
		cout << "余额为0！\n";
		cout << "退费失败，返回上级菜单！\n\n";
		return;
	}

	//所有条件通过，退费
	double money = node->data.fBalance;
	node->data.fBalance = 0.0;

	//打印退费菜单
	cout << "\n----------退费信息如下----------\n";
	cout << "卡号\t退费金额\t余额\n";
	cout << card_name << "\t" << money << "\t\t" << node->data.fBalance << endl << endl;

	//存入充值退费信息链表
	money_node* moneyNew = new money_node;
	moneyNew->data.nStatus = 0;
	moneyNew->data.aCardName = card_name;
	moneyNew->data.time = current_date_string();
	moneyNew->data.amount = money;
	moneyNew->data.fBalance = node->data.fBalance;
	moneyNew->next = nullptr;

	if (money_head == nullptr) {
		money_head = moneyNew;
	}
	else {
		money_node* tail = money_head;
		while (tail->next != nullptr) tail = tail->next;
		tail->next = moneyNew;
	}

	save_money_to_file(money_head);
	save_cards_to_file(card_head);

	return;
}

//注销
void cancel_card()
{
	//打印菜单
	cout << "\n----------注销卡----------\n";
	cout << "请输入注销卡号：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

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
		cout << "卡号不存在！\n\n";
		return;
	}

	//检测该卡是否已经注销
	if (node->data.nStatus == 2) {
		cout << "该卡已经注销！\n\n";
		return;
	}

	//检测密码是否正确
	cout << "请输入密码：________\b\b\b\b\b\b\b\b";
	string password;
	cin >> password;
	if (node->data.aPwd != password) {
		cout << "密码错误！\n\n";
		return;
	}

	//检测卡是否正在使用
	if (node->data.nStatus == 1) {
		cout << "\n该卡正在上机，无法注销！\n\n";
		return;
	}

	//检测余额是否为0
	if (node->data.fBalance > 0) {
		cout << "\n该卡余额不为0，请先退费后再注销！\n\n";
		return;
	}

	//注销卡
	node->data.nStatus = 2;
	cout << "\n----------注销信息如下----------\n";
	cout << "卡号\t状态\t余额\n";
	cout << card_name << '\t' << node->data.nStatus << '\t' << fixed << setprecision(2) << node->data.fBalance << endl << endl;

	//保存卡信息到文件
	save_cards_to_file(card_head);
}