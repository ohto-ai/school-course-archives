#include<iostream>
#include"LinkList.h"
void CreateList(LinkList &L)
{
	L=new LNode;
	L->next=NULL;
}
void AddData(LinkList &L,int data)
{//²ÉÓÃÎ²²å·¨
	LinkList p,r;
	p=new LNode;
	p->data=data;
	for(r=L;r->next!=NULL;r=r->next);
	p->next=r->next;
	r->next=p;
}

void DeleteData(LinkList &L,int data)
{
	LinkList p,q;
	
	for(p=L;p->next->data!=data;p=p->next);
	q=p->next;
	p->next=p->next->next;
	delete q;
	
}

void DestroyData(LinkList &L)
{
	if(L->next!=NULL)
	{
	LinkList p,q;
	p=L->next;
	L->next=NULL;
	for(q=p->next;q!=NULL;)
	{
		delete p;
		p=q;
		q=q->next;
	}
	delete p;
	}
}