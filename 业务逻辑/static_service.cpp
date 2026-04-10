#include "static_service.h"
#include "card_service.h"
#include "billing_service.h"
#include "money_service.h"
#include<iostream>
#include<string>
using namespace std;

//查询统计功能菜单
void sum_up_menu() {
	cout << "\n----------查询统计----------\n";
	cout << "1.消费记录查询\n";
	cout << "2.统计总营业额\n";
	cout << "3.统计月营业额\n";
	cout << "0.返回上级菜单\n";

}