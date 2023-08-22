#include <GL/glut.h>
#include<windows.h>
#include<iostream>
#include"TimeStateChange.h"
#include<cstring>
#include"Run.h"
//定义10个GLfloat类型，用于跟踪，十架电梯的坐标
//以便于进行状态更新
using namespace std;
#define MAX_CHAR  128
int TimeCount=0;
char TimeSecond[3];
char TimeMinute[3];
int TimeButton[10][11];
int AllStopTime[10];
int AllElevatorPersonNumber[10];
int AllCurrentfloor[10];
int AllFloorPersonNumber[11];
int AllFloorElevatorNumber[11];
int AllElevatorState[10];
char Statestr[10][10];
char Numstr[10][10];
char ElevatorNumberstr[11][10];
char AllPeopleNumber[4]="000";
char FloorPerNumStr[11][4];
int GetState(int ElevatorNumber);
void GetAllPeopleNumber();
void ChooseFNumber(int floor,int digit,int i);
void SetWordState();
void SetTime();
void ChooseTSNumber(int Sdigit,int i);
void GetFloorPerNum(int floor);
void ChooseTMNumber(int Mdigit,int i);
int i=0;
GLfloat theta[10];
void RunStateChange();
void ChooseNumber(int digit,int i);
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;
    if( isFirstCall ) { // 如果是第一次调用，执行初始化
// 为每一个ASCII字符产生一个显示列表
        isFirstCall = 0;
        // 申请MAX_CHAR个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);
        // 把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);
}

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}
void display()////利用该函数画图
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);//画出背景
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.8,0.7);
	glColor3f(1.0,0.4,0);
	glVertex2f(-0.8,-0.8);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(0.8,-0.8);
	glColor3f(1.0,0.6,0);
	glVertex2f(0.8,0.7);
	glEnd();
	
	
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.7);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-1.0,0.7);
	glColor3f(1.0,0.4,0);
	glVertex2f(-0.8,0.7);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.8,-0.8);
	glColor3f(1.0,0.6,0);
	glVertex2f(-1.0,-0.8);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-1.0,-0.8);
	glColor3f(1.0,0.4,0);
	glVertex2f(0.8,-0.8);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(0.8,-0.98);
	glColor3f(1.0,0.6,0);
	glVertex2f(-1.0,-0.98);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-1.0,0.8);
	glColor3f(1.0,0.4,0);
	glVertex2f(-0.8,0.8);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.8,0.7);
	glColor3f(1.0,0.6,0);
	glVertex2f(-1.0,0.7);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.8,0.7);
	glColor3f(1.0,0.4,0);
	glVertex2f(-0.75,0.8);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(0.85,0.8);
	glColor3f(1.0,0.6,0);
	glVertex2f(0.8,0.7);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(0.8,0.7);
	glColor3f(1.0,0.4,0);
	glVertex2f(0.85,0.8);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(0.85,-0.9);
	glColor3f(1.0,0.6,0);
	glVertex2f(0.8,-0.99);
	glEnd();

	//画出底层显示板
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.98);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,-0.98);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.98);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.98);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,-0.88);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,-0.88);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,-0.7);
	glEnd();
	
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.98);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.98);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.98);
	glEnd();

	//画出上沿说明图
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-1.0,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,-0.7);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.85,-0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.8);
	glEnd();
    
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.8);
	glEnd();

	//画出电梯图
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(-0.7,theta[0]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(-0.6,theta[0]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(-0.6,theta[0]);
	glVertex2f(-0.7,theta[0]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(-0.55,theta[1]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(-0.45,theta[1]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(-0.45,theta[1]);
	glVertex2f(-0.55,theta[1]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(-0.4,theta[2]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(-0.3,theta[2]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(-0.3,theta[2]);
	glVertex2f(-0.4,theta[2]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(-0.25,theta[3]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(-0.15,theta[3]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(-0.15,theta[3]);
	glVertex2f(-0.25,theta[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(-0.1,theta[4]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.0,theta[4]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.0,theta[4]);
	glVertex2f(-0.1,theta[4]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(0.05,theta[5]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.15,theta[5]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.15,theta[5]);
	glVertex2f(0.05,theta[5]);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(0.2,theta[6]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.3,theta[6]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.3,theta[6]);
	glVertex2f(0.2,theta[6]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(0.35,theta[7]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.45,theta[7]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.45,theta[7]);
	glVertex2f(0.35,theta[7]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(0.5,theta[8]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.6,theta[8]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.6,theta[8]);
	glVertex2f(0.5,theta[8]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5,0.15,0);
	glVertex2f(0.65,theta[9]+0.1);
	glColor3f(0.5,0.5,0);
	glVertex2f(0.75,theta[9]+0.1);
	glColor3f(0.5,0.65,0);
	glVertex2f(0.75,theta[9]);
	glVertex2f(0.65,theta[9]);
	glEnd();
	
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.75);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.8);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.8);
	glEnd();

	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.7);
	glEnd();
	


	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.6);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.65);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.65);
	glEnd();






   
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.45);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.5);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.5);
	glEnd();





	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.3);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.35);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.35);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.35);
	glEnd();





	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.15);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.2);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.2);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.2);
	glEnd();





    glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.05);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.05);
	glEnd();



	
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.15);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,0.1);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,0.1);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.1);
	glEnd();
	


	
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.3);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,0.25);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.25);
	glEnd();
	


	
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.45);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,0.4);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,0.4);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.4);
	glEnd();
	
	
	glBegin(GL_LINE_STRIP);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.6);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,0.55);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,0.55);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.55);
	glEnd();
	

	glBegin(GL_LINES);//画出楼层线
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.8,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.7);
	glEnd();
	//////画出竖线
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.7,-0.75);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,0.65);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.75,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.6,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.55,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.45,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.4,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.3,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.25,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.15,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(-0.1,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.0,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.05,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.15,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.2,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.3,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.35,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.45,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.5,-0.8);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.6,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.65,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.75,-0.8);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,0.7);
	glColor3f(0.0,0.0,0.0);
	glVertex2f(0.8,-0.8);
	glEnd();


	//画出LXN图标
	/*glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,0.0);
	glVertex2f(-0.25,0.99);
	glColor3f(0.5,0.5,0.0);
	glVertex2f(-0.17,0.99);
	glColor3f(0.5,0.0,0.5);
	glVertex2f(-0.17,0.75);
    glColor3f(0.0,0.5,0.5);
	glVertex2f(-0.25,0.75);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,0.0);
	glVertex2f(-0.17,0.75);
	glColor3f(0.5,0.5,0.0);
	glVertex2f(-0.1,0.75);
	glColor3f(0.5,0.0,0.5);
	glVertex2f(-0.1,0.85);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(-0.17,0.85);
	glEnd();
	*/


	 SetWordState();

	glColor3f(1.0,1.0,1.0);
	 selectFont(17, ANSI_CHARSET, "MS Serif");
	 //此处开始书写文字
	 //以下表示状态
	 glRasterPos2f(-0.7f, theta[0]+0.025);
    drawString(Statestr[0]);

	glRasterPos2f(-0.55f, theta[1]+0.025);
    drawString(Statestr[1]);

	 glRasterPos2f(-0.4f, theta[2]+0.025);
    drawString(Statestr[2]);

	 glRasterPos2f(-0.25f, theta[3]+0.025);
    drawString(Statestr[3]);

	 glRasterPos2f(-0.1f, theta[4]+0.025);
    drawString(Statestr[4]);

	 glRasterPos2f(0.05f, theta[5]+0.025);
    drawString(Statestr[5]);

	 glRasterPos2f(0.2f, theta[6]+0.025);
    drawString(Statestr[6]);


	 glRasterPos2f(0.35f, theta[7]+0.025);
    drawString(Statestr[7]);


	 glRasterPos2f(0.5f, theta[8]+0.025);
    drawString(Statestr[8]);

	 glRasterPos2f(0.65f, theta[9]+0.025);
    drawString(Statestr[9]);
     
	//以下表示数字
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.63f, theta[0]+0.025);
    drawString(Numstr[0]);
	glRasterPos2f(-0.48f, theta[1]+0.025);
    drawString(Numstr[1]);
	glRasterPos2f(-0.33f, theta[2]+0.025);
    drawString(Numstr[2]);
	glRasterPos2f(-0.18f, theta[3]+0.025);
    drawString(Numstr[3]);
	glRasterPos2f(-0.03f, theta[4]+0.025);
    drawString(Numstr[4]);
	glRasterPos2f(0.12f, theta[5]+0.025);
    drawString(Numstr[5]);
	glRasterPos2f(0.27f, theta[6]+0.025);
    drawString(Numstr[6]);
	glRasterPos2f(0.42f, theta[7]+0.025);
    drawString(Numstr[7]);
	glRasterPos2f(0.57f, theta[8]+0.025);
    drawString(Numstr[8]);
	glRasterPos2f(0.72f, theta[9]+0.025);
    drawString(Numstr[9]);


	//以下表示电梯数
	 glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.85f, -0.75);
    drawString(ElevatorNumberstr[1]);
	glRasterPos2f(-0.85f, -0.6);
    drawString(ElevatorNumberstr[2]);
	glRasterPos2f(-0.85f, -0.45);
    drawString(ElevatorNumberstr[3]);
	glRasterPos2f(-0.85f, -0.3);
    drawString(ElevatorNumberstr[4]);
	glRasterPos2f(-0.85f, -0.15);
    drawString(ElevatorNumberstr[5]);
	glRasterPos2f(-0.85f, 0.0);
    drawString(ElevatorNumberstr[6]);
	glRasterPos2f(-0.85f, 0.15);
    drawString(ElevatorNumberstr[7]);
	glRasterPos2f(-0.85f, 0.3);
    drawString(ElevatorNumberstr[8]);
	glRasterPos2f(-0.85f, 0.45);
    drawString(ElevatorNumberstr[9]);
	glRasterPos2f(-0.85f, 0.6);
    drawString(ElevatorNumberstr[10]);

	//////////左层显示板，显示楼层数
	glColor3f(5.0,0.15,0.0);
	glRasterPos2f(-0.98f, -0.75);
    drawString("First");
	glRasterPos2f(-0.98f, -0.6);
    drawString("Second");
	glRasterPos2f(-0.98f, -0.45);
    drawString("Third");
	glRasterPos2f(-0.98f, -0.3);
    drawString("Forth");
	glRasterPos2f(-0.98f, -0.15);
    drawString("Fifth");
	glRasterPos2f(-0.98f, 0.0);
    drawString("Sixth");
	glRasterPos2f(-0.98f, 0.15);
    drawString("Seventh");
	glRasterPos2f(-0.98f, 0.3);
    drawString("Eighth");
	glRasterPos2f(-0.98f, 0.45);
    drawString("Ninth");
	glRasterPos2f(-0.98f, 0.6);
    drawString("Tenth");

	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.99f, -0.9);
    drawString("BuildingName:LXN");
	
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.7f, -0.9);
    drawString("TotalPeopleNumber:");
	
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.1f, -0.9);
    drawString("ElevatorNumber:Ten");

	//显示大楼的时间
	SetTime();
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(0.58f, -0.9);
    drawString(TimeMinute);

    glColor3f(0.0,0.0,0.0);
	glRasterPos2f(0.6f, -0.9);
    drawString(":");
   

	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(0.61f, -0.9);
    drawString(TimeSecond);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(0.42f, -0.9);
    drawString("BuildingTime:00:");



	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.98f, 0.75);
    drawString("F&ENumber");
	//显示总人数
	GetAllPeopleNumber();
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.5f, -0.9);
    drawString(AllPeopleNumber);
	
	
	//显示每层人数
	GetFloorPerNum(1);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, -0.75);
    drawString(FloorPerNumStr[1]);

	GetFloorPerNum(2);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, -0.6);
    drawString(FloorPerNumStr[2]);

	GetFloorPerNum(3);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, -0.45);
    drawString(FloorPerNumStr[3]);

	GetFloorPerNum(4);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, -0.3);
    drawString(FloorPerNumStr[4]);

	GetFloorPerNum(5);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, -0.15);
    drawString(FloorPerNumStr[5]);

	GetFloorPerNum(6);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, 0.0);
    drawString(FloorPerNumStr[6]);
	
	GetFloorPerNum(7);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, 0.15);
    drawString(FloorPerNumStr[7]);

	GetFloorPerNum(8);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, 0.3);
    drawString(FloorPerNumStr[8]);

	GetFloorPerNum(9);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, 0.45);
    drawString(FloorPerNumStr[9]);
	
	GetFloorPerNum(10);
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(-0.9f, 0.6);
    drawString(FloorPerNumStr[10]);
	



	glutSwapBuffers();
}
void myidle()//在此改变状态
{
	RunStateChange();
	glutPostRedisplay();
}
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);//背景颜色
	glColor3f(0.0,0.0,0.0);//图形颜色，若之前没定义颜色，该句可填充颜色
	glLineWidth(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glutIdleFunc(myidle);
}



void InitGraph()
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1200,600);
	glutInitWindowPosition(0,0);//表示生成的窗口出现在屏幕的位置
	glutCreateWindow("LXN_Building_ElevatorSystem");
	glutDisplayFunc(display);
    init();
	glutMainLoop();
}

void RunStateChange()
{
		if(i%100==0)
	{
	for(int j=0;j<10;j++)
	{//初始化电梯图形
	theta[j]=(LXN_Building.m_Elevator[j].m_State.GetCurrentfloor()-1)*0.15-0.8;
	}
	Run();//大楼的状态改变
	TimeCount+=5;
	}
		i++;
		Sleep(5);
	
	
	for(int k=0;k<10;k++)
	{
		if(AllStopTime[k]==0&&GetState(k)==1)
		{//如果该电梯下一步要动，而且方向向上
            theta[k]+=0.00145;
		}
		else if(AllStopTime[k]==0&&GetState(k)==2)
		{//如果该电梯下一步要动，而且方向向下
			theta[k]-=0.00145;
		}
	}
	
}
//第一层坐标：-0.8
//第二层坐标：-0.65
//第三层坐标：-0.5
//第四层坐标：-0.35
//第五层坐标：-0.2
//第六层坐标：-0.05
//第七层坐标：0.1
//第八层坐标：0.25
//第九层坐标：0.4
//第十层坐标：0.55
//房屋上沿坐标：0.7

int GetState(int ElevatorNumber)//判断电梯的下一方向
{
	
	int Upflag=0;
	int Downflag=0;
	for(int num=1;num<AllCurrentfloor[ElevatorNumber];num++)
	{
		if(TimeButton[ElevatorNumber][num]==ButtonPress)
			Downflag=1;
	}
	for(int num=AllCurrentfloor[ElevatorNumber]+1;num<11;num++)
	{
		if(TimeButton[ElevatorNumber][num]==ButtonPress)
			Upflag=1;
	}
	if(AllCurrentfloor[ElevatorNumber]==1&&AllStopTime[ElevatorNumber]==0)
		return 1;
	else
	{
	if(Upflag==1)
		return 1;//如果方向为上
	else if(Downflag==1)
		return 2;//如果方向为下
	else 
		return 0;//如果静止
	}
}

void SetWordState()
{

	for(int num=0;num<10;num++)
	{//设置电梯显示时，UP或DOWN,或者STOP
		if(GetState(num)==1&&AllStopTime[num]==0)//表明方向向上
		{
			strcpy_s(Statestr[num],"UP");
		}
		else if(GetState(num)==2&&AllStopTime[num]==0)//表明方向向下
		{
			strcpy_s(Statestr[num],"DOWN");
		}
		else //表明静止
		{
			strcpy_s(Statestr[num],"STOP");
		}
	}

	for(int num=0;num<10;num++)
	{//设置电梯显示时，每台电梯中的人数
		switch(AllElevatorPersonNumber[num])
		{
		case 0: strcpy_s(Numstr[num],"00");
			break;
		case 1: strcpy_s(Numstr[num],"01");
			break;
		case 2: strcpy_s(Numstr[num],"02");
			break;
		case 3: strcpy_s(Numstr[num],"03");
			break;
		case 4: strcpy_s(Numstr[num],"04");
			break;
		case 5: strcpy_s(Numstr[num],"05");
			break;
		case 6: strcpy_s(Numstr[num],"06");
			break;
		case 7: strcpy_s(Numstr[num],"07");
			break;
		case 8: strcpy_s(Numstr[num],"08");
			break;
		case 9: strcpy_s(Numstr[num],"09");
			break;
		case 10: strcpy_s(Numstr[num],"10");
			break;
		case 11: strcpy_s(Numstr[num],"11");
			break;
		case 12: strcpy_s(Numstr[num],"12");
			break;
		case 13: strcpy_s(Numstr[num],"13");
			break;
		case 14: strcpy_s(Numstr[num],"14");
			break;
		case 15: strcpy_s(Numstr[num],"15");
			break;
		case 16: strcpy_s(Numstr[num],"16");
			break;
		case 17: strcpy_s(Numstr[num],"17");
			break;
		case 18: strcpy_s(Numstr[num],"18");
			break;
		case 19: strcpy_s(Numstr[num],"19");
			break;
		case 20: strcpy_s(Numstr[num],"20");
			break;
		case 21: strcpy_s(Numstr[num],"21");
			break;
		case 22: strcpy_s(Numstr[num],"22");
			break;
		case 23: strcpy_s(Numstr[num],"23");
			break;
		case 24: strcpy_s(Numstr[num],"24");
			break;
		default: strcpy_s(Numstr[num],"error");
			break;
		}
	}

	for(int COUNT=1;COUNT<11;COUNT++)
	{
		switch(AllFloorElevatorNumber[COUNT])
		{
		case 0:strcpy_s(ElevatorNumberstr[COUNT],"00");
			break;
			case 1:strcpy_s(ElevatorNumberstr[COUNT],"01");
			break;
			case 2:strcpy_s(ElevatorNumberstr[COUNT],"02");
			break;
			case 3:strcpy_s(ElevatorNumberstr[COUNT],"03");
			break;
			case 4:strcpy_s(ElevatorNumberstr[COUNT],"04");
			break;
			case 5:strcpy_s(ElevatorNumberstr[COUNT],"05");
			break;
			case 6:strcpy_s(ElevatorNumberstr[COUNT],"06");
			break;
			case 7:strcpy_s(ElevatorNumberstr[COUNT],"07");
			break;
			case 8:strcpy_s(ElevatorNumberstr[COUNT],"08");
			break;
			case 9:strcpy_s(ElevatorNumberstr[COUNT],"09");
			break;
			case 10:strcpy_s(ElevatorNumberstr[COUNT],"10");
			break;
			default:
				strcpy_s(ElevatorNumberstr[COUNT],"error");
		}
	}

}

void GetAllPeopleNumber()
{
	int NUMBER=LXN_Building.GetTotalpeopleNumber();
	int digit;
	int count=3;
	int i=2;
	do
	{
		digit=NUMBER%10;
		ChooseNumber(digit,i--);
		NUMBER/=10;

	}while(--count);
}
void GetFloorPerNum(int floor)
{
	int NUMBER=AllFloorPersonNumber[floor];
	int digit;
	int count=3;
	int i=2;
	do
	{
		digit=NUMBER%10;
		ChooseFNumber(floor,digit,i--);
		NUMBER/=10;

	}while(--count);
}
void ChooseNumber(int digit,int i)
{
	switch(digit)
	{
	case 0: AllPeopleNumber[i]='0';
		break;
	case 1: AllPeopleNumber[i]='1';
		break;
	case 2: AllPeopleNumber[i]='2';
		break;
	case 3: AllPeopleNumber[i]='3';
		break;
	case 4: AllPeopleNumber[i]='4';
		break;
	case 5: AllPeopleNumber[i]='5';
		break;
	case 6: AllPeopleNumber[i]='6';
		break;
	case 7: AllPeopleNumber[i]='7';
		break;
	case 8: AllPeopleNumber[i]='8';
		break;
	case 9: AllPeopleNumber[i]='9';
	default:
		break;
	}
}
void ChooseFNumber(int floor,int digit,int i)
{
	switch(digit)
	{
	case 0: FloorPerNumStr[floor][i]='0';
		break;
	case 1: FloorPerNumStr[floor][i]='1';
		break;
	case 2: FloorPerNumStr[floor][i]='2';
		break;
	case 3: FloorPerNumStr[floor][i]='3';
		break;
	case 4: FloorPerNumStr[floor][i]='4';
		break;
	case 5: FloorPerNumStr[floor][i]='5';
		break;
	case 6: FloorPerNumStr[floor][i]='6';
		break;
	case 7: FloorPerNumStr[floor][i]='7';
		break;
	case 8: FloorPerNumStr[floor][i]='8';
		break;
	case 9: FloorPerNumStr[floor][i]='9';
	default:
		break;
	}
}

void SetTime()
{
	int Second,Minute;
	int Sdigit,Mdigit;
	int count=2;
	int i=1;
	Second=TimeCount%60;
	Minute=TimeCount/60;
	do
	{
		Sdigit=Second%10;
		ChooseTSNumber(Sdigit,i--);
		Second/=10;

	}while(--count);
	 count=2;
	 i=1;
	 do
	{
		Mdigit=Minute%10;
		ChooseTMNumber(Mdigit,i--);
		Minute/=10;

	}while(--count);
}

void ChooseTSNumber(int Sdigit,int i)
{
	switch(Sdigit)
	{
	case 0: TimeSecond[i]='0';
		break;
	case 1: TimeSecond[i]='1';
		break;
	case 2: TimeSecond[i]='2';
		break;
	case 3: TimeSecond[i]='3';
		break;
	case 4: TimeSecond[i]='4';
		break;
	case 5: TimeSecond[i]='5';
		break;
	case 6: TimeSecond[i]='6';
		break;
	case 7: TimeSecond[i]='7';
		break;
	case 8: TimeSecond[i]='8';
		break;
	case 9: TimeSecond[i]='9';
	default:
		break;
	}
}
void ChooseTMNumber(int Mdigit,int i)
{
	switch(Mdigit)
	{
	case 0: TimeMinute[i]='0';
		break;
	case 1: TimeMinute[i]='1';
		break;
	case 2: TimeMinute[i]='2';
		break;
	case 3: TimeMinute[i]='3';
		break;
	case 4: TimeMinute[i]='4';
		break;
	case 5: TimeMinute[i]='5';
		break;
	case 6: TimeMinute[i]='6';
		break;
	case 7: TimeMinute[i]='7';
		break;
	case 8: TimeMinute[i]='8';
		break;
	case 9: TimeMinute[i]='9';
	default:
		break;
	}
}