#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

char ConWaitKey(int KeyNum,...)
{
	if(KeyNum<=0)			//������ͣ
		return getch();
	char *KeyList=(char*)calloc(KeyNum,sizeof(char));	//�����б�
	int i;		//ѭ������
	char ch;	//�����ַ�
	//��������
	va_list valist;
	va_start(valist,KeyNum); 
	for(i=0;i<KeyNum;i++)
		KeyList[i]=va_arg(valist,char);	//�����һ������
	va_end(valist);						//����������

	for(;;)
	{
		ch=getch();				//��ȡ����
		for(i=0;i<KeyNum;i++)	//��ѯ�����б�
			if(ch==KeyList[i])
			{
				free(KeyList);	//�ͷ��ڴ�
				return ch;		//�����û����°�ťASCIIֵ
			}
	}
}