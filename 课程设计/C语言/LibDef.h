#ifndef _LIB_DEF_H_
#define _LIB_DEF_H_


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#ifndef TEXT_DEF_COL
#define TEXT_DEF_COL 0X0F
#endif

#ifndef TEXT_STU_COL
#define TEXT_STU_COL 0X0A		//ѧ���б���ɫ
#endif

#ifndef TEXT_BOK_COL
#define TEXT_BOK_COL 0X0E		//�鼮�б���ɫ 
#endif

#ifndef TEXT_BOK_COL_D
#define TEXT_BOK_COL_D 0X01		//δ���鼮�б���ɫ
#endif

#ifndef TEXT_BOR_COL
#define TEXT_BOR_COL 0X0C		//�����б���ɫ
#endif

#ifndef TEXT_BOR_COL_D
#define TEXT_BOR_COL_D 0X01		//δ�������б���ɫ
#endif

#ifndef TEXT_FINE_COL
#define TEXT_FINE_COL 0X0D		//�����ɫ
#endif

#ifndef TEXT_TITLE_COL
#define TEXT_TITLE_COL 0X0408
#endif

#ifndef _Borrow_Days_Limit
#define _Borrow_Days_Limit (30)	//��������
#endif

#ifndef _SecondPerDay
#define _SecondPerDay (86400) //60*60*24
#endif


/*****************�ڵ㶨��*******************/
//ѧ������ڵ�
typedef struct tag_StuNode
{
	char StuNum[32];		//ѧ��
	char StuName[32];		//����
	char Department[32];	//ϵ��

	struct tag_StuNode		*Last;
	struct tag_StuNode		*Next;
}StuNode,*StuNodeLink;


//ͼ������ڵ�
typedef struct tag_BokNode
{
	char BookNum[32];		//���
	char BookName[32];		//����
	char PublishHouse[32];	//������
	bool HasBorrow;			//�Ƿ���
	double Price;			//����

	struct tag_BokNode		*Last;
	struct tag_BokNode		*Next;
}BokNode,*BokNodeLink;

//��������ڵ�
typedef struct tag_BorNode
{
	char StuNum[32];		//ѧ��
	char BookNum[32];		//���
	time_t BDate;			//��������
	time_t RDate;			//�������� 0��ʾ��δ�黹
	double Fine;			//����

	struct tag_BorNode		*Last;
	struct tag_BorNode		*Next;
}BorNode,*BorNodeLink;


/*****************��������*******************/
//���ѧ��
StuNodeLink AddStudent	(char*StuNum,char*StuName,char*Department);
//����鼮
BokNodeLink AddBook		(char*BokNum,char*BokName,char*PublishHouse,double Price);

//�軹��¼
int LogBor(StuNodeLink Stu,BokNodeLink Bok);//����
int LogRet(BorNodeLink Bor);				//����

//�����ʼ������
void InitStudent(int N);
void InitBook(int N);
void InitBorrow(int N);


//����
StuNodeLink FindStudent	(char*StuNum,char*StuName,char*Department);
BokNodeLink FindBook	(char*BokNum,char*BokName,char*PublishHouse);
BorNodeLink FindBorrow	(StuNodeLink Stu,BokNodeLink Bok);
BorNodeLink FindUnRet	(StuNodeLink Stu,BokNodeLink Bok);

StuNodeLink FindFirstStudent(char*StuNum,char*StuName,char*Department);
BokNodeLink FindFirstBook	(char*BokNum,char*BokName,char*PublishHouse);
BorNodeLink FindFirstBorrow	(StuNodeLink Stu,BokNodeLink Bok);

StuNodeLink GetLastFindStudent	(void);
StuNodeLink ResetLastFindStudent(void);

BokNodeLink GetLastFindBook		(void);
BokNodeLink ResetLastFindBook	(void);

BorNodeLink GetLastFindBorrow	(void);
BorNodeLink ResetLastFindBorrow	(void);


//ɾ��
void RemoveStudent	(StuNodeLink Stu);
void RemoveBook		(BokNodeLink Bok);
void RemoveBorrow	(BorNodeLink Bor);
//�����ڴ�
void FreeStu();
void FreeBok();
void FreeBor();
//�޸�

StuNodeLink ModifyStudent	(StuNodeLink Stu,char*StuNum,char*StuName,char*Department);
BokNodeLink ModifyBook		(BokNodeLink Bok,char*BokNum,char*BokName,char*PublishHouse,double Price,int HasBorrow);//Price<0 HasBorrow<0��ʾ���ı� 
BorNodeLink ModifyBorrow	(BorNodeLink Bor,char*StuNum,char*BookNum,time_t BDate,time_t RDate,double Fine);

//�軹��¼
int LogBor(StuNodeLink Stu,BokNodeLink Bok);//����

//����
double	CalculateFine(BorNodeLink Bor);
int		CountStudent();
int		CountBook();
int		CountBorrow();


//��ʾ
int ShowStudent		(StuNodeLink Stu);
int ShowBook		(BokNodeLink Bok);
int ShowBorrow		(BorNodeLink Bor);
int ShowStudentList	(void);
int ShowBookList	(void);
int ShowBorrowList	(void);

int ShowFine		(StuNodeLink Stu);
int ShowFineList	();


//��������
int SaveStu();
int SaveBor();
int SaveBok();
int SaveData();

int ReadStu();
int ReadBor();
int ReadBok();
int ReadData();

#endif
