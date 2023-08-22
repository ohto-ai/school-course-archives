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
#define TEXT_STU_COL 0X0A		//学生列表颜色
#endif

#ifndef TEXT_BOK_COL
#define TEXT_BOK_COL 0X0E		//书籍列表颜色 
#endif

#ifndef TEXT_BOK_COL_D
#define TEXT_BOK_COL_D 0X01		//未还书籍列表颜色
#endif

#ifndef TEXT_BOR_COL
#define TEXT_BOR_COL 0X0C		//借阅列表颜色
#endif

#ifndef TEXT_BOR_COL_D
#define TEXT_BOR_COL_D 0X01		//未还借阅列表颜色
#endif

#ifndef TEXT_FINE_COL
#define TEXT_FINE_COL 0X0D		//罚款单颜色
#endif

#ifndef TEXT_TITLE_COL
#define TEXT_TITLE_COL 0X0408
#endif

#ifndef _Borrow_Days_Limit
#define _Borrow_Days_Limit (30)	//借阅期限
#endif

#ifndef _SecondPerDay
#define _SecondPerDay (86400) //60*60*24
#endif


/*****************节点定义*******************/
//学生链表节点
typedef struct tag_StuNode
{
	char StuNum[32];		//学号
	char StuName[32];		//姓名
	char Department[32];	//系部

	struct tag_StuNode		*Last;
	struct tag_StuNode		*Next;
}StuNode,*StuNodeLink;


//图书链表节点
typedef struct tag_BokNode
{
	char BookNum[32];		//编号
	char BookName[32];		//书名
	char PublishHouse[32];	//出版社
	bool HasBorrow;			//是否借出
	double Price;			//单价

	struct tag_BokNode		*Last;
	struct tag_BokNode		*Next;
}BokNode,*BokNodeLink;

//借阅链表节点
typedef struct tag_BorNode
{
	char StuNum[32];		//学号
	char BookNum[32];		//编号
	time_t BDate;			//借书日期
	time_t RDate;			//还书日期 0表示尚未归还
	double Fine;			//罚款

	struct tag_BorNode		*Last;
	struct tag_BorNode		*Next;
}BorNode,*BorNodeLink;


/*****************函数声明*******************/
//添加学生
StuNodeLink AddStudent	(char*StuNum,char*StuName,char*Department);
//添加书籍
BokNodeLink AddBook		(char*BokNum,char*BokName,char*PublishHouse,double Price);

//借还记录
int LogBor(StuNodeLink Stu,BokNodeLink Bok);//借书
int LogRet(BorNodeLink Bor);				//还书

//随机初始化数据
void InitStudent(int N);
void InitBook(int N);
void InitBorrow(int N);


//查找
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


//删除
void RemoveStudent	(StuNodeLink Stu);
void RemoveBook		(BokNodeLink Bok);
void RemoveBorrow	(BorNodeLink Bor);
//清理内存
void FreeStu();
void FreeBok();
void FreeBor();
//修改

StuNodeLink ModifyStudent	(StuNodeLink Stu,char*StuNum,char*StuName,char*Department);
BokNodeLink ModifyBook		(BokNodeLink Bok,char*BokNum,char*BokName,char*PublishHouse,double Price,int HasBorrow);//Price<0 HasBorrow<0表示不改变 
BorNodeLink ModifyBorrow	(BorNodeLink Bor,char*StuNum,char*BookNum,time_t BDate,time_t RDate,double Fine);

//借还记录
int LogBor(StuNodeLink Stu,BokNodeLink Bok);//借书

//计算
double	CalculateFine(BorNodeLink Bor);
int		CountStudent();
int		CountBook();
int		CountBorrow();


//显示
int ShowStudent		(StuNodeLink Stu);
int ShowBook		(BokNodeLink Bok);
int ShowBorrow		(BorNodeLink Bor);
int ShowStudentList	(void);
int ShowBookList	(void);
int ShowBorrowList	(void);

int ShowFine		(StuNodeLink Stu);
int ShowFineList	();


//保存数据
int SaveStu();
int SaveBor();
int SaveBok();
int SaveData();

int ReadStu();
int ReadBor();
int ReadBok();
int ReadData();

#endif
