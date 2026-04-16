#include "manager_file.h"
#include<iostream>
#include<fstream>
using namespace std;

//存储管理员菜单密匙到文件
void save_passkey_to_file(const std::string& passkey)
{
	ofstream fout;
	fout.open("manager_passkey.txt");
	if (!fout.is_open()) return;
	fout << passkey;
	fout.close();
	return;
}

//存储上机费用到文件
void save_price_to_file(double price)
{
	ofstream fout;
	fout.open("billing_price.txt");
	if (!fout.is_open()) return;
	fout << price;
	fout.close();
	return;
}

//从文件读取上机费用
void load_price_to_file(double& price)
{
	ifstream fin;
	fin.open("billing_price.txt");
	if (!fin.is_open()) return;
	fin >> price;
	fin.close();
	return;
}


//从文件读取管理员菜单密匙
void load_passkey_to_file(std::string& passkey)
{
	ifstream fin;
	fin.open("manager_passkey.txt");
	if (!fin.is_open()) return;
	fin >> passkey;
	fin.close();
	return;
}

//存储管理员列表到文件
void save_manager_to_file(manager_node* head)
{
	ofstream fout;
	fout.open("manager_list.txt");
	if (!fout.is_open()) return;
	manager_node* node = head;
	while (node != nullptr) {
		fout << node->name << endl;
		node = node->next;
	}
	fout.close();
	return;
}

//从文件读取管理员列表
void load_manager_to_file(manager_node** head)
{
	ifstream fin;
	fin.open("manager_list.txt");
	if (!fin.is_open()) return;
    *head = nullptr;
	manager_node* tail = nullptr;
	string name;
	while (fin >> name) {
		manager_node* node = new manager_node;
		node->name = name;
		node->next = nullptr;
		if (*head == nullptr) {
			*head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}
}