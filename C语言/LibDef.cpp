 
#include "LibDef.h"


static StuNode StuListHead;						//ѧ������ͷ���
static StuNodeLink pStuListTail=&StuListHead;	//ѧ������βָ��

static BokNode BokListHead;						//ͼ������ͷ���
static BokNodeLink pBokListTail=&BokListHead;	//ͼ������βָ��

static BorNode BorListHead;						//��������ͷ���
static BorNodeLink pBorListTail=&BorListHead;	//��������βָ��

///////////////////////////////////////////////////          ��ʼ��
#include "LibDef_FuncInit.h"

///////////////////////////////////////////////////          ���
#include "LibDef_FuncAdd.h"

///////////////////////////////////////////////////          ����
#include "LibDef_FuncFind.h"

///////////////////////////////////////////////////          ɾ��
#include "LibDef_FuncRemove.h"

///////////////////////////////////////////////////          �޸�
#include "LibDef_FuncModify.h"

///////////////////////////////////////////////////          ����
#include "LibDef_FuncCalculate.h"

///////////////////////////////////////////////////          ��ʾ
#include "LibDef_FuncShow.h"

///////////////////////////////////////////////////          ����
#include "LibDef_FuncData.h"

#undef _Borrow_Days_Limit
#undef _SecondPerDay


