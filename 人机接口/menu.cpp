#include<iostream>
#include<string>
#include "menu.h"
#include "../业务逻辑/service.h"
#include "../业务逻辑/card_service.h"
#include "../数据管理/card_file.h"
#include "../业务逻辑/billing_service.h"
#include "../数据管理/billing_file.h"
#include "../业务逻辑/money_service.h"
#include "../数据管理/money_file.h"
#include "../业务逻辑/manager_service.h"
#include "../数据管理/manager_file.h"
using namespace std;

//显示主菜单函数
void main_menu() {
	cout << "---------- 菜单 ----------" << endl;
	cout << "1. 添加卡" << endl << "2. 查询卡" << endl << "3. 上机" << endl;
	cout << "4. 下机" << endl << "5. 充值" << endl << "6. 退费" << endl;
	cout << "7. 注销卡" << endl << "0. 退出" << endl;
	cout << "请选择菜单项编号 (0-7):";
}

//显示菜单函数
void OutputMenu()
{
	cout << "欢迎进入计费管理系统" << endl;

	//读取卡信息文件到链表（文本文件或二进制文件）
    load_cards_to_node(&card_head);
	//load_cards_to_node_binary(&card_head);

	//读取计费信息文件到链表
    load_billing_to_node(&billing_head);

	//读取充值退费信息文件到链表
	load_money_to_node(&money_head);

	//读取管理员密匙文件
	load_passkey_to_file(passkey);

	//读取上机费用
	load_price_to_file(price);

	//读取管理员列表
	load_manager_to_file(&manager_head);

	string choice;
	while (true) {
		main_menu();
		cin >> choice;
		if (choice == "0") break;
		do_service(choice);
	}
}