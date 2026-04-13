#include "static_service.h"
#include "card_service.h"
#include "billing_service.h"
#include "money_service.h"
#include<iostream>
#include<string>
using namespace std;

static bool starts_with(const string& s, const string& prefix) {
	return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

//查询统计功能菜单
void sum_up_menu() {
	while (true) {
		//打印菜单
		cout << "\n----------查询统计----------\n";
		cout << "1.消费记录查询\n";
		cout << "2.统计总营业额\n";
		cout << "3.统计月营业额\n";
		cout << "4.统计日营业额\n";
		cout << "0.返回上级菜单\n";
		cout << "请选择菜单项编号(0~4):";

		//处理业务
		string choice;
		cin >> choice;
		if (choice == "0") { cout << endl;return; }
		else if (choice == "1") sum_up_card();
		else if (choice == "2") sum_up_all();
		else if (choice == "3") sum_up_month();
		else if (choice == "4") sum_up_day();
		else {
			cout << "错误，请再次输入!\n";
		}
	}
}

//查询统计卡的消费记录
void sum_up_card()
{
	//打印菜单
	cout << "\n----------查询卡消费记录----------\n";
	cout << "请输入卡号：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

	//查找卡
	string card_name;
	cin >> card_name;
	card_node* card_node = card_head;
	bool is_find = false;
	while (card_node != nullptr) {
		if (card_node->data.aName == card_name) {
			is_find = true;
			break;
		}
		card_node = card_node->next;
	}
	if (!is_find) {
		cout << "卡号不存在！返回上级菜单！\n";
		return;
	}

	//总消费数据
	double cost_logon = 0;     //上机消费
	double cost_charge = 0;    //充值消费
	double cost_back = 0;      //退费金额
	double cost_all = 0;       //总消费

	//查找计费信息
	cout << "\n----------计费信息如下----------\n";
	billing_node* billing_node = billing_head;
	is_find = false;
	while (billing_node != nullptr) {
		if (billing_node->data.aCardName == card_name) {
			is_find = true;
			break;
		}
		billing_node = billing_node->next;
	}
	if (!is_find) {
		cout << "该卡没有计费记录！\n";
	}

	//打印计费信息
	if(is_find) cout << "上机时间\t\t" << "下机时间\t\t" << "消费金额\n";
	while (billing_node != nullptr) {
		if (billing_node->data.aCardName == card_name) {
			cout << billing_node->data.tStart << "\t" << billing_node->data.tEnd << "\t"
				<< billing_node->data.fAmount << "\t\n";
			cost_logon += billing_node->data.fAmount;
		}
		billing_node = billing_node->next;
	}

	//查找充值退费信息
	cout << "\n----------充值退费信息如下----------\n";
	money_node* money_node = money_head;
	is_find = false;
	while (money_node != nullptr) {
		if (money_node->data.aCardName == card_name) {
			is_find = true;
			break;
		}
		money_node = money_node->next;
	}
	if (!is_find) {
		cout << "该卡没有充值退费记录！\n";
	}

	//打印计费信息
	if(is_find) cout << "充值/退费\t" << "充值/退费时间\t\t" << "充值/退费金额\n";
	while (money_node != nullptr) {
		if (money_node->data.aCardName == card_name) {
			cout << ((money_node->data.nStatus==1) ? ("充值"):("退费")) << "\t\t" 
				<< money_node->data.time << "\t"
				<< money_node->data.amount << "\t\n";
			if (money_node->data.nStatus == 1) cost_charge += money_node->data.amount;
			else if (money_node->data.nStatus == 0) cost_back += money_node->data.amount;
		}
		money_node = money_node->next;
	}

	//打印总消费信息
	cost_all = cost_charge - cost_back;
	cout << "\n----------总消费信息如下----------\n";
	cout << "总上机消费\t" << "总充值金额\t" << "总退费金额\t" << "净充值(充值-退费)\t" << "余额\n";
	cout << cost_logon << "\t\t" << cost_charge << "\t\t" << cost_back << "\t\t" << cost_all
		<< "\t\t\t" << card_node->data.fBalance << endl << endl;

	return;
}

//查询统计总营业额
void sum_up_all()
{
	cout << "\n----------总营业额信息如下----------\n";
	cout << "总上机金额\t" << "总充值金额\t" << "总退费金额\t" << "总盈利(充值-退费)\n";

	//总营业额数据
	double money_logon = 0;     //总上机金额
	double money_charge = 0;    //总充值金额
	double money_back = 0;      //总退费金额
	double money_profit = 0;    //总盈利（充值-退费）

	//扫描上机数据
	billing_node* billing_node = billing_head;
	while (billing_node != nullptr) {
		money_logon += billing_node->data.fAmount;
		billing_node = billing_node->next;
	}

	//扫描充值退费信息数据
	money_node* money_node = money_head;
	while (money_node != nullptr) {
		if (money_node->data.nStatus == 1) money_charge += money_node->data.amount;
		else if (money_node->data.nStatus == 0) money_back += money_node->data.amount;
		money_node = money_node->next;
	}

	//打印信息
	money_profit = money_charge - money_back;
	cout << money_logon << "\t\t" << money_charge << "\t\t" << money_back << "\t\t" << money_profit << endl << endl;

	return;
}

//查询统计月营业额
void sum_up_month()
{
	cout << "\n请输入月份：YYYY-MM\b\b\b\b\b\b\b";
	string month;
	cin >> month;
	if (month.size() != 7 || month[4] != '-') {
		cout << "输入格式错误！\n";
		return;
	}

	cout << "\n----------" << month << "月营业额信息如下----------\n";
	cout << "总上机金额\t" << "总充值金额\t" << "总退费金额\t" << "总盈利(充值-退费)\n";

	//月营业额数据
	double money_logon = 0;     //总上机金额
	double money_charge = 0;    //总充值金额
	double money_back = 0;      //总退费金额
	double money_profit = 0;    //总盈利（充值-退费）

	const string monthPrefix = month + "-";

	//扫描上机数据（按下机时间tEnd统计）
	billing_node* billing_node = billing_head;
	while (billing_node != nullptr) {
		if (starts_with(billing_node->data.tEnd, monthPrefix)) {
			money_logon += billing_node->data.fAmount;
		}
		billing_node = billing_node->next;
	}

	//扫描充值退费信息数据（按money.time统计）
	money_node* money_node = money_head;
	while (money_node != nullptr) {
		if (starts_with(money_node->data.time, monthPrefix)) {
			if (money_node->data.nStatus == 1) money_charge += money_node->data.amount;
			else if (money_node->data.nStatus == 0) money_back += money_node->data.amount;
		}
		money_node = money_node->next;
	}

	//打印信息
	money_profit = money_charge - money_back;
	cout << money_logon << "\t\t" << money_charge << "\t\t" << money_back << "\t\t" << money_profit << "\n\n";

	return;
}

//查询统计日营业额
void sum_up_day()
{
	cout << "\n请输入日期：YYYY-MM-DD\b\b\b\b\b\b\b\b\b\b";
	string day;
	cin >> day;
	if (day.size() != 10 || day[4] != '-' || day[7] != '-') {
		cout << "输入格式错误！\n";
		return;
	}

	cout << "\n----------" << day << " 日营业额信息如下----------\n";
	cout << "总上机金额\t" << "总充值金额\t" << "总退费金额\t" << "总盈利(充值-退费)\n";

	//日营业额数据
	double money_logon = 0;     //总上机金额
	double money_charge = 0;    //总充值金额
	double money_back = 0;      //总退费金额
	double money_profit = 0;    //总盈利（充值-退费）

	const string dayPrefix = day + " ";

	//扫描上机数据（按下机时间tEnd统计）
	billing_node* billing_node = billing_head;
	while (billing_node != nullptr) {
		if (starts_with(billing_node->data.tEnd, dayPrefix)) {
			money_logon += billing_node->data.fAmount;
		}
		billing_node = billing_node->next;
	}

	//扫描充值退费信息数据（按money.time统计）
	money_node* money_node = money_head;
	while (money_node != nullptr) {
		if (starts_with(money_node->data.time, dayPrefix)) {
			if (money_node->data.nStatus == 1) money_charge += money_node->data.amount;
			else if (money_node->data.nStatus == 0) money_back += money_node->data.amount;
		}
		money_node = money_node->next;
	}

	//打印信息
	money_profit = money_charge - money_back;
	cout << money_logon << "\t\t" << money_charge << "\t\t" << money_back << "\t\t" << money_profit << "\n\n";

	return;
}