#include "../公共头文件（数据结构）/model.h"
#include "card_service.h"
#include<iostream>
#include<iomanip>   //为了使输出左对齐
using namespace std;

card_node* card_head = NULL;

//添加卡服务
void adding_card() {
    cout << endl << "----------添加卡----------" << endl;
    card_node* card_new = new card_node;

    // 读取卡号
    cout << "请输入卡号（长度为1~18）：";
    cin >> card_new->data.aName;

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

    // 继续读取其它信息
    cout << "请输入密码（长度为1~8）：";     //添加密码
    cin >> card_new->data.aPwd;
    cout << "请输入开卡金额（RMB）：";       //添加初始金额
    cin >> card_new->data.fBalance;
    card_new->data.nStatus = 0;            //添加使用状态
    card_new->data.nUseCount = 0;          //添加使用次数
    card_new->data.fTotalUse = 0.0;        //添加累计使用
    card_new->data.tStart = time(NULL);    //添加开卡时间为当前系统时间
    card_new->data.tLast = card_new->data.tStart;
    card_new->data.nDel = 0;               //添加删除标志

    //显示添加的卡信息
    cout << endl << "-----添加的卡信息如下-----" << endl;
    cout << left;     //左对齐
    cout << setw(10) << "卡号" << setw(10) << "密码" << 
        setw(10) << "状态" << setw(10) << "金额" << endl;
    cout << setw(10) << card_new->data.aName << setw(10) << card_new->data.aPwd <<
        setw(10) << card_new->data.nStatus << setw(10) << card_new->data.fBalance << endl << endl;
    return;
}

//查询卡服务
void searching_card() {
    cout << endl << "----------查询卡----------" << endl;
    string cardnum;
    cout << "请输入查询的卡号（长度为1~18）：";
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

    //输出卡的信息
    cout << endl << setw(10) << "卡号" << setw(10) << "状态" << setw(10) << "余额" << setw(10) <<
        "累计使用" << setw(10) << "使用次数" << setw(10) << "上次使用时间" << endl;
    cout << setw(10) << ptr->data.aName << setw(10) << ptr->data.nStatus << setw(10) << ptr->data.fBalance << setw(10) <<
        ptr->data.fTotalUse << setw(10) << ptr->data.nUseCount << setw(10) << ptr->data.tLast << endl;
    return;
}