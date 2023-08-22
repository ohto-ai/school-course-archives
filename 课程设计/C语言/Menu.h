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
	Menu_BorMng=1,	//���Ĺ���
	Menu_StuMng,	//ѧ������
	Menu_BokMng,	//ͼ�����
	Menu_Fine,		//���ڷ���
	Menu_SysSet,	//ϵͳ����
	Menu_ExtSys,	//�˳�ϵͳ

	Menu_Error=-1,	//����
	Menu_Null=0		//��ָ��
}MenuMsg;

MenuMsg Menu();	//�˵�
void BorMng();	//���Ĺ���
void StuMng();	//ѧ������
void BokMng();	//ͼ�����
void Fine();	//���ڷ���
void SysSet();	//ϵͳ����

extern HANDLE HConsoleIn;
extern HANDLE HConsoleOut;
extern INPUT_RECORD InputRec;						//���������¼��ṹ��  
extern COORD MousePos;								//���λ��
extern CONSOLE_SCREEN_BUFFER_INFO ConScrBuffInfo;	//���ڻ�������Ϣ
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