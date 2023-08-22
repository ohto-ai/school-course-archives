double CalculateFine		(BorNodeLink Bor)
{
	if(Bor==NULL)
		return 0.0;
	int Days;//ÓâÆÚÌìÊı
	Days=((Bor->RDate!=0?Bor->RDate:time(NULL))-Bor->BDate)/_SecondPerDay-_Borrow_Days_Limit;
	Bor->Fine=Days>0?Days*0.1:0.0;
	return Bor->Fine;
}
int CountStudent()
{
	int Count=0;
	StuNodeLink Stu;
	for(Stu=StuListHead.Next;Stu!=NULL;Stu=Stu->Next)
		++Count;
	return Count; 
}
int CountBook()
{
	int Count=0;
	BokNodeLink Bok;
	for(Bok=BokListHead.Next;Bok!=NULL;Bok=Bok->Next)
		++Count;
	return Count;
}
int CountBorrow()
{
	int Count=0;
	BorNodeLink Bor;
	for(Bor=BorListHead.Next;Bor!=NULL;Bor=Bor->Next)
		++Count;
	return Count;
}
