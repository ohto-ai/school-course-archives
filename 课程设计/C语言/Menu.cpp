

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "LibDef.h"
#include "Menu.h"

#define scanf SetCursor(20,1);fflush(stdin);scanf
#define printf SetCursor(20,0);printf
#define gets(s) SetCursor(20,1);fflush(stdin);fgets(s,MAX_PATH, stdin)
#define fgets SetCursor(20,1);fflush(stdin);fgets

#define OptionCol 0XE0
#define BoxCol 0X8F
#define TitleCol 0X8B
 

void BorMng()	//���Ĺ���
{
ReturnToFunBegin:
	SaveBor();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"�� �� �� ��");
	//������Ҫ������
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         ��      ��         ",
		"         ��      ��         ",
		"         ��      ��         ",
		"         ��      ѯ         ",
		"         ��      ��         "
	};
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAtW(12,5+i,OptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAtW(12,5+Choice, OptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			Choice=(Choice+OptionNum-1)%OptionNum;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%OptionNum;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			ClearScreen();
			switch(Choice)
			{
			case 0:
				{	//����
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   ����   > > >",0X8F,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"�������������Ϣ���鼮��Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");
					StringAtW(2,9,"���:");
					StringAtW(2,10,"����:");
					StringAtW(2,11,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);
					if((Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)||
						Stu==NULL)
					{
						DrawShadowStringBox(15,8,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					SetCurPosW(5,9);gets(Buffer[0]);
					SetCurPosW(5,10);gets(Buffer[1]);
					SetCurPosW(5,11);gets(Buffer[2]);
					BokNodeLink Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);
					if((Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)||
						Bok==NULL)
					{
						DrawShadowStringBox(15,8,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					
					SetCursor(20,0);
					int LogInfo=LogBor(Stu,Bok);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					SetCurPosW(1,12);
					OutCutString(80,"%s(%s)����%s(%s) %s",Stu->StuName,Stu->StuNum,Bok->BookName,Bok->BookNum,LogInfo?"ʧ��":"�ɹ�");
					
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//����
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   ����   > > >",0X8F,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"�������������Ϣ���鼮��Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");
					StringAtW(2,9,"���:");
					StringAtW(2,10,"����:");
					StringAtW(2,11,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCurPosW(5,9);gets(Buffer[0]);
					SetCurPosW(5,10);gets(Buffer[1]);
					SetCurPosW(5,11);gets(Buffer[2]);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Bok=NULL;
					else
						Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);

					if(Stu==NULL&&Bok==NULL)
					{
						DrawShadowStringBox(15,8,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}

					SetCursor(20,0);
					BorNodeLink Bor;
					ResetLastFindBorrow();
					int LogInfo=LogRet(Bor=FindUnRet(Stu,Bok));

					SetConsoleTextAttribute(HConsoleOut,0X0B);
					SetCurPosW(2,12);
					if(LogInfo)
						OutCutString(80,"�黹 �鼮 ʧ��");
					else
						OutCutString(80,"%s �黹 �鼮 %s �ɹ�",FindFirstStudent(Bor->StuNum,0,0),FindFirstBook(Bor->BookNum,0,0));
					
					ConWaitKey(0);
				}
				break;
			case 2://չʾ�����б�
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   �鿴   > > >",0X8B,0XF0);

					SetCursor(20,0);
					SetCurPosW(0,4);
					ShowBorrowList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//��ѯ
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   ��ѯ   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"�������������Ϣ���鼮��Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");
					StringAtW(2,9,"���:");
					StringAtW(2,10,"����:");
					StringAtW(2,11,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCurPosW(5,9);gets(Buffer[0]);
					SetCurPosW(5,10);gets(Buffer[1]);
					SetCurPosW(5,11);gets(Buffer[2]);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Bok=NULL;
					else
						Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);

					if(Stu==NULL&&Bok==NULL)
					{
						DrawShadowStringBox(15,8,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}

					BorNodeLink Bor;

					SetCursor(20,0);
					ResetLastFindBorrow();
					SetCurPosW(0,14);
					while(Bor=FindBorrow(Stu,Bok)){
						ShowBorrow(Bor);
					}

					ConWaitKey(0);
				}
				break;
			case 4:{	//�޸�
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"�������������Ϣ���鼮��Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");
					StringAtW(2,9,"���:");
					StringAtW(2,10,"����:");
					StringAtW(2,11,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCurPosW(5,9);gets(Buffer[0]);
					SetCurPosW(5,10);gets(Buffer[1]);
					SetCurPosW(5,11);gets(Buffer[2]);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Bok=NULL;
					else
						Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);

					BorNodeLink Bor=FindFirstBorrow(Stu,Bok);
					if((Stu==NULL&&Bok==NULL)||Bor==NULL)
					{
						DrawShadowStringBox(15,8,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}


					//
					long BData,RData;
					double Fine;
					ClearScreen();
					SetCursor(20,0);
					SetCurPosW(0,14);
					ShowBorrow(Bor);

					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"�����ƽ�����Ϣ(�����޸Ļس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"���:");
					StringAtW(2,7,"���:");
					StringAtW(2,8,"�黹:");
					StringAtW(2,9,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%ld",&BData);else BData=-1;
					SetCurPosW(5,8);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%ld",&RData);else RData=-1;
					SetCurPosW(5,9);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%lf",&Fine);else Fine=-1.0;


					//�޸���Ϣ
					ModifyBorrow(Bor,Buffer[0],Buffer[1],BData,RData,Fine);

					DrawShadowStringBox(15,7,"  �޸ĳɹ���",0XF0,0X80);
					ConWaitKey(0);
				}
			default:;
			}
			goto ReturnToFunBegin;
		case 27:
			ClearScreen();
			return;
		}
	}

	ConWaitKey(0);
}

void StuMng()	//ѧ������
{
ReturnToFunBegin:
	SaveStu();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"ѧ �� �� ��");
	//������Ҫ������
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         ע      ��         ",
		"         ע      ��         ",
		"         ��      ��         ",
		"         ��      ѯ         ",
		"         ��      ��         "
	};
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAtW(12,5+i,OptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAtW(12,5+Choice, OptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			Choice=(Choice+OptionNum-1)%OptionNum;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%OptionNum;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			ClearScreen();
			switch(Choice)
			{
			case 0:
				{	//����
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   ע��   > > >",0X8B,0XF0);

					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ������Ϣ");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					StuNodeLink Stu;
					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					Stu=FindFirstStudent(Buffer[0],NULL,NULL);


					SetCursor(20,0);
					SetConsoleTextAttribute(HConsoleOut,0X8C);


					if(Buffer[0][0]==0||
						Buffer[1][0]==0||
						Buffer[2][0]==0)
					{
						DrawShadowStringBox(15,7,"��Ϣ������",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					if(Stu!=NULL)
					{
						DrawShadowStringBox(15,7,"ѧ���Ѵ���",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					if(AddStudent(Buffer[0],Buffer[1],Buffer[2]))
					{
						DrawShadowStringBox(15,7,"ѧ��ע��ɹ�",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					else
					{
						DrawShadowStringBox(15,7,"ע��ʧ�ܣ�",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//ע��
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   ע��   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCursor(20,0);
					if(Stu==NULL)
					{
						DrawShadowStringBox(15,7,"δ���ҵ���",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					SetCurPosW(2,11);
					ShowStudent(Stu);

					DrawShadowStringBox(15,7,"ȷ��ɾ����(Y/N) ",0X8C,0XF0);
					char ch=ConWaitKey(5,'Y','y','N','n',27);
					if(ch=='Y'||ch=='y'){
						RemoveStudent(Stu);
						DrawShadowStringBox(15,7,"    ɾ���ɹ���  ",0X8C,0XF0);
						ConWaitKey(0);
					}
					break;					
				}
				break;
			case 2://չʾѧ���б�
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   �鿴   > > >",0X8B,0XF0);

					SetCursor(20,0);
					SetCurPosW(0,4);

					ShowStudentList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//��ѯ
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   ��ѯ   > > >",0X8B,0XF0);

					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);

					SetCursor(20,0);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
					{
						Stu=NULL;
						DrawShadowStringBox(15,7,"δ���ҵ���",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					ResetLastFindStudent();
					SetCurPosW(0,8);
					while(Stu=FindStudent(Buffer[0],Buffer[1],Buffer[2]))
					{
						ShowStudent(Stu);
					}

					ConWaitKey(0);
				}
				break;
			case 4://�޸�
				{
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCursor(20,0);
					if(Stu==NULL)
					{
						DrawShadowStringBox(15,7,"δ���ҵ���",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}

					//�޸�
					
					ClearScreen();
					SetCurPosW(2,11);
					ShowStudent(Stu);
					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ������Ϣ(�����޸Ļس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);

					SetCursor(20,0);


					if(Buffer[0][0]&&FindFirstStudent(Buffer[0],0,0))
					{
						DrawShadowStringBox(15,7,"ѧ���Ѵ���",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					//�޸���Ϣ
					ModifyStudent(Stu,Buffer[0],Buffer[1],Buffer[2]);


					DrawShadowStringBox(15,7,"  �޸ĳɹ���",0X8C,0XF0);
					ConWaitKey(0);
					
					break;
				}
					
			default:;
			}
			goto ReturnToFunBegin;
		case 27:
			ClearScreen();
			return;
		}
	}
	ConWaitKey(0);
}
void BokMng()	//ͼ�����
{
ReturnToFunBegin:
	SaveBok();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"ͼ �� �� ��");
	//������Ҫ������
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         ��      ��         ",
		"         ��      ��         ",
		"         ��      ��         ",
		"         ��      ѯ         ",
		"         ��      ��         "
	};
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAtW(12,5+i,OptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAtW(12,5+Choice, OptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			Choice=(Choice+OptionNum-1)%OptionNum;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%OptionNum;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			ClearScreen();
			switch(Choice)
			{
			case 0:
				{	//����
					ClearScreen();
					char Buffer[4][128];
					double Price;
					DrawShadowStringBox(15,0,"< < <   ���   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ͼ�����Ϣ");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"���:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"����:");
					StringAtW(2,8,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					BokNodeLink Bok;
					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					SetCurPosW(5,8);gets(Buffer[3]);if(Buffer[3][0])sscanf(Buffer[3],"%lf",&Price);else Price=-1.0;

					Bok=FindFirstBook(Buffer[0],NULL,NULL);

					SetCursor(20,0);

					if(Buffer[0][0]==0||
						Buffer[1][0]==0||
						Buffer[2][0]==0)
					{
						DrawShadowStringBox(15,8,"��Ϣ������",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					if(Bok!=NULL)
					{
						DrawShadowStringBox(15,8,"����Ѵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					if(AddBook(Buffer[0],Buffer[1],Buffer[2],Price))
					{
						DrawShadowStringBox(15,8,"ͼ������ӣ�",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					else
					{
						
						DrawShadowStringBox(15,8,"���ʧ�ܣ�",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//�Ƴ�
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   �Ƴ�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ͼ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"���:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Bok=NULL;
					else
						Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);

					SetCursor(20,0);
					if(Bok==NULL)
					{
						
						DrawShadowStringBox(15,7,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					SetCurPosW(2,11);
					ShowBook(Bok);

					DrawShadowStringBox(15,7,"ȷ��ɾ����(Y/N) ",0XF0,0X80);
					char ch=ConWaitKey(5,'Y','y','N','n',27);
					if(ch=='Y'||ch=='y'){
						RemoveBook(Bok);
						DrawShadowStringBox(15,7,"    ɾ���ɹ���  ",0XF0,0X80);
						ConWaitKey(0);
					}
					break;					
				}
				break;
			case 2://չʾͼ���б�
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   �鿴   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);

					SetCursor(20,0);
					SetCurPosW(0,4);

					ShowBookList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//��ѯ
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   ��ѯ   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ͼ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"���:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);

					SetCursor(20,0);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
					{
						Bok=NULL;
						DrawShadowStringBox(15,7,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					ResetLastFindBook();
					SetCurPosW(0,8);
					while(Bok=FindBook(Buffer[0],Buffer[1],Buffer[2]))
					{
						ShowBook(Bok);
					}

					ConWaitKey(0);
				}
				break;
			case 4://�޸�
				{
					ClearScreen();
					char Buffer[4][128];

					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ͼ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"���:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"����:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					BokNodeLink Bok;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Bok=NULL;
					else
						Bok=FindFirstBook(Buffer[0],Buffer[1],Buffer[2]);

					SetCursor(20,0);
					if(Bok==NULL)
					{
						
						DrawShadowStringBox(15,7,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}

					//�޸�
					double Price;
					int HasBorrow;
					ClearScreen();
					SetCurPosW(2,11);
					ShowBook(Bok);

					DrawShadowStringBox(15,0,"< < <   �޸�   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ͼ�����Ϣ(�����޸Ļس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"���:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"����:");
					StringAtW(2,8,"����:");
					StringAtW(2,9,"״̬:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					SetCurPosW(5,8);gets(Buffer[3]);if(Buffer[3][0])sscanf(Buffer[3],"%lf",&Price);else Price=-1.0;
					SetCurPosW(5,9);gets(Buffer[3]);if(Buffer[3][0])sscanf(Buffer[3],"%d",&HasBorrow);else HasBorrow=-1;

					SetCursor(20,0);

					if(Buffer[0][0]&&FindFirstBook(Buffer[0],0,0))
					{
						DrawShadowStringBox(15,7," ����Ѵ��� ",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					//�޸���Ϣ
					ModifyBook(Bok,Buffer[0],Buffer[1],Buffer[2],Price,HasBorrow);


					DrawShadowStringBox(15,7,"  �޸ĳɹ���",0XF0,0X80);
					ConWaitKey(0);
					
					break;
				}
					
			default:;
			}
			goto ReturnToFunBegin;
		case 27:
			ClearScreen();
			return;
		}
	}
	ConWaitKey(0);
}
void Fine()		//���ڷ���
{
ReturnToFunBegin:
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,8,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"�� �� �� ��");
	//������Ҫ������
	int OptionNum=2;
	static char OptionStr[2][29]=
	{		
		"         ��      ��         ",
		"         ȫ      ��         "
	};
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAtW(12,5+i,OptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAtW(12,5+Choice, OptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			Choice=(Choice+OptionNum-1)%OptionNum;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%OptionNum;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			ClearScreen();
			switch(Choice)
			{
			case 0:
				{	//����
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   ����   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"������ѧ����Ϣ(δ֪��Ϣ�ɻس�����)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"ѧ��:");
					StringAtW(2,6,"����:");
					StringAtW(2,7,"Ժϵ:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					StuNodeLink Stu;
					if(Buffer[0][0]==0&&
						Buffer[1][0]==0&&
						Buffer[2][0]==0)
						Stu=NULL;
					else
						Stu=FindFirstStudent(Buffer[0],Buffer[1],Buffer[2]);

					SetCursor(20,0);
					if(Stu==NULL)
					{
						DrawShadowStringBox(15,7,"δ���ҵ���",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					ShowFine(Stu);
					ConWaitKey(0);
				}
				break;
			case 1:
				{	
					ClearScreen();
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   ȫ��   > > >",0X8B,0XF0);

					SetCursor(20,0);
					SetCurPosW(0,4);

					ShowFineList();
					ConWaitKey(0);

				}
				break;
			default:;
			}
			goto ReturnToFunBegin;
		case 27:
			ClearScreen();
			return;
		}
	}
	ConWaitKey(0);
}
void SysSet()	//ϵͳ����
{
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"ϵ ͳ �� ��");
	//������Ҫ������
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         ��      δ         ",
		"         ��      ��         ",
		"  ---+<�������ķָ���>+---  ",
		"         ��      ��         ",
		"         ��  ��  ��         "
	};
	
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAtW(12,5+i,OptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAtW(12,5+Choice, OptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			Choice=(Choice+OptionNum-1)%OptionNum;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%OptionNum;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			Beep(1000,50);
			break;
		case 27:
			return;
		default:;
		}
	}
}



MenuMsg Menu()//���˵�
{
	SetCursor(20,0);
	ClearScreen();
	SetConsoleTextAttribute(HConsoleOut,BoxCol);
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"�X","�T","�[",
		"�U","  ","�U",
		"�c","��","�f");
	DrawShadowBox(9,4,29,12,BoxCol,0XF0,
		"�U","  ","�U",
		"�U","  ","�U",
		"�^","�T","�a");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"ͼ�����ϵͳ");

	//������Ҫ������
	int OptionNum=6;
	static char MenuOptionStr[6][32]=
	{		
		"      ��  ��  ��  ��      ",
		"      ѧ  ��  ��  ��      ",
		"      ͼ  ��  ��  ��      ",
		"      ��  ��  ��  ��      ",
		"      ϵ  ͳ  ��  ��      ",
		"      ��  ��  ϵ  ͳ      "
	};

	
	Beep(1800,100);
	static int Choice=0;
	int i;
	for(;;)
	{
		SetConsoleTextAttribute(HConsoleOut,TEXT_OPTION_COL);
		for(i=0;i<OptionNum;++i)
			StringAt(25,5+i,MenuOptionStr[i]);

		SetConsoleTextAttribute(HConsoleOut,OptionCol);
		StringAt(25,5+Choice, MenuOptionStr[Choice]);

		switch(ConWaitKey(7,
			27,//Esc�˳�
			-32,//��չ��
			13,//�س�
			'W',
			'w',
			'S',
			's'))
		{
		case 'W':
		case 'w':
			
			Choice=(Choice+5)%6;
			break;
		case 'S':
		case 's':
			Choice=(Choice+1)%6;
			break;
		case -32:
			{
				switch(ConWaitKey(2,'H','P'))
				{
				case 'H':
					Choice=(Choice+OptionNum-1)%OptionNum;
					break;
				case 'P':
					Choice=(Choice+1)%OptionNum;
					break;
				}
				break;
			}
		case 13:
			ClearScreen();
			Beep(1500,100);
			return (MenuMsg)(Choice+1);
		case 27:
			ClearScreen();
			return Menu_ExtSys;
		}
	}
	ClearScreen();
	return (MenuMsg)0;
}



#undef scanf
#undef printf

