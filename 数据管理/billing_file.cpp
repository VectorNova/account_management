#include "../公共头文件（数据结构）/model.h"
#include "billing_file.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;


//将计费信息存储到文件
void save_billing_to_file(billing_node* head)
{
    ofstream fout;
   fout.open("billing_data.txt");
    if (!fout.is_open()) return;

    for (billing_node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        fout << ptr->data.aCardName << '\t'
            << (ptr->data.tStart.empty() ? "-" : ptr->data.tStart) << '\t'
            << (ptr->data.tEnd.empty() ? "-" : ptr->data.tEnd) << '\t'
            << ptr->data.fAmount << '\t'
            << ptr->data.nStatus << '\t'
            << ptr->data.nDel << endl;
    }

    fout.close();
}

//从文件读取计费信息到链表
void load_billing_to_node(billing_node** head)
{
    ifstream fin;
    fin.open("billing_data.txt");
    if (!fin.is_open()) return;

    *head = nullptr;
    billing_node* tail = nullptr;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        vector<string> parts;
        parts.reserve(6);
        size_t start = 0;
        while (true) {
            size_t pos = line.find('\t', start);
            if (pos == string::npos) {
                parts.push_back(line.substr(start));
                break;
            }
            parts.push_back(line.substr(start, pos - start));
            start = pos + 1;
        }
        if (parts.size() != 6) continue;

        billing_node* node = new billing_node;
        node->data.aCardName = parts[0];
        node->data.tStart = (parts[1] == "-" ? "" : parts[1]);
        node->data.tEnd = (parts[2] == "-" ? "" : parts[2]);
        node->data.fAmount = stod(parts[3]);
        node->data.nStatus = stoi(parts[4]);
        node->data.nDel = stoi(parts[5]);
        node->next = nullptr;

        if (*head == nullptr) {
            *head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    fin.close();
}