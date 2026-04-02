#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<windows.h>
#include "../公共头文件（数据结构）/model.h"
#include "menu.h"
using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);   //使中文输出不出现乱码
	OutputMenu();
	return 0;
}
