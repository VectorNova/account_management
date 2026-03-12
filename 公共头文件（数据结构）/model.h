#ifndef MODEL_H
#define MODEL_H
#include<windows.h>
#include<time.h>
#include<string>
using namespace std;

//卡信息
typedef struct card {
	string aName;     //卡号
	string aPwd;       //密码
	int nStatus;        //卡状态（0-未上机；1-正在上机；2-已注销）
	time_t tStart;      //开卡时间
	time_t tEnd;        //卡的截止期
	float fTotalUse;    //累计使用金额
	time_t tLast;       //最后使用日期
	int nUseCount;      //使用次数
	float fBalance;     //余额
	int nDel;           //删除标识（0-未删除；1-删除）
}card;

//卡链表
typedef struct card_node {
	card data;                     //卡的数据
	struct card_node* next;        //链表的下一项
}card_node;

//计费信息
typedef struct billing {
	char aCardName[18];  //卡号
	time_t tStart;       //上机时间
	time_t tEnd;         //下机时间
	float fAmount;       //消费金额
	int nStatus;         //卡状态（0-未结算；1-已结算）
	int nDel;            //删除标识（0-未删除；1-已删除）
}billing;

#endif