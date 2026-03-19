#ifndef CARD_FILE
#define CARD_FILE
#include "../公共头文件（数据结构）/model.h"

//将卡的数据存入文件
void save_cards_to_file(card_node* head);
//读取卡信息到链表
void load_cards_to_node(card_node* & head);

#endif