#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

char ConWaitKey(int KeyNum,...)
{
	if(KeyNum<=0)			//函数暂停
		return getch();
	char *KeyList=(char*)calloc(KeyNum,sizeof(char));	//按键列表
	int i;		//循环变量
	char ch;	//输入字符
	//不定参数
	va_list valist;
	va_start(valist,KeyNum); 
	for(i=0;i<KeyNum;i++)
		KeyList[i]=va_arg(valist,char);	//获得下一个参数
	va_end(valist);						//结束不定参

	for(;;)
	{
		ch=getch();				//获取按键
		for(i=0;i<KeyNum;i++)	//查询按键列表
			if(ch==KeyList[i])
			{
				free(KeyList);	//释放内存
				return ch;		//返回用户按下按钮ASCII值
			}
	}
}