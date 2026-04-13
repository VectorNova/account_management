#include "money_file.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

//将充值退费信息存入文件
void save_money_to_file(money_node* money_head)
{
    ofstream fout;
    fout.open("money_data.txt");
    if (!fout.is_open()) return;

    for (money_node* ptr = money_head; ptr != nullptr; ptr = ptr->next) {
        fout << ptr->data.nStatus << '\t'
            << ptr->data.aCardName << '\t'
            << (ptr->data.time.empty() ? "-" : ptr->data.time) << '\t'
            << ptr->data.amount << '\t'
            << ptr->data.fBalance << endl;
    }

    fout.close();
}

//从文件中读取充值退费信息到链表
void load_money_to_node(money_node** money_head)
{
    ifstream fin;
    fin.open("money_data.txt");
    if (!fin.is_open()) return;

    *money_head = nullptr;
    money_node* tail = nullptr;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        string statusStr;
        string cardName;
        string timeStr;
        string amountStr;
        string balanceStr;
        stringstream ss(line);
        if (!getline(ss, statusStr, '\t')) continue;
        if (!getline(ss, cardName, '\t')) continue;
        if (!getline(ss, timeStr, '\t')) continue;
        if (!getline(ss, amountStr, '\t')) continue;
        if (!getline(ss, balanceStr, '\t')) continue;

        money_node* node = new money_node;
        node->data.nStatus = stoi(statusStr);
        node->data.aCardName = cardName;
        node->data.time = (timeStr == "-" ? "" : timeStr);
        node->data.amount = stod(amountStr);
        node->data.fBalance = stod(balanceStr);
        node->next = nullptr;

        if (*money_head == nullptr) {
            *money_head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    fin.close();
}
