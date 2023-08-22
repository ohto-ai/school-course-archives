

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
 

void BorMng()	//借阅管理
{
ReturnToFunBegin:
	SaveBor();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"借 阅 管 理");
	//本来是要鼠标操作
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         借      阅         ",
		"         还      书         ",
		"         查      看         ",
		"         查      询         ",
		"         修      改         "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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
				{	//借阅
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   借阅   > > >",0X8F,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入借阅者信息及书籍信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");
					StringAtW(2,9,"编号:");
					StringAtW(2,10,"书名:");
					StringAtW(2,11,"出版:");

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
						DrawShadowStringBox(15,8,"未查找到！",0XF0,0X80);
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
						DrawShadowStringBox(15,8,"未查找到！",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					
					SetCursor(20,0);
					int LogInfo=LogBor(Stu,Bok);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					SetCurPosW(1,12);
					OutCutString(80,"%s(%s)借阅%s(%s) %s",Stu->StuName,Stu->StuNum,Bok->BookName,Bok->BookNum,LogInfo?"失败":"成功");
					
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//还书
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   还书   > > >",0X8F,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入借阅者信息及书籍信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");
					StringAtW(2,9,"编号:");
					StringAtW(2,10,"书名:");
					StringAtW(2,11,"出版:");

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
						DrawShadowStringBox(15,8,"未查找到！",0XF0,0X80);
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
						OutCutString(80,"归还 书籍 失败");
					else
						OutCutString(80,"%s 归还 书籍 %s 成功",FindFirstStudent(Bor->StuNum,0,0),FindFirstBook(Bor->BookNum,0,0));
					
					ConWaitKey(0);
				}
				break;
			case 2://展示借阅列表
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   查看   > > >",0X8B,0XF0);

					SetCursor(20,0);
					SetCurPosW(0,4);
					ShowBorrowList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//查询
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   查询   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入借阅者信息及书籍信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");
					StringAtW(2,9,"编号:");
					StringAtW(2,10,"书名:");
					StringAtW(2,11,"出版:");

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
						DrawShadowStringBox(15,8,"未查找到！",0XF0,0X80);
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
			case 4:{	//修改
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入借阅者信息及书籍信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");
					StringAtW(2,9,"编号:");
					StringAtW(2,10,"书名:");
					StringAtW(2,11,"出版:");

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
						DrawShadowStringBox(15,8,"未查找到！",0XF0,0X80);
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

					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请完善借阅信息(无需修改回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"编号:");
					StringAtW(2,7,"借出:");
					StringAtW(2,8,"归还:");
					StringAtW(2,9,"罚款:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%ld",&BData);else BData=-1;
					SetCurPosW(5,8);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%ld",&RData);else RData=-1;
					SetCurPosW(5,9);gets(Buffer[2]);if(Buffer[3][0])sscanf(Buffer[3],"%lf",&Fine);else Fine=-1.0;


					//修改信息
					ModifyBorrow(Bor,Buffer[0],Buffer[1],BData,RData,Fine);

					DrawShadowStringBox(15,7,"  修改成功！",0XF0,0X80);
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

void StuMng()	//学生管理
{
ReturnToFunBegin:
	SaveStu();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"学 生 管 理");
	//本来是要鼠标操作
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         注      册         ",
		"         注      销         ",
		"         查      看         ",
		"         查      询         ",
		"         修      改         "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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
				{	//借阅
					ClearScreen();
					char Buffer[3][128];
					DrawShadowStringBox(15,0,"< < <   注册   > > >",0X8B,0XF0);

					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请完善学生的信息");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

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
						DrawShadowStringBox(15,7,"信息不完整",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					if(Stu!=NULL)
					{
						DrawShadowStringBox(15,7,"学号已存在",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					if(AddStudent(Buffer[0],Buffer[1],Buffer[2]))
					{
						DrawShadowStringBox(15,7,"学生注册成功",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					else
					{
						DrawShadowStringBox(15,7,"注册失败！",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//注销
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   注销   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入学生信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

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
						DrawShadowStringBox(15,7,"未查找到！",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					SetCurPosW(2,11);
					ShowStudent(Stu);

					DrawShadowStringBox(15,7,"确认删除？(Y/N) ",0X8C,0XF0);
					char ch=ConWaitKey(5,'Y','y','N','n',27);
					if(ch=='Y'||ch=='y'){
						RemoveStudent(Stu);
						DrawShadowStringBox(15,7,"    删除成功！  ",0X8C,0XF0);
						ConWaitKey(0);
					}
					break;					
				}
				break;
			case 2://展示学生列表
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   查看   > > >",0X8B,0XF0);

					SetCursor(20,0);
					SetCurPosW(0,4);

					ShowStudentList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//查询
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   查询   > > >",0X8B,0XF0);

					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入学生信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

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
						DrawShadowStringBox(15,7,"未查找到！",0X8C,0XF0);
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
			case 4://修改
				{
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入学生信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

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
						DrawShadowStringBox(15,7,"未查找到！",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}

					//修改
					
					ClearScreen();
					SetCurPosW(2,11);
					ShowStudent(Stu);
					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请完善学生的信息(无需修改回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);

					SetCursor(20,0);


					if(Buffer[0][0]&&FindFirstStudent(Buffer[0],0,0))
					{
						DrawShadowStringBox(15,7,"学号已存在",0X8C,0XF0);
						ConWaitKey(0);
						break;
					}
					//修改信息
					ModifyStudent(Stu,Buffer[0],Buffer[1],Buffer[2]);


					DrawShadowStringBox(15,7,"  修改成功！",0X8C,0XF0);
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
void BokMng()	//图书管理
{
ReturnToFunBegin:
	SaveBok();
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"图 书 管 理");
	//本来是要鼠标操作
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         添      加         ",
		"         移      除         ",
		"         查      看         ",
		"         查      询         ",
		"         修      改         "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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
				{	//借阅
					ClearScreen();
					char Buffer[4][128];
					double Price;
					DrawShadowStringBox(15,0,"< < <   添加   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请完善图书的信息");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"编号:");
					StringAtW(2,6,"书名:");
					StringAtW(2,7,"出版:");
					StringAtW(2,8,"单价:");

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
						DrawShadowStringBox(15,8,"信息不完整",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					if(Bok!=NULL)
					{
						DrawShadowStringBox(15,8,"编号已存在",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					if(AddBook(Buffer[0],Buffer[1],Buffer[2],Price))
					{
						DrawShadowStringBox(15,8,"图书已添加！",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					else
					{
						
						DrawShadowStringBox(15,8,"添加失败！",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					ConWaitKey(0);
				}
				break;
			case 1:
				{	//移除
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   移除   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入图书信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"编号:");
					StringAtW(2,6,"书名:");
					StringAtW(2,7,"出版:");

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
						
						DrawShadowStringBox(15,7,"未查找到！",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					SetCurPosW(2,11);
					ShowBook(Bok);

					DrawShadowStringBox(15,7,"确认删除？(Y/N) ",0XF0,0X80);
					char ch=ConWaitKey(5,'Y','y','N','n',27);
					if(ch=='Y'||ch=='y'){
						RemoveBook(Bok);
						DrawShadowStringBox(15,7,"    删除成功！  ",0XF0,0X80);
						ConWaitKey(0);
					}
					break;					
				}
				break;
			case 2://展示图书列表
				{
					ClearScreen();
					DrawShadowStringBox(15,0,"< < <   查看   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);

					SetCursor(20,0);
					SetCurPosW(0,4);

					ShowBookList();
					ConWaitKey(0);
				}
				break;
			case 3:{	//查询
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   查询   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入图书信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"编号:");
					StringAtW(2,6,"书名:");
					StringAtW(2,7,"出版:");

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
						DrawShadowStringBox(15,7,"未查找到！",0XF0,0X80);
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
			case 4://修改
				{
					ClearScreen();
					char Buffer[4][128];

					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入图书信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"编号:");
					StringAtW(2,6,"书名:");
					StringAtW(2,7,"出版:");

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
						
						DrawShadowStringBox(15,7,"未查找到！",0XF0,0X80);
						ConWaitKey(0);
						break;
					}

					//修改
					double Price;
					int HasBorrow;
					ClearScreen();
					SetCurPosW(2,11);
					ShowBook(Bok);

					DrawShadowStringBox(15,0,"< < <   修改   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请完善图书的信息(无需修改回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"编号:");
					StringAtW(2,6,"书名:");
					StringAtW(2,7,"出版:");
					StringAtW(2,8,"单价:");
					StringAtW(2,9,"状态:");

					SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);

					SetCurPosW(5,5);gets(Buffer[0]);
					SetCurPosW(5,6);gets(Buffer[1]);
					SetCurPosW(5,7);gets(Buffer[2]);
					SetCurPosW(5,8);gets(Buffer[3]);if(Buffer[3][0])sscanf(Buffer[3],"%lf",&Price);else Price=-1.0;
					SetCurPosW(5,9);gets(Buffer[3]);if(Buffer[3][0])sscanf(Buffer[3],"%d",&HasBorrow);else HasBorrow=-1;

					SetCursor(20,0);

					if(Buffer[0][0]&&FindFirstBook(Buffer[0],0,0))
					{
						DrawShadowStringBox(15,7," 编号已存在 ",0XF0,0X80);
						ConWaitKey(0);
						break;
					}
					//修改信息
					ModifyBook(Bok,Buffer[0],Buffer[1],Buffer[2],Price,HasBorrow);


					DrawShadowStringBox(15,7,"  修改成功！",0XF0,0X80);
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
void Fine()		//逾期罚款
{
ReturnToFunBegin:
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,8,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"逾 期 罚 款");
	//本来是要鼠标操作
	int OptionNum=2;
	static char OptionStr[2][29]=
	{		
		"         个      人         ",
		"         全      体         "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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
				{	//个人
					ClearScreen();
					char Buffer[3][128];

					DrawShadowStringBox(15,0,"< < <   个人   > > >",0X8B,0XF0);
					SetConsoleTextAttribute(HConsoleOut,0X0B);
					StringAtW(10,4,"请输入学生信息(未知信息可回车跳过)");

					SetConsoleTextAttribute(HConsoleOut,0X0C);

					StringAtW(2,5,"学号:");
					StringAtW(2,6,"姓名:");
					StringAtW(2,7,"院系:");

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
						DrawShadowStringBox(15,7,"未查找到！",0XF0,0X80);
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
					DrawShadowStringBox(15,0,"< < <   全体   > > >",0X8B,0XF0);

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
void SysSet()	//系统设置
{
	ClearScreen();
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,11,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"系 统 设 置");
	//本来是要鼠标操作
	int OptionNum=5;
	static char OptionStr[5][29]=
	{		
		"         暂      未         ",
		"         开      放         ",
		"  ---+<华丽丽的分割线>+---  ",
		"         作      者         ",
		"         朱  广  锋         "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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



MenuMsg Menu()//主菜单
{
	SetCursor(20,0);
	ClearScreen();
	SetConsoleTextAttribute(HConsoleOut,BoxCol);
	DrawShadowBox(9,1,29,3,BoxCol,0XF0,
		"╔","═","╗",
		"║","  ","║",
		"╟","─","╢");
	DrawShadowBox(9,4,29,12,BoxCol,0XF0,
		"║","  ","║",
		"║","  ","║",
		"╚","═","╝");
	
	SetConsoleTextAttribute(HConsoleOut,TitleCol);
	StringAtW(16,2,"图书管理系统");

	//本来是要鼠标操作
	int OptionNum=6;
	static char MenuOptionStr[6][32]=
	{		
		"      借  阅  管  理      ",
		"      学  生  管  理      ",
		"      图  书  管  理      ",
		"      逾  期  罚  款      ",
		"      系  统  设  置      ",
		"      退  出  系  统      "
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
			27,//Esc退出
			-32,//拓展键
			13,//回车
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

