#ifndef MODEL_H
#define MODEL_H
#include<windows.h>
#include<time.h>
#include<string>
using namespace std;

//卡信息
typedef struct card {
	string aName;        //卡号
	string aPwd;         //密码
	int nStatus;         //卡状态（0-未上机；1-正在上机；2-已注销）
    string tStart;       //开卡时间
	string tEnd;         //卡的截止期
	double fTotalUse;    //累计使用金额
    string tLast;        //最后使用日期
	int nUseCount;       //使用次数
	double fBalance;     //余额
	int nDel;            //删除标识（0-未删除；1-删除）
}card;

//卡链表
typedef struct card_node {
	card data;                     //卡的数据
	struct card_node* next;        //链表的下一项
}card_node;

//计费信息
typedef struct billing {
	string aCardName;    //卡号
    string tStart;       //上机时间
	string tEnd;         //下机时间
	double fAmount;      //消费金额
	int nStatus;         //卡状态（0-未结算；1-已结算）
	int nDel;            //删除标识（0-未删除；1-已删除）
}billing;

//计费信息链表
typedef struct billing_node {
	billing data;                     //计费信息的数据
	struct billing_node* next;        //链表的下一项
}billing_node;

//充值退费(注销)信息
typedef struct money {
	int nStatus;         //充值还是退费（0-退费；1-充值；2-注销)
	string aCardName;    //卡号
	string time;         //充值退费时间
	double amount;       //充值退费金额
	double fBalance;     //卡的余额
}money;

//充值退费信息链表
typedef struct money_node {
	money data;
	struct money_node* next;
}money_node;

#endif