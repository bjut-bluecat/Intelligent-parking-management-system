// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
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
//enum type { small��medium };
typedef struct car
{
	string chehao;
	int num;//��λ����
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
	int current;//��ǰʣ�೵λ
	double price_s;//С���շ�
	double price_m;//���ͳ��շ�
public:
	Garage();
	~Garage() { cout << "�����Ѿ�����" << endl; };
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
	cout << "������ͣ�����շѱ�׼" << endl;
	cout << "���ͳ�ÿ���շѱ�׼" << endl;
	cin >> price_m;
	cout << "С�ͳ�ÿ���շѱ�׼" << endl;
	cin >> price_s;
	cout << "���������ͣ����������" << endl;
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
	cout << "��ǰ���г�λ������" << remant_num() << endl;
	return 0;
};
int Garage::carin()
{
	string chehao;
	int num;
	SYSTEMTIME timein;
	char type;
	cout << "�����복�ƺ�" << endl;
	cin >> chehao;
	cout << "�����복��ͣ��λ��" << endl;
	cin >> num;
	if (car[num].flag == 1) { cout << "�˳�������" << endl; return -1; }
	if (num <= 0 || num>total) { cout << "û���������" << endl; return -1; }
	cout << "�����복������(sСb��)" << endl;
	cin >> type;
	car[num].flag = 1;
	car[num].chehao = chehao;
	GetLocalTime(&timein);
	car[num].timein = timein;
	car[num].type = type;
	cout << endl << "¼��ɹ�" << endl;
	current_subtraction();//��λ��һ
	cout << "���գ�" << car[num].chehao << endl;
	if (car[num].type == 's') { cout << "���ͣ�С" << endl; }
	else if (car[num].type == 'b') cout << "���ͣ���" << endl;
	else { cout << "û���������" << endl; return -1; }
	cout << "���ʱ�䣺" << car[num].timein.wHour << "��" << car[num].timein.wMinute << "��" << car[num].timein.wSecond << "��" << endl;
	cout << "����ͣ��λ��:" << num << endl;
	return 0;
};
int Garage::carout()
{
	int num;
	SYSTEMTIME timeout;
	cout << "��������������ĺ���" << endl;
	cin >> num;
	if (car[num].flag == 0)
	{
		cout << "�˳�λû�г�" << endl;
		return 0;
	}
	car[num].flag = 0;
	current_add();//��λ��һ
	GetLocalTime(&timeout);
	car[num].timeout = timeout;
	cout << "������룺" << num << endl;
	cout << "���գ�" << car[num].chehao << endl;
	if (car[num].type == 's')
	{
		cout << "���ͣ�С" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "���ͣ���" << endl;
	}
	cout << "����ʱ�䣺" << car[num].timeout.wHour << "��" << car[num].timeout.wMinute << "��" << car[num].timeout.wSecond << "��" << endl;
	expense(num);
	return 0;
};
int Garage::expense(int num)
{
	WORD time;
	time = 60 * 60 * (car[num].timeout.wHour - car[num].timein.wHour) + 60 * (car[num].timeout.wMinute - car[num].timein.wMinute) + (car[num].timeout.wSecond - car[num].timein.wSecond);
	cout << "����ͣ��" << time << "��" << endl;
	if (car[num].type == 's')
	{
		cout << "�뽻��ͣ����" << time*price_s << "Ԫ" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "�뽻��ͣ����" << time*price_m << "Ԫ" << endl;
	}
	return 0;
};
int Garage::current_information()
{
	SYSTEMTIME time;
	WORD parking_time;
	int num;
	cout << "�����������ĳ������" << endl;
	cin >> num;
	cout << "������룺" << num << endl;
	if (car[num].flag == 0)
	{
		cout << "�ó������" << endl;
		return 0;
	}
	cout << "���գ�" << car[num].chehao << endl;
	if (car[num].type == 's')
	{
		cout << "���ͣ�С" << endl;
	}
	else if (car[num].type == 'b')
	{
		cout << "���ͣ���" << endl;
	}
	GetLocalTime(&time);
	cout << "���ʱ�䣺" << car[num].timein.wHour << "��" << car[num].timein.wMinute << "��" << car[num].timein.wSecond << "��" << endl;
	parking_time = 60 * 60 * (time.wHour - car[num].timein.wHour) + 60 * (time.wMinute - car[num].timein.wMinute) + (time.wSecond - car[num].timein.wSecond);
	cout << "��ͣʱ�䣺" << parking_time << "��" << endl;
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
		cout << "********��ӭ���ٵ����èͣ����********" << endl;
		g.graph_garage();
		cout << "-��ʼ-" << endl;
		cout << "�������ּ����в���" << endl;
		cout << "1.ʣ����г�λ����" << endl;
		cout << "2.�������" << endl;
		cout << "3.��������" << endl;
		cout << "4.�鿴ÿ����λ״̬" << endl;
		//cout << "5.ͣ������λͼ" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			g.current_num();
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 2:
			g.carin();
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 3:
			g.carout();
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 4:
			g.current_information();
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		case 5:
			g.graph_garage();
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		default:
			cout << "�������" << endl;
			cout << "��������˳�" << endl;
			//getch();
			system("PAUSE");
			system("cls");
			break;
		}
	}
	return 0;
}