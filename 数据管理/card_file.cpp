#include "../公共头文件（数据结构）/model.h"
#include "card_file.h"
#include<fstream>
#include<iostream>
using namespace std;

//二进制文件存储字符串辅助函数
static void write_string_binary(ofstream& out, const string& value) {
	unsigned int size = static_cast<unsigned int>(value.size());
	out.write((const char*)&size, sizeof(size));
	out.write(value.c_str(), size);
}

//二进制文件读取字符串辅助函数
static bool read_string_binary(ifstream& in, string& value) {
	unsigned int size = 0;
	if (!in.read((char*)&size, sizeof(size))) return false;
	value.resize(size);
	if (size > 0 && !in.read(&value[0], size)) return false;
	return true;
}

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

	save_cards_to_file_binary(head);
}

//将卡的信息存入文件（二进制文件）
void save_cards_to_file_binary(card_node* head) {
	ofstream bout;
	bout.open("card_data.bin", ios::binary | ios::trunc);
	if (!bout.is_open()) return;

	for (card_node* ptr = head; ptr != nullptr; ptr = ptr->next) {
		write_string_binary(bout, ptr->data.aName);
		write_string_binary(bout, ptr->data.aPwd);
		bout.write(reinterpret_cast<const char*>(&ptr->data.nStatus), sizeof(ptr->data.nStatus));
		write_string_binary(bout, ptr->data.tStart);
		write_string_binary(bout, ptr->data.tEnd);
		bout.write(reinterpret_cast<const char*>(&ptr->data.fTotalUse), sizeof(ptr->data.fTotalUse));
		write_string_binary(bout, ptr->data.tLast);
		bout.write(reinterpret_cast<const char*>(&ptr->data.nUseCount), sizeof(ptr->data.nUseCount));
		bout.write(reinterpret_cast<const char*>(&ptr->data.fBalance), sizeof(ptr->data.fBalance));
		bout.write(reinterpret_cast<const char*>(&ptr->data.nDel), sizeof(ptr->data.nDel));
	}
	bout.close();
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

//读取卡信息到链表（二进制文件）
void load_cards_to_node_binary(card_node*& head) {
	ifstream bin;
	bin.open("card_data.bin", ios::binary);
	if (!bin.is_open()) return;

	head = nullptr;
	card_node* tail = nullptr;

	while (true) {
		string aName;
		string aPwd;
		string tStartStr;
		string tEndStr;
		string tLastStr;
		int nStatus = 0;
		double fTotalUse = 0.0;
		int nUseCount = 0;
		double fBalance = 0.0;
		int nDel = 0;

		if (!read_string_binary(bin, aName)) break;
		if (!read_string_binary(bin, aPwd)) break;
		if (!bin.read((char*)&nStatus, sizeof(nStatus))) break;
		if (!read_string_binary(bin, tStartStr)) break;
		if (!read_string_binary(bin, tEndStr)) break;
		if (!bin.read((char*)&fTotalUse, sizeof(fTotalUse))) break;
		if (!read_string_binary(bin, tLastStr)) break;
		if (!bin.read((char*)&nUseCount, sizeof(nUseCount))) break;
		if (!bin.read((char*)&fBalance, sizeof(fBalance))) break;
		if (!bin.read((char*)&nDel, sizeof(nDel))) break;

		card_node* node = new card_node;
		node->data.aName = aName;
		node->data.aPwd = aPwd;
		node->data.nStatus = nStatus;
		node->data.tStart = tStartStr;
		node->data.tEnd = tEndStr;
		node->data.fTotalUse = fTotalUse;
		node->data.tLast = tLastStr;
		node->data.nUseCount = nUseCount;
		node->data.fBalance = fBalance;
		node->data.nDel = nDel;
		node->next = nullptr;

		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}
}