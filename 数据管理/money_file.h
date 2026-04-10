#ifndef MONEY_FILE
#define MONEY_FILE
#include "../公共头文件（数据结构）/model.h"
#include "../业务逻辑/money_service.h"

//将充值退费信息存入文件
void save_money_to_file(money_node* money_head);
//从文件中读取充值退费信息
void load_money_to_node(money_node** money_head);

#endif