#include "../公共头文件（数据结构）/model.h"
#include "card_service.h"
#include "../数据管理/card_file.h"
#include<iostream>
#include<iomanip>
#include<sstream>
#include<ctime>
using namespace std;

static string current_date_string() {
    time_t now = time(NULL);
    tm localTm = {};
    localtime_s(&localTm, &now);
    ostringstream oss;
    oss << put_time(&localTm, "%Y-%m-%d");
    return oss.str();
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
    string nowDate = current_date_string();
    card_new->data.tStart = nowDate;       //添加开卡时间为当前系统时间
    card_new->data.tEnd = nowDate;         //开卡截止期默认当前时间
    card_new->data.tLast = nowDate;        //最后使用时间默认当前时间
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
    return;
}

//查询卡服务
void searching_card() {
    cout << endl << "----------查询卡----------" << endl;
    string cardnum;
    cout << "请输入查询的卡号（长度为1~18）：__________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
    cin >> cardnum;

    //查询卡是否存在
    card_node* ptr = card_head;
    bool is_exist = false;
    while (ptr != NULL) {
        if (cardnum == ptr->data.aName) { is_exist = true; break; }
        ptr = ptr->next;
    }
    if (!is_exist) {
        cout << "没有该卡的信息！" << endl << endl;
        return;
    }

    //检测密码是否正确
    string cardpwd;
    cout << "请输入密码（长度为1~8）：________\b\b\b\b\b\b\b\b";
    cin >> cardpwd;
    if (cardpwd != ptr->data.aPwd) { cout << "密码错误" << endl << endl; return; }

    //输出卡的信息
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