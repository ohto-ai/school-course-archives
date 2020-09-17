
StuNodeLink ModifyStudent	(StuNodeLink Stu,char*StuNum,char*StuName,char*Department)
{
	if(Stu==NULL)
		return NULL;
	if(StuNum!=NULL&&StuNum[0]!=0)
		strcpy(Stu->StuNum,StuNum);
	if(StuName!=NULL&&StuName[0]!=0)
		strcpy(Stu->StuName,StuName);
	if(Department!=NULL&&Department[0]!=0)
		strcpy(Stu->Department,Department);
	return Stu;
}
BokNodeLink ModifyBook		(BokNodeLink Bok,char*BokNum,char*BokName,char*PublishHouse,double Price,int HasBorrow)
{
	if(Bok==NULL)
		return NULL;
	if(BokNum!=NULL&&BokNum[0]!=0)
		strcpy(Bok->BookNum,BokNum);
	if(BokName!=NULL&&BokName[0]!=0) 
		strcpy(Bok->BookName,BokName);
	if(PublishHouse!=NULL&&PublishHouse[0]!=0)
		strcpy(Bok->PublishHouse,PublishHouse);
	if(Price>=0.0)
		Bok->Price=Price;
	if(HasBorrow>=0)
		Bok->HasBorrow=(HasBorrow>0);
	return Bok;
}
BorNodeLink ModifyBorrow	(BorNodeLink Bor,char*StuNum,char*BookNum,time_t BDate,time_t RDate,double Fine)
{
	if(Bor==NULL)
		return NULL;
	if(StuNum!=NULL&&StuNum[0]!=0)
		strcpy(Bor->StuNum,StuNum);
	if(BookNum!=NULL&&BookNum[0]!=0)
		strcpy(Bor->BookNum,BookNum);
	if(BDate>=0)
		Bor->BDate=BDate;
	if(RDate>=0)
		Bor->RDate=RDate;
	if(Fine>=0.0)
		Bor->Fine=Fine;
	return Bor;
}
