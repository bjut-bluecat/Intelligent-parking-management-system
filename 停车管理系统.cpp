// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <winbase.h>
using namespace std;
#define MAX 5000
//enum type { small，medium };
typedef struct car
{
	string chehao;
	int num;//车位号码
	SYSTEMTIME timein, timeout;
	char type;
	int flag;
}Car;
void delay()
{
	;
}
class Garage
{
private:
	Car car[MAX];
	int total;
	int current;//当前剩余车位
	double price_s;//小车收费
	double price_m;//中型车收费
public:
	Garage();
	~Garage() { cout << "车库已经析构" << endl; };
	int current_num();
	int carin();
	int carout();
	int remant_num() { return current; };
	int expense(int num);
	int current_add() { current++; return current; };
	int current_subtraction() { current--; return current; };
	int current_information();
	int graph_garage();
};
Garage::Garage()
{
	int i;
	cout << "请输入停车场收费标准" << endl;
	cout << "大型车每秒收费标准" << endl;
	cin >> price_m;
	cout << "小型车每秒收费标准" << endl;
	cin >> price_s;
	cout << "请输入这个停车场的容量" << endl;
	cin >> total;
	for (i = 1; i <= total; i++)
	{
		car[i].flag = 0;
		car[i].num = i;
	}
	current = total;
};
int Garage::current_num()
{
	cout << "当前空闲车位数量：" << remant_num() << endl;
	return 0;
};
int Garage::carin()
{
	string chehao;
	int num;
	SYSTEMTIME timein;
	char type;
	cout << "请输入车牌号" << endl;
	cin >> chehao;
	cout << "请输入车所停的位置" << endl;
	cin >> num;
	if (car[num].flag == 1) { cout << "此车库已满" << endl; return -1; }
	if (num <= 0 || num>total) { cout << "没有这个车库" << endl; return -1; }
	cout << "请输入车的类型(s小b大)" << endl;
	cin >> type;
	car[num].flag = 1;
	car[num].chehao = chehao;
	GetLocalTime(&timein);
	car[num].timein = timein;
	car[num].type = type;
	cout << endl << "录入成功" << endl;
	current_subtraction();//车位减一
	cout << "牌照：" << car[num].chehao << endl;
	if (car[num].type == 's') { cout << "车型：小" << endl; }
	else if (car[num].type == 'b') cout << "车型：大" << endl;
	else { cout << "没有这个车型" << endl; return -1; }
	cout << "入库时间：" << car[num].timein.wHour << "点" << car[num].timein.wMinute << "分" << car[num].timein.wSecond << "秒" << endl;
	cout << "车所停的位置:" << num << endl;
	return 0;
};
int Garage::carout()
{
	int num;
	SYSTEMTIME timeout;
	cout << "请输入汽车出库的号码" << endl;
	cin >> num;
	if (car[num].flag == 0)
	{
		cout << "此车位没有车" << endl;
		return 0;
	}
	car[num].flag = 0;
	current_add();//车位加一
	GetLocalTime(&timeout);
	car[num].timeout = timeout;
	cout << "车库号码：" << num << endl;
	cout << "牌照：" << car[num].chehao << endl;
	if (car[num].type == 's')
	{
		cout << "车型：小" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "车型：大" << endl;
	}
	cout << "出库时间：" << car[num].timeout.wHour << "点" << car[num].timeout.wMinute << "分" << car[num].timeout.wSecond << "秒" << endl;
	expense(num);
	return 0;
};
int Garage::expense(int num)
{
	WORD time;
	time = 60 * 60 * (car[num].timeout.wHour - car[num].timein.wHour) + 60 * (car[num].timeout.wMinute - car[num].timein.wMinute) + (car[num].timeout.wSecond - car[num].timein.wSecond);
	cout << "共计停车" << time << "秒" << endl;
	if (car[num].type == 's')
	{
		cout << "请交纳停车费" << time*price_s << "元" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "请交纳停车费" << time*price_m << "元" << endl;
	}
	return 0;
};
int Garage::current_information()
{
	SYSTEMTIME time;
	WORD parking_time;
	int num;
	cout << "请输出你想检测的车库号码" << endl;
	cin >> num;
	cout << "车库号码：" << num << endl;
	if (car[num].flag == 0)
	{
		cout << "该车库空闲" << endl;
		return 0;
	}
	cout << "牌照：" << car[num].chehao << endl;
	if (car[num].type == 's')
	{
		cout << "车型：小" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "车型：大" << endl;
	}
	GetLocalTime(&time);
	cout << "入库时间：" << car[num].timein.wHour << "点" << car[num].timein.wMinute << "分" << car[num].timein.wSecond << "秒" << endl;
	parking_time = 60 * 60 * (time.wHour - car[num].timein.wHour) + 60 * (time.wMinute - car[num].timein.wMinute) + (time.wSecond - car[num].timein.wSecond);
	cout << "已停时间：" << parking_time << "秒" << endl;
	return 0;
};
int Garage::graph_garage()
{
	int i;
	for (i = 1; i <= total; i++)
	{
		if (i % 10 == 0)
		{
			if (car[i].flag == 1)
			{
				cout << i << "*" << endl;
			}
			else
			{
				cout << i << endl;
			}
		}
		if (i % 10 != 0)
		{
			if (car[i].flag == 1)
			{
				cout << i << "* ";
			}
			else
			{
				cout << i << " ";
			}
		}
	}
	return 0;
};
int main()
{
	int a;
	Garage g;
	while (1)
	{
		cout << "********欢迎观临电控蓝猫停车场********" << endl;
		g.graph_garage();
		cout << "-开始-" << endl;
		cout << "请用数字键进行操作" << endl;
		cout << "1.剩余空闲车位数量" << endl;
		cout << "2.车辆入库" << endl;
		cout << "3.车辆出库" << endl;
		cout << "4.查看每个车位状态" << endl;
		//cout << "5.停车场车位图" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			g.current_num();
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 2:
			g.carin();
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 3:
			g.carout();
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 4:
			g.current_information();
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 5:
			g.graph_garage();
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		default:
			cout << "输入错误" << endl;
			cout << "按任意键退出" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		}
	}
	return 0;
}