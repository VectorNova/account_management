#ifndef BILLING_SERVICE
#define BILLING_SRVICE

#include "../公共头文件（数据结构）/model.h"

extern billing_node* billing_head;
extern double price;       //上机费用（每一秒XX元）

void log_on();    //上机
void log_out();   //下机

#endif