#ifndef MANAGER_FILE
#define MANAGER_FILE
#include<string>

//存储管理员菜单密匙到文件
void save_passkey_to_file(const std::string& passkey);
//从文件读取管理员菜单密匙
void load_passkey_to_file(std::string& passkey);

#endif