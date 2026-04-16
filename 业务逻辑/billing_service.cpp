#include "billing_service.h"
#include "card_service.h"
#include "../数据管理/card_file.h"
#include "../数据管理/billing_file.h"
#include<iostream>
#include<iomanip>
#include<sstream>
#include<ctime>
#include<cmath>
using namespace std;

static string current_date_string() {
	time_t now = time(NULL);
	tm localTm = {};
	localtime_s(&localTm, &now);
	ostringstream oss;
    oss << put_time(&localTm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

billing_node* billing_head = NULL;
double price = 0.1;

//上机
void log_on()
{
	//打印菜单
	cout << endl << "----------上机----------\n";
	cout << "请输入上机卡号（长度为1~18）：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	string card_name;
	cin >> card_name;
	
	//检测是否存在卡号
	card_node* ptr = card_head;
	bool is_exist = false;
	while (ptr != nullptr) {
		if (ptr->data.aName == card_name) { is_exist = true; break; }
		ptr = ptr->next;
	}
	if (!is_exist) {
		cout << "\n卡号不存在！\n\n";
		return;
	}

	//检测密码是否正确
	string password;
	cout << "请输入上机密码（长度为1~8）：________\b\b\b\b\b\b\b\b";
	cin >> password;
	if (password != ptr->data.aPwd) {
		cout << "\n密码错误！\n\n";
		return;
	}

	//检测卡是否超过截止期
	if (!ptr->data.tEnd.empty()) {
		string nowDate = current_date_string();
		if (ptr->data.tEnd < nowDate) {
			cout << "\n该卡已过期！\n\n";
			return;
		}
	}

	//检测卡是否已注销/已删除
	if (ptr->data.nStatus == 2 || ptr->data.nDel == 1) {
		cout << "\n该卡已注销！\n\n";
		return;
	}

	//检测卡状态是否在上机
	if (ptr->data.nStatus == 1) {
		cout << "\n该卡正在上机！\n\n";
		return;
	}
	
	//检测余额是否大于0
	if (ptr->data.fBalance <= 0) {
		cout << "\n余额不足！\n\n";
		return;
	}

	//更新卡的信息
	ptr->data.nStatus = 1;            //将卡的状态调整为上机
	ptr->data.nUseCount++;
	ptr->data.tLast = current_date_string();

	//存入计费信息链表
  billing_node* node = new billing_node;
	node->data.aCardName = ptr->data.aName;
	node->data.tStart = ptr->data.tLast;
	node->data.tEnd = "";
	node->data.fAmount = 0.0;
	node->data.nStatus = 0;
	node->data.nDel = 0;
	node->next = nullptr;

	if (billing_head == nullptr) {
		billing_head = node;
	} else {
		billing_node* tail = billing_head;
		while (tail->next != nullptr) tail = tail->next;
		tail->next = node;
	}

	//打印上机信息
	cout << "\n----------上机信息如下----------\n";
	cout << "卡号\t" << "余额\t" << "上机时间\n";
	cout << node->data.aCardName << '\t' << ptr->data.fBalance << '\t' << node->data.tStart << endl << endl;

	//将计费信息存储到文件
	save_billing_to_file(billing_head);
	return;
}

//下机
void log_out()
{
	//打印菜单
	cout << endl << "----------下机----------\n";
	cout << "请输入下机卡号（长度为1~18）：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	string card_name;
	cin >> card_name;

	//检查卡号是否存在
	card_node* cardPtr = card_head;
	while (cardPtr != nullptr) {
		if (cardPtr->data.aName == card_name) break;
		cardPtr = cardPtr->next;
	}
	if (cardPtr == nullptr) {
		cout << "\n卡号不存在！\n\n";
		return;
	}

	//检测密码是否正确
	string password;
	cout << "请输入下机密码（长度为1~8）：________\b\b\b\b\b\b\b\b";
	cin >> password;
	if (password != cardPtr->data.aPwd) {
		cout << "\n密码错误！\n\n";
		return;
	}

	//检测该卡是否处于上机状态
	if (cardPtr->data.nStatus != 1) {
		cout << "\n该卡未处于上机状态！\n\n";
		return;
	}

	// 找到该卡最新的一条未结算计费记录
	billing_node* billPtr = billing_head;
	billing_node* target = nullptr;
	while (billPtr != nullptr) {
		if (billPtr->data.aCardName == card_name && billPtr->data.nStatus == 0 && billPtr->data.nDel == 0) {
			target = billPtr;
		}
		billPtr = billPtr->next;
	}
	if (target == nullptr) {
		cout << "\n未找到该卡的上机记录，无法下机！\n\n";
		return;
	}

	// 计算费用
	tm startTm = {};
	istringstream startIss(target->data.tStart);
   startIss >> get_time(&startTm, "%Y-%m-%d %H:%M:%S");
	if (startIss.fail()) {
		cout << "\n上机时间格式错误，无法结算！\n\n";
		return;
	}
	startTm.tm_isdst = -1;
	time_t startTime = mktime(&startTm);
	time_t endTime = time(NULL);
	if (endTime < startTime) endTime = startTime;

	double seconds = difftime(endTime, startTime);
	if (seconds < 0) seconds = 0;
	int secondsInt = static_cast<int>(ceil(seconds));
	double amount = secondsInt * price;
	if (amount < 0) amount = 0;
	if (amount > cardPtr->data.fBalance) amount = cardPtr->data.fBalance;

	// 更新计费记录
	target->data.tEnd = current_date_string();
	target->data.fAmount = amount;
	target->data.nStatus = 1;

	// 更新卡信息
	cardPtr->data.nStatus = 0;
	cardPtr->data.fBalance -= amount;
	cardPtr->data.fTotalUse += amount;
	cardPtr->data.tLast = target->data.tEnd;

	cout << "\n----------下机结算信息如下----------\n";
	cout << "卡号\t" << "上机时间\t\t" << "下机时间\t\t" << "消费\t" << "余额\n";
	cout << target->data.aCardName << '\t'
		<< target->data.tStart << "\t"
		<< target->data.tEnd << "\t"
		<< fixed << setprecision(2) << amount << '\t'
		<< fixed << setprecision(2) << cardPtr->data.fBalance << endl << endl;

	// 保存到文件
	save_billing_to_file(billing_head);
	save_cards_to_file(card_head);
}