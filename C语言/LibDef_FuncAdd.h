
//添加学生
StuNodeLink AddStudent(char*StuNum,		//学号
				   char*StuName,		//姓名
				   char*Department	//系部
				   )
{
	//申请内存
	if(NULL==(pStuListTail->Next=(StuNodeLink )calloc(1,sizeof(StuNode))))
		return NULL; 
	
	pStuListTail->Next->Last=pStuListTail;	//设置新节点的前驱
	pStuListTail=pStuListTail->Next;		//变更尾指针
	pStuListTail->Last->Next=pStuListTail;	//设置旧节点的后继
	
	//写入数据
	strcpy(pStuListTail->StuNum,StuNum);	
	strcpy(pStuListTail->StuName,StuName);
	strcpy(pStuListTail->Department,Department);
	return pStuListTail;
}
//添加书籍
BokNodeLink AddBook(char*BokNum,			//编号
				char*BokName,		//书名
				char*PublishHouse,	//出版社
				double Price			//单价
				)
{
	//申请内存
	if(NULL==(pBokListTail->Next=(BokNodeLink )calloc(1,sizeof(BokNode))))
		return NULL;
	
	pBokListTail->Next->Last=pBokListTail;	//设置新节点的前驱
	pBokListTail=pBokListTail->Next;		//变更尾指针
	pBokListTail->Last->Next=pBokListTail;	//设置旧节点的后继
	
	//写入数据
	strcpy(pBokListTail->BookNum,BokNum);
	strcpy(pBokListTail->BookName,BokName);
	strcpy(pBokListTail->PublishHouse,PublishHouse);
	pBokListTail->HasBorrow=false;
	pBokListTail->Price=Price;
	return pBokListTail;
}
//借书
int LogBor(StuNodeLink Stu,		//学生
		   BokNodeLink Bok		//图书
		   )
{
	if(Stu==NULL||Bok==NULL)
		return -1;
	if(Bok->HasBorrow)//已经被借阅
		return -2;
	//添加新的借阅记录
	//申请内存
	if(NULL==(pBorListTail->Next=(BorNodeLink )calloc(1,sizeof(BorNode))))
		return -3;
	
	
	pBorListTail->Next->Last=pBorListTail;	//设置新节点的前驱
	pBorListTail=pBorListTail->Next;		//变更尾指针
	pBorListTail->Last->Next=pBorListTail;	//设置旧节点的后继
	
	//记录时间
	pBorListTail->BDate=time(NULL);	//获得日历时间
	pBorListTail->RDate=0;			//标记尚未归还
	//记录书籍及学号
	strcpy(pBorListTail->StuNum,Stu->StuNum);
	strcpy(pBorListTail->BookNum,Bok->BookNum);
	//设置罚款为0
	pBorListTail->Fine=0;
	
	Bok->HasBorrow=true;			//标记已经被借阅
	
	return 0;
}
int LogRet(BorNodeLink Bor		//借阅记录
		   )
{
	if(Bor==NULL)
		return -1;
	//记录时间
	Bor->RDate=time(NULL);	//获得日历时间
	
	BokNodeLink Tmp=FindFirstBook(Bor->BookNum,NULL,NULL);
	if(Tmp)
		Tmp->HasBorrow=false;//标记已经还书
	
	return 0;
}
