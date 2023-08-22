#ifndef _MENU_H_
#define _MENU_H_

#ifndef TEXT_DEF_COL
#define TEXT_DEF_COL 0X0F
#endif

#ifndef TEXT_TIELE_COL
#define TEXT_TIELE_COL 0X8A
#endif

#ifndef TEXT_TAB_COL
#define TEXT_TAB_COL 0X8F
#endif

#ifndef TEXT_OPTION_COL
#define TEXT_OPTION_COL 0X8E
#endif


#ifndef TEXT_OPTION_COL_C
#define TEXT_OPTION_COL_C 0X4A 
#endif


typedef enum tag_MenuMsg
{
	Menu_BorMng=1,	//借阅管理
	Menu_StuMng,	//学生管理
	Menu_BokMng,	//图书管理
	Menu_Fine,		//逾期罚款
	Menu_SysSet,	//系统设置
	Menu_ExtSys,	//退出系统

	Menu_Error=-1,	//出错
	Menu_Null=0		//空指令
}MenuMsg;

MenuMsg Menu();	//菜单
void BorMng();	//借阅管理
void StuMng();	//学生管理
void BokMng();	//图书管理
void Fine();	//逾期罚款
void SysSet();	//系统设置

extern HANDLE HConsoleIn;
extern HANDLE HConsoleOut;
extern INPUT_RECORD InputRec;						//定义输入事件结构体  
extern COORD MousePos;								//鼠标位置
extern CONSOLE_SCREEN_BUFFER_INFO ConScrBuffInfo;	//窗口缓冲区信息
extern void ClearScreen(void);

extern void SetCursor(DWORD dwSize,int bVisable);
extern void SetCurPos(int x, int y);
extern void SetCurPosW(int Wx, int Wy);
extern void StringAt(int,int,char*);
extern void StringAtW(int,int,char*);

extern char ConWaitKey(int,...);
extern int OutCutString(int Len,const char*Formt,...);
extern void DrawBox(int Wleft,int Wtop,int Wright,int Wbottom);
extern void DrawBox(int Wleft,int Wtop,int Wright,int Wbottom,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22);

extern void DrawShadowStringBox(int Wx,int Wy,char*Str,int BoxColor,int ShadowColor);
extern void DrawShadowStringBox(int Wx,int Wy,char*Str,int BoxColor,int ShadowColor,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22);
extern void DrawShadowBox(int Wleft,int Wtop,int Wright,int Wbottom,int BoxColor,int ShadowColor,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22);
#endif