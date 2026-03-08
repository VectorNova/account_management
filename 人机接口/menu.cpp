#include<iostream>
#include "menu.h"
using namespace std;

//输入菜单函数
void OutputMenu()
{
	cout << "---------- 菜单 ----------" << endl;
	cout << "1. 添加卡" << endl << "2. 查询卡" << endl << "3. 上机" << endl;
	cout << "4. 下机" << endl << "5. 充值" << endl << "6. 退费" << endl;
	cout << "7. 查询统计" << endl << "8. 注销卡" << endl << "0. 退出" << endl;
	cout << "请选择菜单项编号 (0-8):";
}