#include "manager_service.h"
#include<iostream>
using namespace std;

//管理员主菜单
void manager_menu()
{
	cout << "\n----------欢迎进入管理员菜单!----------\n";

	//权限验证
	if (!manager_verify()) return;   

	while (true) {
		cout << "\n----------管理员功能列表----------\n";
		cout << "1.添加管理员\n";
		cout << "2.删除管理员\n";
	}
}