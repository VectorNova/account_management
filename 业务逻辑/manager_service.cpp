#include "manager_service.h"
#include "../数据管理/manager_file.h"
#include<iostream>
#include<string>
using namespace std;

string passkey;

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
		cout << "5.查看修改数据\n";
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
	if (manager_name == "manager") return true;
	else return false;
}

//添加管理员
void add_manager()
{
	return;
}

//删除管理员
void delete_manager()
{
	return;
}

//查看管理员列表
void manager_list()
{
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

//修改数据
void change_data()
{
	return;
}