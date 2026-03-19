#include "../公共头文件（数据结构）/model.h"
#include "card_file.h"
#include<fstream>
#include<iostream>
using namespace std;

//将卡信息存入文件
void save_cards_to_file(card_node* head) {
	ofstream fout;
	fout.open("card_data.txt");
	if (!fout.is_open()) return;
	card_node* ptr = head;
    while (ptr != nullptr) {
		fout << ptr->data.aName << '\t'
			<< ptr->data.aPwd << '\t'
			<< ptr->data.nStatus << '\t'
			<< (ptr->data.tStart.empty() ? "-" : ptr->data.tStart) << '\t'
			<< (ptr->data.tEnd.empty() ? "-" : ptr->data.tEnd) << '\t'
			<< ptr->data.fTotalUse << '\t'
			<< (ptr->data.tLast.empty() ? "-" : ptr->data.tLast) << '\t'
			<< ptr->data.nUseCount << '\t'
			<< ptr->data.fBalance << '\t'
			<< ptr->data.nDel << endl;
		ptr = ptr->next;
	}
	fout.close();
}

//读取卡信息到链表
void load_cards_to_node(card_node* & head) {
  ifstream fin;
  fin.open("card_data.txt");
  if (!fin.is_open()) return;

  head = nullptr;
  card_node* tail = nullptr;

  string aName;
  string aPwd;
  int nStatus;
  string tStartStr;
  string tEndStr;
  float fTotalUse;
  string tLastStr;
  int nUseCount;
  float fBalance;
  int nDel;

  while (fin >> aName >> aPwd >> nStatus >> tStartStr >> tEndStr >> fTotalUse >> tLastStr >> nUseCount >> fBalance >> nDel) {
	  card_node* node = new card_node;
	  node->data.aName = aName;
	  node->data.aPwd = aPwd;
	  node->data.nStatus = nStatus;
     node->data.tStart = (tStartStr == "-" ? "" : tStartStr);
	  node->data.tEnd = (tEndStr == "-" ? "" : tEndStr);
	  node->data.fTotalUse = fTotalUse;
   node->data.tLast = (tLastStr == "-" ? "" : tLastStr);
	  node->data.nUseCount = nUseCount;
	  node->data.fBalance = fBalance;
	  node->data.nDel = nDel;
	  node->next = nullptr;

	  if (head == nullptr) {
		  head = node;
		  tail = node;
	  } else {
		  tail->next = node;
		  tail = node;
	  }
  }
}