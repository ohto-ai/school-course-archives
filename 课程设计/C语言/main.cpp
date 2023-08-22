//Main.cpp 
//����ʹ��C++���ԣ��������أ�
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
CONSOLE_SCREEN_BUFFER_INFO ConScrBuffInfo;	//���ڻ�������Ϣ
COORD ConBuffSize={80,400};					//���ڻ�������С  
SMALL_RECT ConRect={0,0,ConBuffSize.X-1, ConBuffSize.Y-1}; 
INPUT_RECORD InputRec;						//���������¼��ṹ��  
COORD MousePos;								//���λ��

#include "OutPutSet.h"
#include "InputSet.h" 
#include "LibDef.h"
#include "Menu.h"
void WhenReturn()//���������ͷ��ڴ�
{
	SaveData();
	FreeStu();
	FreeBok();
	FreeBor();
				
}
int main()
{
	HConsoleIn =GetStdHandle(STD_INPUT_HANDLE);		//��ñ�׼�����豸���  
    HConsoleOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ñ�׼����豸���   
	SetConsoleTitle("ͼ�����ϵͳ"); 
    SetConsoleScreenBufferSize(HConsoleOut,ConBuffSize);		//���ô��ڻ�������С 
	SetConsoleWindowInfo(HConsoleOut,true,&ConRect);			//���ô���λ�úʹ�С
    GetConsoleScreenBufferInfo(HConsoleOut,&ConScrBuffInfo);	//��ô��ڻ�������Ϣ 
	SetConsoleCtrlHandler(NULL,TRUE);							//��ֹCtrl+C�رճ���

	atexit(WhenReturn);//ע�ắ��
	srand(time(0));
	
	int ReadDataSign=ReadData();
	if(ReadDataSign&0X04)//Student��ȡʧ��
	{
		//�����Լ��������ѵ���Ϣ
		AddStudent("202170638","����","���������ѧԺ");
		AddStudent("202170623","�׽���","���������ѧԺ");
		AddStudent("202170637","�ܻ�","���������ѧԺ");
		AddStudent("202170503","����ܷ","���������ѧԺ");

		//�������20��
		InitStudent(20);
		SaveStu();//��������
	}
	if(ReadDataSign&0X02)//Book��ȡʧ��
	{
		AddBook("0715","ͼ�����ϵͳӦ��ָ��","THAT BOY ������",99.99);
		//�������20����
		InitBook(20);
		SaveBok();//��������
	}
	if(ReadDataSign&0X01)//Borrow��ȡʧ��
	{
		InitBorrow(20);
		SaveBor();//��������
	}

	for(;;)
	{
		SetConsoleTitle("ͼ�����ϵͳ"); 
		switch(Menu())
		{
		case Menu_BorMng:	//���Ĺ���
			SetConsoleTitle("ͼ�����ϵͳ-���Ĺ���"); 
			BorMng();
			break;
		case Menu_StuMng:	//ѧ������
			SetConsoleTitle("ͼ�����ϵͳ-ѧ������"); 
			StuMng();
			break;
		case Menu_BokMng:	//ͼ�����
			SetConsoleTitle("ͼ�����ϵͳ-ͼ�����");
			BokMng(); 
			break;
		case Menu_Fine	:	//���ڷ���
			SetConsoleTitle("ͼ�����ϵͳ-���ڷ���");
			Fine();
			break;
		case Menu_SysSet:	//ϵͳ����
			SetConsoleTitle("ͼ�����ϵͳ-ϵͳ����");
			SysSet();
			break;
		case Menu_ExtSys:	//�˳�ϵͳ
			//�Զ��ͷ��ڴ�
			return 0;
		case Menu_Null	:	//��ָ��
			DrawShadowStringBox(10,3,"NULL COMMAND!",0X8F,0XF0);
			break;
		case Menu_Error :	//����
		default:
			DrawShadowStringBox(10,3,"ERROR COMMAND!",0X8F,0XF0);
		}
	}

	return 0;
}

/*
#        ��������������+ +
#�����������ߩ��������ߩ� + +
#������������������������ ��
#��������������������  �� ++ + + +
#���� ���������������� �� +
#������������������������ +
#���������������ߡ�������
#������������������������ + +
#������������������������
#������������������������������������������
#�������������������� + + + +
#����������������������Codes are far away from bugs with the animal protecting������
#�������������������� + �����������ޱ���,������bug����
#��������������������
#������������������������+������������������
#�������������� �������������� + +
#������������ ���������������ǩ�
#������������ ������������������
#���������������������ש����� + + + +
#���������������ϩϡ����ϩ�
#���������������ߩ������ߩ�+ + + +
*/