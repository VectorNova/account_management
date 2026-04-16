#ifndef MANAGER_FILE
#define MANAGER_FILE
#include "../公共头文件（数据结构）/model.h"
#include<string>

//存储管理员菜单密匙到文件
void save_passkey_to_file(const std::string& passkey);
//从文件读取管理员菜单密匙
void load_passkey_to_file(std::string& passkey);
//存储上机费用到文件
void save_price_to_file(double price);
//从文件读取上机费用
void load_price_to_file(double& price);
//存储管理员列表到文件
void save_manager_to_file(manager_node* head);
//从文件读取管理员列表
void load_manager_to_file(manager_node** head);

#endif