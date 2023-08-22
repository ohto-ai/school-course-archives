//Main.cpp 
//部分使用C++特性（函数重载）
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

HANDLE HConsoleIn;
HANDLE HConsoleOut;
CONSOLE_SCREEN_BUFFER_INFO ConScrBuffInfo;	//窗口缓冲区信息
COORD ConBuffSize={80,400};					//窗口缓冲区大小  
SMALL_RECT ConRect={0,0,ConBuffSize.X-1, ConBuffSize.Y-1}; 
INPUT_RECORD InputRec;						//定义输入事件结构体  
COORD MousePos;								//鼠标位置

#include "OutPutSet.h"
#include "InputSet.h" 
#include "LibDef.h"
#include "Menu.h"
void WhenReturn()//保存数据释放内存
{
	SaveData();
	FreeStu();
	FreeBok();
	FreeBor();
				
}
int main()
{
	HConsoleIn =GetStdHandle(STD_INPUT_HANDLE);		//获得标准输入设备句柄  
    HConsoleOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出设备句柄   
	SetConsoleTitle("图书管理系统"); 
    SetConsoleScreenBufferSize(HConsoleOut,ConBuffSize);		//设置窗口缓冲区大小 
	SetConsoleWindowInfo(HConsoleOut,true,&ConRect);			//重置窗口位置和大小
    GetConsoleScreenBufferInfo(HConsoleOut,&ConScrBuffInfo);	//获得窗口缓冲区信息 
	SetConsoleCtrlHandler(NULL,TRUE);							//禁止Ctrl+C关闭程序

	atexit(WhenReturn);//注册函数
	srand(time(0));
	
	int ReadDataSign=ReadData();
	if(ReadDataSign&0X04)//Student读取失败
	{
		//加入自己几个密友的信息
		AddStudent("202170638","朱广锋","计算机工程学院");
		AddStudent("202170623","孔江华","计算机工程学院");
		AddStudent("202170637","周欢","计算机工程学院");
		AddStudent("202170503","陈姿芊","计算机工程学院");

		//随机生成20人
		InitStudent(20);
		SaveStu();//保存数据
	}
	if(ReadDataSign&0X02)//Book读取失败
	{
		AddBook("0715","图书管理系统应用指南","THAT BOY 出版社",99.99);
		//随机生成20本书
		InitBook(20);
		SaveBok();//保存数据
	}
	if(ReadDataSign&0X01)//Borrow读取失败
	{
		InitBorrow(20);
		SaveBor();//保存数据
	}

	for(;;)
	{
		SetConsoleTitle("图书管理系统"); 
		switch(Menu())
		{
		case Menu_BorMng:	//借阅管理
			SetConsoleTitle("图书管理系统-借阅管理"); 
			BorMng();
			break;
		case Menu_StuMng:	//学生管理
			SetConsoleTitle("图书管理系统-学生管理"); 
			StuMng();
			break;
		case Menu_BokMng:	//图书管理
			SetConsoleTitle("图书管理系统-图书管理");
			BokMng(); 
			break;
		case Menu_Fine	:	//逾期罚款
			SetConsoleTitle("图书管理系统-逾期罚款");
			Fine();
			break;
		case Menu_SysSet:	//系统设置
			SetConsoleTitle("图书管理系统-系统设置");
			SysSet();
			break;
		case Menu_ExtSys:	//退出系统
			//自动释放内存
			return 0;
		case Menu_Null	:	//空指令
			DrawShadowStringBox(10,3,"NULL COMMAND!",0X8F,0XF0);
			break;
		case Menu_Error :	//出错
		default:
			DrawShadowStringBox(10,3,"ERROR COMMAND!",0X8F,0XF0);
		}
	}

	return 0;
}

/*
#        ┏┓　　　┏┓+ +
#　　　┏┛┻━━━┛┻┓ + +
#　　　┃　　　　　　　┃ 　
#　　　┃　　　━　　  ┃ ++ + + +
#　　 ████━███ ┃ +
#　　　┃　　　　　　　┃ +
#　　　┃　　　┻　　　┃
#　　　┃　　　　　　　┃ + +
#　　　┗━┓　　　┏━┛
#　　　　　┃　　　┃　　　　　　　　　　　
#　　　　　┃　　　┃ + + + +
#　　　　　┃　　　┃　Codes are far away from bugs with the animal protecting　　　
#　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
#　　　　　┃　　　┃
#　　　　　┃　　　┃　　+　　　　　　　　　
#　　　　　┃　 　　┗━━━┓ + +
#　　　　　┃ 　　　　　　　┣┓
#　　　　　┃ 　　　　　　　┏┛
#　　　　　┗┓┓┏━┳┓┏┛ + + + +
#　　　　　　┃┫┫　┃┫┫
#　　　　　　┗┻┛　┗┻┛+ + + +
*/