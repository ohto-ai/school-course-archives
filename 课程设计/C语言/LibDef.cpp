 
#include "LibDef.h"


static StuNode StuListHead;						//学生链表头结点
static StuNodeLink pStuListTail=&StuListHead;	//学生链表尾指针

static BokNode BokListHead;						//图书链表头结点
static BokNodeLink pBokListTail=&BokListHead;	//图书链表尾指针

static BorNode BorListHead;						//借阅链表头结点
static BorNodeLink pBorListTail=&BorListHead;	//借阅链表尾指针

///////////////////////////////////////////////////          初始化
#include "LibDef_FuncInit.h"

///////////////////////////////////////////////////          添加
#include "LibDef_FuncAdd.h"

///////////////////////////////////////////////////          查找
#include "LibDef_FuncFind.h"

///////////////////////////////////////////////////          删除
#include "LibDef_FuncRemove.h"

///////////////////////////////////////////////////          修改
#include "LibDef_FuncModify.h"

///////////////////////////////////////////////////          计算
#include "LibDef_FuncCalculate.h"

///////////////////////////////////////////////////          显示
#include "LibDef_FuncShow.h"

///////////////////////////////////////////////////          保存
#include "LibDef_FuncData.h"

#undef _Borrow_Days_Limit
#undef _SecondPerDay


