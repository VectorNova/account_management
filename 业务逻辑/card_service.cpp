#include "../公共头文件（数据结构）/model.h"
#include "card_service.h"
#include "../数据管理/card_file.h"
#include "money_service.h"
#include "../数据管理/money_file.h"
#include<iostream>
#include<iomanip>
#include<sstream>
#include<ctime>
#include<vector>
using namespace std;

static string format_time_string(time_t value) {
    tm localTm = {};
    localtime_s(&localTm, &value);
    ostringstream oss;
    oss << put_time(&localTm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static string current_date_string() {
    return format_time_string(time(NULL));
}

card_node* card_head = NULL;

//添加卡服务
void adding_card() {
    cout << endl << "----------添加卡----------" << endl;
    card_node* card_new = new card_node;

    // 读取卡号
    cout << "请输入卡号（长度为1~18）：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
    cin >> card_new->data.aName;
    if (card_new->data.aName.size() > 18) {
        cout << "卡号超长" << endl;
        delete card_new;
        return;
    }

    // 检查是否有重复卡
    card_node* ptr = card_head;
    bool is_repeat = false;
    while (ptr != NULL) {
        if (ptr->data.aName == card_new->data.aName) { is_repeat = true; break; }
        ptr = ptr->next;
    }

    if (is_repeat) {
        cout << "错误，已有重复卡" << endl;
        delete card_new;
        return;
    }

    // 继续读取其它信息
    cout << "请输入密码（长度为1~8）：________\b\b\b\b\b\b\b\b";     //添加密码
    cin >> card_new->data.aPwd;
    if (card_new->data.aPwd.size() > 8) {
        cout << "密码超长" << endl;
        delete card_new;
        return;
    }
    cout << "请输入开卡金额（RMB）：";       //添加初始金额
    cin >> card_new->data.fBalance;
    card_new->data.nStatus = 0;            //添加使用状态
    card_new->data.nUseCount = 0;          //添加使用次数
    card_new->data.fTotalUse = 0.0;        //添加累计使用
 time_t now = time(NULL);
    string nowDate = format_time_string(now);
    tm endTm = {};
    localtime_s(&endTm, &now);
    endTm.tm_year += Card_Life;
    time_t endTime = mktime(&endTm);
    string endDate = format_time_string(endTime);
    card_new->data.tStart = nowDate;       //添加开卡时间为当前系统时间
    card_new->data.tEnd = endDate;         //开卡截止期默认当前时间 + Card_Life 年
    card_new->data.tLast = nowDate;        //最后使用时间默认当前系统时间
    card_new->data.nDel = 0;               //添加删除标志

    // 插入到链表末尾或作为头节点
    if (card_head == NULL) {
        card_head = card_new;
        card_new->next = NULL;
    }
    else {
        ptr = card_head;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = card_new;
        card_new->next = NULL;
    }

    //显示添加的卡信息
    cout << endl << "-----添加的卡信息如下-----" << endl;
    cout << "卡号\t" 
        << "密码\t" 
        << "状态\t" 
        << "金额\t" << endl;
    cout << card_new->data.aName << '\t'
        << card_new->data.aPwd << '\t'
        << card_new->data.nStatus << '\t'
        << card_new->data.fBalance << endl << endl;

	//将卡信息存入文件
    save_cards_to_file(card_head);

    //将开卡金额写入充值退费日志（作为一条充值记录）
    if (card_new->data.fBalance > 0) {
        money_node* moneyNew = new money_node;
        moneyNew->data.nStatus = 1;
        moneyNew->data.aCardName = card_new->data.aName;
        moneyNew->data.time = card_new->data.tStart;
        moneyNew->data.amount = card_new->data.fBalance;
        moneyNew->data.fBalance = card_new->data.fBalance;
        moneyNew->next = nullptr;

        if (money_head == nullptr) {
            money_head = moneyNew;
        } else {
            money_node* tail = money_head;
            while (tail->next != nullptr) tail = tail->next;
            tail->next = moneyNew;
        }
        save_money_to_file(money_head);
    }
    return;
}

//查询卡服务
void searching_card() {
    cout << endl << "----------查询卡----------" << endl;
    string cardnum;
    cout << "请输入查询的卡号（长度为1~18）：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
    cin >> cardnum;

    //模糊查询：匹配包含输入内容的卡号
    vector<card_node*> matches;
    card_node* ptr = card_head;
    while (ptr != NULL) {
        if (ptr->data.aName.find(cardnum) != string::npos) {
            matches.push_back(ptr);
        }
        ptr = ptr->next;
    }
    if (matches.empty()) {
        cout << "没有该卡的信息！" << endl << endl;
        return;
    }

    if (matches.size() > 1) {
        cout << endl << "卡号\t"
            << "状态\t"
            << "余额\t"
            << "累计使用\t"
            << "使用次数\t"
            << "上次使用时间\t" << endl;
        for (auto* node : matches) {
            cout << node->data.aName << '\t'
                << node->data.nStatus << '\t'
                << node->data.fBalance << '\t'
                << node->data.fTotalUse << "\t\t"
                << node->data.nUseCount << "\t\t";
            if (!node->data.tLast.empty()) {
                cout << node->data.tLast;
            } else {
                cout << "-";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    //仅匹配一张卡时，继续验证密码并输出
    ptr = matches.front();
    string cardpwd;
    cout << "请输入密码（长度为1~8）：________\b\b\b\b\b\b\b\b";
    cin >> cardpwd;
    if (cardpwd != ptr->data.aPwd) { cout << "密码错误" << endl << endl; return; }

    cout << endl << "卡号\t"
        << "状态\t"
        << "余额\t"
        << "累计使用\t"
        << "使用次数\t"
        << "上次使用时间\t" << endl;
    cout << ptr->data.aName << '\t'
        << ptr->data.nStatus << '\t'
        << ptr->data.fBalance << '\t'
        << ptr->data.fTotalUse << "\t\t"
        << ptr->data.nUseCount << "\t\t";
    if (!ptr->data.tLast.empty()) {
        cout << ptr->data.tLast;
    } else {
        cout << "-";
    }
    cout << endl << endl;
    return;
}
