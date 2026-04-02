#include "billing_service.h"
#include "card_service.h"
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
	oss << put_time(&localTm, "%Y-%m-%d %H:%M");
	return oss.str();
}

billing_node* billing_head = NULL;

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
	return;
}