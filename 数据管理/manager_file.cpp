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