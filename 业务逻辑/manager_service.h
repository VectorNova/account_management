#ifndef MANAGER_SERVICE
#define MANAGER_SERVICE

//进入管理员菜单的密匙
extern int password = -1;  
//管理员主菜单
void manager_menu();
//管理员验证
bool manager_verify();

#endif