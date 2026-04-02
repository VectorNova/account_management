#ifndef BILLING_FILE
#define BILLING_FILE
#include "../公共头文件（数据结构）/model.h"

//将计费信息存入文件
void save_billing_to_file(billing_node* head);
//从文件读取计费信息到链表
void load_billing_to_node(billing_node** head);

#endif