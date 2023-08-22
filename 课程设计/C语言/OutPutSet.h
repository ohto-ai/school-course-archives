#ifndef _OUTPUTSET_H_
#define _OUTPUTSET_H_



#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifndef _MaxCutStringLen_
#define _MaxCutStringLen_ 511
#endif

static char*_00="�X";
static char*_01="�T";
static char*_02="�[";

static char*_10="�U";
static char*_11="  ";
static char*_12="�U";

static char*_20="�^";
static char*_21="�T";
static char*_22="�a"; 


void SetCurPos(int x, int y)  
{  
    COORD pos = {x, y};  
    SetConsoleCursorPosition(HConsoleOut, pos);  
}


void SetCurPosW(int Wx, int Wy)  
{  
    COORD pos = {Wx*2, Wy};  
    SetConsoleCursorPosition(HConsoleOut, pos);  
}

int OutCutString(int Len,const char*Formt,...)
{
	if(Len<0||Len>_MaxCutStringLen_)
		return -1;
	if(Len==0)
		Len=_MaxCutStringLen_;
	bool IsChinese=false;
	static int i;
	static int TrueLen;
	static char _OutTextBuff[_MaxCutStringLen_+1];			//�ַ���������
	static va_list valist;					//�����б�
	va_start(valist,Formt);					//��ò���ָ��
	TrueLen=vsprintf(_OutTextBuff,Formt,valist);	//װ�뻺��
	va_end(valist);							//��������ָ��
	if(TrueLen>Len)//����
	{
		for(i=0;i<Len-3;i++){
			if(_OutTextBuff[i]<0)//�����ַ�
				IsChinese=!IsChinese;
		}
		if(IsChinese)//��ǰ���Ļᱻ�ض�
			_OutTextBuff[Len-4]=' ';
		_OutTextBuff[Len-3]='.';
		_OutTextBuff[Len-2]='.';
		_OutTextBuff[Len-1]='.';
		_OutTextBuff[Len-0]=NULL;
	}
	return printf(_OutTextBuff);
}
void ClearScreen(void)
{
	SetConsoleTextAttribute(HConsoleOut,0X0F);
	system("@cls");
	SetCurPos(0,0);
}
/*
void ClearScreen(void)
{
	COORD Home = {0, 0};
	WORD Attrib=ConScrBuffInfo.wAttributes;
	DWORD Size =ConScrBuffInfo.dwSize.X*ConScrBuffInfo.dwSize.Y;
	FillConsoleOutputAttribute(HConsoleOut,Attrib,Size,Home,NULL);
	FillConsoleOutputCharacter(HConsoleOut,' ',Size,Home,NULL);
}
*/


void StringAt(int x, int y,char*String)  
{  
    COORD pos = {x, y};  
    SetConsoleCursorPosition(HConsoleOut, pos);
	printf(String);
}
void StringAtW(int Wx, int Wy,char*String)  
{  
    COORD pos = {Wx*2, Wy};  
    SetConsoleCursorPosition(HConsoleOut, pos);
	printf(String);
}
void SetCursor(DWORD dwSize,int bVisable)//���ÿ���̨�Ĺ��
{
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize=dwSize;
	cursor_info.bVisible=bVisable;
	SetConsoleCursorInfo(HConsoleOut, &cursor_info);
}


void DrawBox(int Wleft,int Wtop,int Wright,int Wbottom,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22)
{
	int i,j;
	//�X�j�[�d�p�g�^�m�a�T�b�c�e�f�n�U�h�i�k�l�o�V�Y�\�_
	static char BoxBuff[3][512];

	//��һ��
	strcpy(BoxBuff[0],_00);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[0],_01);
	}
	strcat(BoxBuff[0],_02);

	//�м�
	strcpy(BoxBuff[1],_10);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[1],_11);
	}
	strcat(BoxBuff[1],_12);

	//���һ��
	strcpy(BoxBuff[2],_20);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[2],_21);
	}
	strcat(BoxBuff[2],_22);
	
	SetCurPosW(Wleft,Wtop);
	puts(BoxBuff[0]);				//��һ��
	for(j=Wtop+1;j<Wbottom;++j)		//�м�
	{
		SetCurPosW(Wleft,j);
		puts(BoxBuff[1]);
	}
	SetCurPosW(Wleft,Wbottom);
	puts(BoxBuff[2]);				//���һ��
}
void DrawBox(int Wleft,int Wtop,int Wright,int Wbottom)
{
	DrawBox(Wleft,Wtop,Wright,Wbottom,
		"�X","�T","�[",
		"�U","  ","�U",
		"�^","�T","�a");
}


void DrawShadowStringBox(int Wx,int Wy,char*Str,int BoxColor,int ShadowColor,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22)
{
	int i;
	int WLen=(int)((strlen(Str)+1)/2);

	static char BoxBuff[4][512];

	//��һ��
	strcpy(BoxBuff[0],_00);
	for(i=0;i<WLen;++i)
	{
		strcat(BoxBuff[0],_01);
	}
	strcat(BoxBuff[0],_02);

	//�м�
	strcpy(BoxBuff[1],_10);
	strcat(BoxBuff[1],Str);
	strcat(BoxBuff[1],_12);

	//���һ��
	strcpy(BoxBuff[2],_20);
	for(i=0;i<WLen;++i)
	{
		strcat(BoxBuff[2],_21);
	}
	strcat(BoxBuff[2],_22);

	//��Ӱ
	for(i=0;i<WLen+2;++i)
	{
		BoxBuff[3][i*2]=' ';
		BoxBuff[3][i*2+1]=' ';
	}
	BoxBuff[3][i*2]=0;
	SetConsoleTextAttribute(HConsoleOut,BoxColor);
	SetCurPosW(Wx,Wy);
	puts(BoxBuff[0]);				//��һ��
	SetCurPosW(Wx,Wy+1);
	puts(BoxBuff[1]);
	SetCurPosW(Wx,Wy+2);
	puts(BoxBuff[2]);				//���һ��
	//��Ӱ
	SetConsoleTextAttribute(HConsoleOut,ShadowColor);
	SetCurPos(Wx*2+1,Wy+3);
	puts(BoxBuff[3]);
	SetCurPosW(Wx+WLen+2,Wy+1);
	putchar(' ');
	SetCurPosW(Wx+WLen+2,Wy+2);
	putchar(' ');
}
void DrawShadowStringBox(int Wx,int Wy,char*Str,int BoxColor,int ShadowColor)
{
	DrawShadowStringBox(Wx,Wy,Str,BoxColor,ShadowColor,
		"�X","�T","�[",
		"�U","  ","�U",
		"�^","�T","�a");
}
void DrawShadowBox(int Wleft,int Wtop,int Wright,int Wbottom,
				   int BoxColor,int ShadowColor,
			 char*_00,char*_01,char*_02,
			 char*_10,char*_11,char*_12,
			 char*_20,char*_21,char*_22)
{
	
	static char BoxBuff[4][512];
	int i;
	
	//��һ��
	strcpy(BoxBuff[0],_00);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[0],_01);
	}
	strcat(BoxBuff[0],_02);

	//�м�
	strcpy(BoxBuff[1],_10);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[1],_11);
	}
	strcat(BoxBuff[1],_12);

	//���һ��
	strcpy(BoxBuff[2],_20);
	for(i=Wleft+1;i<Wright;++i)
	{
		strcat(BoxBuff[2],_21);
	}
	strcat(BoxBuff[2],_22);
	//��Ӱ
	for(i=0;i<Wright-Wleft+1;++i)
	{
		BoxBuff[3][i*2]="  �I����"[0];//�I��
		BoxBuff[3][i*2+1]="  ���I"[1];
	}

	//����
	SetConsoleTextAttribute(HConsoleOut,BoxColor);

	SetCurPosW(Wleft,Wtop);
	puts(BoxBuff[0]);				//��һ��

	for(i=Wtop+1;i<Wbottom;++i)		//�м�
	{
		SetCurPosW(Wleft,i);
		puts(BoxBuff[1]);
	}

	SetCurPosW(Wleft,Wbottom);
	puts(BoxBuff[2]);				//���һ��


	//��Ӱ
	SetConsoleTextAttribute(HConsoleOut,ShadowColor);
	for(i=Wtop+1;i<Wbottom;++i)		//�м�
	{
		SetCurPosW(Wright+1,i);
		putchar(' ');
	}
	SetCurPosW(Wright+1,Wbottom);
	putchar(' ');

	SetCurPos(Wleft*2+1,Wbottom+1);
	puts(BoxBuff[3]);				//���һ��
}



#endif




