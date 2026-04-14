#ifndef MANAGER_SERVICE
#define MANAGER_SERVICE
#include <string>
#include "../公共头文件（数据结构）/model.h"

//进入管理员菜单的密匙
extern std::string passkey;
//管理员列表
extern manager_node* manager_head;

//管理员主菜单
void manager_menu();
//管理员验证
bool manager_verify();
//添加管理员
void add_manager();
//删除管理员
void delete_manager();
//查看管理员列表
void manager_list();
//修改进入管理员菜单的密匙
void change_passkey();
//修改数据
void change_data();

#endif