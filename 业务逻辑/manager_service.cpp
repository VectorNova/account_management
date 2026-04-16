#include "manager_service.h"
#include "../数据管理/manager_file.h"
#include "card_service.h"
#include "billing_service.h"
#include "money_service.h"
#include "../数据管理/card_file.h"
#include "../数据管理/billing_file.h"
#include "../数据管理/money_file.h"
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

string passkey;
manager_node* manager_head = nullptr;

static void list_cards()
{
	cout << "\n----------卡信息列表----------\n";
	cout << left << setw(20) << "卡号"
		<< setw(10) << "密码"
		<< setw(8) << "状态"
		<< setw(10) << "余额"
		<< setw(12) << "累计使用"
		<< setw(10) << "使用次数"
		<< setw(20) << "开卡时间"
		<< setw(20) << "截止期"
		<< setw(20) << "最后使用"
		<< setw(8) << "删除" << endl;
	if (card_head == nullptr) {
		cout << "暂无卡信息。\n";
		return;
	}
	for (card_node* node = card_head; node != nullptr; node = node->next) {
		cout << left << setw(20) << node->data.aName
			<< setw(10) << node->data.aPwd
			<< setw(8) << node->data.nStatus
			<< setw(10) << fixed << setprecision(2) << node->data.fBalance
			<< setw(12) << fixed << setprecision(2) << node->data.fTotalUse
			<< setw(10) << node->data.nUseCount
			<< setw(20) << (node->data.tStart.empty() ? "-" : node->data.tStart)
			<< setw(20) << (node->data.tEnd.empty() ? "-" : node->data.tEnd)
			<< setw(20) << (node->data.tLast.empty() ? "-" : node->data.tLast)
			<< setw(8) << node->data.nDel << endl;
	}
}

static void edit_card()
{
	cout << "\n----------修改卡信息----------\n";
	cout << "请输入要修改的卡号：";
	string card_name;
	cin >> card_name;
	card_node* node = card_head;
	while (node != nullptr && node->data.aName != card_name) {
		node = node->next;
	}
	if (node == nullptr) {
		cout << "未找到该卡信息。\n";
		return;
	}

	cout << "输入-表示不修改。\n";
	cout << "新密码：";
	string new_pwd;
	cin >> new_pwd;
	if (new_pwd != "-") node->data.aPwd = new_pwd;

	cout << "新状态(0未上机/1上机/2注销，-1不修改)：";
	int new_status;
	cin >> new_status;
	if (new_status >= 0) node->data.nStatus = new_status;

	cout << "新余额(-1不修改)：";
	double new_balance;
	cin >> new_balance;
	if (new_balance >= 0) node->data.fBalance = new_balance;

	cout << "新累计使用(-1不修改)：";
	double new_total_use;
	cin >> new_total_use;
	if (new_total_use >= 0) node->data.fTotalUse = new_total_use;

	cout << "新使用次数(-1不修改)：";
	int new_use_count;
	cin >> new_use_count;
	if (new_use_count >= 0) node->data.nUseCount = new_use_count;

	cout << "新截止期(YYYY-MM-DD HH:MM:SS，输入-不修改)：";
	string new_end;
	cin >> new_end;
	if (new_end != "-") node->data.tEnd = new_end;

	cout << "新最后使用时间(YYYY-MM-DD HH:MM:SS，输入-不修改)：";
	string new_last;
	cin >> new_last;
	if (new_last != "-") node->data.tLast = new_last;

	cout << "删除标识(0/1，-1不修改)：";
	int new_del;
	cin >> new_del;
	if (new_del >= 0) node->data.nDel = new_del;

	save_cards_to_file(card_head);
	cout << "修改完成。\n";
}

static void list_billing()
{
	cout << "\n----------计费信息列表----------\n";
	cout << left << setw(6) << "序号"
		<< setw(20) << "卡号"
		<< setw(20) << "上机时间"
		<< setw(20) << "下机时间"
		<< setw(10) << "消费"
		<< setw(8) << "状态"
		<< setw(6) << "删除" << endl;
	if (billing_head == nullptr) {
		cout << "暂无计费信息。\n";
		return;
	}
	int index = 1;
	for (billing_node* node = billing_head; node != nullptr; node = node->next) {
		cout << left << setw(6) << index++
			<< setw(20) << node->data.aCardName
			<< setw(20) << (node->data.tStart.empty() ? "-" : node->data.tStart)
			<< setw(20) << (node->data.tEnd.empty() ? "-" : node->data.tEnd)
			<< setw(10) << fixed << setprecision(2) << node->data.fAmount
			<< setw(8) << node->data.nStatus
			<< setw(6) << node->data.nDel << endl;
	}
}

static billing_node* billing_by_index(int index)
{
	if (index <= 0) return nullptr;
	int current = 1;
	for (billing_node* node = billing_head; node != nullptr; node = node->next) {
		if (current == index) return node;
		current++;
	}
	return nullptr;
}

static void edit_billing()
{
	list_billing();
	cout << "请输入要修改的计费记录序号：";
	int index;
	cin >> index;
	billing_node* node = billing_by_index(index);
	if (node == nullptr) {
		cout << "未找到该计费记录。\n";
		return;
	}

	cout << "输入-表示不修改。\n";
	cout << "新卡号：";
	string new_card;
	cin >> new_card;
	if (new_card != "-") node->data.aCardName = new_card;

	cout << "新上机时间(YYYY-MM-DD HH:MM:SS)：";
	string new_start;
	cin >> new_start;
	if (new_start != "-") node->data.tStart = new_start;

	cout << "新下机时间(YYYY-MM-DD HH:MM:SS)：";
	string new_end;
	cin >> new_end;
	if (new_end != "-") node->data.tEnd = new_end;

	cout << "新消费金额(-1不修改)：";
	double new_amount;
	cin >> new_amount;
	if (new_amount >= 0) node->data.fAmount = new_amount;

	cout << "新状态(0未结算/1已结算，-1不修改)：";
	int new_status;
	cin >> new_status;
	if (new_status >= 0) node->data.nStatus = new_status;

	cout << "删除标识(0/1，-1不修改)：";
	int new_del;
	cin >> new_del;
	if (new_del >= 0) node->data.nDel = new_del;

	save_billing_to_file(billing_head);
	cout << "修改完成。\n";
}

static void list_money()
{
	cout << "\n----------充值退费信息列表----------\n";
	cout << left << setw(6) << "序号"
		<< setw(8) << "类型"
		<< setw(20) << "卡号"
		<< setw(20) << "时间"
		<< setw(10) << "金额"
		<< setw(10) << "余额" << endl;
	if (money_head == nullptr) {
		cout << "暂无充值退费信息。\n";
		return;
	}
	int index = 1;
	for (money_node* node = money_head; node != nullptr; node = node->next) {
		cout << left << setw(6) << index++
			<< setw(8) << node->data.nStatus
			<< setw(20) << node->data.aCardName
			<< setw(20) << (node->data.time.empty() ? "-" : node->data.time)
			<< setw(10) << fixed << setprecision(2) << node->data.amount
			<< setw(10) << fixed << setprecision(2) << node->data.fBalance << endl;
	}
}

static money_node* money_by_index(int index)
{
	if (index <= 0) return nullptr;
	int current = 1;
	for (money_node* node = money_head; node != nullptr; node = node->next) {
		if (current == index) return node;
		current++;
	}
	return nullptr;
}

static void edit_money()
{
	list_money();
	cout << "请输入要修改的记录序号：";
	int index;
	cin >> index;
	money_node* node = money_by_index(index);
	if (node == nullptr) {
		cout << "未找到该记录。\n";
		return;
	}

	cout << "输入-表示不修改。\n";
	cout << "新类型(0退费/1充值/2注销，-1不修改)：";
	int new_status;
	cin >> new_status;
	if (new_status >= 0) node->data.nStatus = new_status;

	cout << "新卡号：";
	string new_card;
	cin >> new_card;
	if (new_card != "-") node->data.aCardName = new_card;

	cout << "新时间(YYYY-MM-DD HH:MM:SS)：";
	string new_time;
	cin >> new_time;
	if (new_time != "-") node->data.time = new_time;

	cout << "新金额(-1不修改)：";
	double new_amount;
	cin >> new_amount;
	if (new_amount >= 0) node->data.amount = new_amount;

	cout << "新余额(-1不修改)：";
	double new_balance;
	cin >> new_balance;
	if (new_balance >= 0) node->data.fBalance = new_balance;

	save_money_to_file(money_head);
	cout << "修改完成。\n";
}

static void edit_price()
{
	cout << "\n----------上机费用设置----------\n";
	cout << "当前上机费用(每秒)：" << price << "\n";
	cout << "请输入新的上机费用：";
	cin >> price;
   save_price_to_file(price);
	cout << "修改成功！新的上机费用为：" << price << "\n";
}

//管理员主菜单
void manager_menu()
{
	cout << "\n----------欢迎进入管理员菜单----------\n";

	//权限验证
	if (!manager_verify()) {
		cout << "权限验证失败！你没有权限访问管理员菜单！\n";
		cout << "即将返回计费管理系统……\n\n";
		return;
	}
	cout << "权限验证成功！即将进入管理员菜单！\n";

	while (true) {
		//打印菜单
		cout << "\n----------管理员功能列表----------\n";
		cout << "1.添加管理员\n";
		cout << "2.删除管理员\n";
		cout << "3.查看管理员列表\n";
		cout << "4.修改进入管理员菜单的密匙\n";
		cout << "5.查看/修改数据\n";
		cout << "0.返回计费管理系统\n";
		cout << "请输入菜单编号(0~5):";

		//处理业务
		string choice;
		cin >> choice;
		if (choice == "0") { cout << endl; return; }
		else if (choice == "1") add_manager();
		else if (choice == "2") delete_manager();
		else if (choice == "3") manager_list();
		else if (choice == "4") change_passkey();
		else if (choice == "5") change_data();
		else {
			cout << "错误！请输入正确编号！\n";
			continue;
		}
	}
}

//管理员验证
bool manager_verify()
{
	cout << "请输入管理员编号：";
	string manager_name;
	cin >> manager_name;

	//固定终端管理员，不可删除
	if (manager_name == "manager") return true;
	
	//寻找是否存在该管理员
	manager_node* node = manager_head;
	bool is_exist = false;
	while (node != nullptr) {
		if (node->name == manager_name) {
			is_exist = true;
			break;
		}
		node = node->next;
	}
	return is_exist;
}

//添加管理员
void add_manager()
{
	//打印菜单
	cout << "\n----------添加管理员----------\n";
	cout << "请输入要添加的管理员编号：";
	string name;
	cin >> name;

	//检查是否已经存在该管理员
	manager_node* node = manager_head;
	manager_node* tail = node;
	while (node != nullptr) {
		if (node->name == name) {
			cout << "错误！已经存在该管理员！\n";
			cout << "即将返回管理员菜单\n";
			return;
		}
		tail = node;
		node = node->next;
	}

	//输出添加成功菜单
	cout << "添加成功！新的管理员编号为：" << name << endl;

	//添加该管理员到链表
	manager_node* newNode = new manager_node;
	newNode->name = name;
	newNode->next = nullptr;
	if (tail == nullptr) manager_head = newNode;
	else tail->next = newNode;
	
	//保存到文件
	save_manager_to_file(manager_head);

	return;
}

//删除管理员
void delete_manager()
{
	//打印菜单
	cout << "\n----------删除管理员----------\n";
	cout << "请输入要删除的管理员编号：";
	string name;
	cin >> name;

	//终端不可删除
	if (name == "manager") {
		cout << "错误！终端管理员不可删除！\n";
		cout << "即将返回管理员列表\n";
		return;
	}

	//检测是否存在该管理员
	manager_node* node = manager_head;
	bool is_exist = false;
	while (node != nullptr) {
		if (node->name == name) {
			is_exist = true;
			break;
		}
		node = node->next;
	}
	if (!is_exist) {
		cout << "错误！不存在该管理员！\n";
		cout << "即将返回管理员列表\n";
		return;
	}

	//删除管理员
	if (node == manager_head) {
		manager_head = node->next;
		delete node;
	}
	else {
		manager_node* pre = manager_head;
		while (pre->next != node) pre = pre->next;
		pre->next = node->next;
		delete node;
	}

	//输出删除成功菜单
	cout << "删除成功！删除的管理员编号为：" << name << endl;
	
	//存储到文件里
	save_manager_to_file(manager_head);

	return;
}

//查看管理员列表
void manager_list()
{
	cout << "\n----------管理员列表----------\n";
	int num = 1;
	cout << num << ".manager(终端，不可删除）\n";
	manager_node* node = manager_head;
	if (node == nullptr) {
		cout << "仅存在终端，无其他新添管理员！\n";
		return;
	}
	while (node != nullptr) {
		cout << ++num << "." << node->name << endl;
		node = node->next;
	}
	return;
}

//修改进入管理员菜单的密匙
void change_passkey()
{
	cout << "\n----------修改进入管理员菜单的密匙----------\n";
	cout << "当前的密匙为：" << passkey << endl;
	cout << "请输入要修改成的新密匙:";
	string new_passkey;
	cin >> new_passkey;
	passkey = new_passkey;
	cout << "修改成功！新的密匙为：" << passkey << endl << endl;

	//存储新密匙到文件
	save_passkey_to_file(passkey);

	return;
}

//查看/修改数据
void change_data()
{
 string choice;
	while (true) {
		cout << "\n----------查看/修改数据----------\n";
		cout << "1.查看所有卡信息\n";
		cout << "2.修改卡信息\n";
		cout << "3.查看所有计费信息\n";
		cout << "4.修改计费信息\n";
		cout << "5.查看所有充值退费信息\n";
		cout << "6.修改充值退费信息\n";
      cout << "7.查看/修改上机费用\n";
		cout << "0.返回管理员菜单\n";
        cout << "请输入菜单编号(0~7):";
		cin >> choice;
		if (choice == "0") return;
		else if (choice == "1") list_cards();
		else if (choice == "2") edit_card();
		else if (choice == "3") list_billing();
		else if (choice == "4") edit_billing();
		else if (choice == "5") list_money();
		else if (choice == "6") edit_money();
       else if (choice == "7") edit_price();
		else cout << "错误！请输入正确编号！\n";
	}
}