#ifndef BILLING_SERVICE
#define BILLING_SRVICE

#include "../公共头文件（数据结构）/model.h"

extern billing_node* billing_head;
const double price = 0.1;       //上机费用（每一秒0.1元）

void log_on();    //上机
void log_out();   //下机

#endif