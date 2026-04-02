#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H

#include "../公共头文件（数据结构）/model.h"

extern card_node* card_head;    //全局变量：链表头
const int Card_Life = 2;        //卡的有效期（年份）

void adding_card();             //添加卡服务
void searching_card();          //查询卡服务

#endif