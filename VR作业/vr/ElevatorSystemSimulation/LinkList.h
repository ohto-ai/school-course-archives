#ifndef ident_Link
#define ident_Link
typedef struct LNode
{
    int data;//��ʾ���
    struct LNode *next;
}LNode, *LinkList;

void CreateList(LinkList &L);
void AddData(LinkList &L,int data);

void DeleteData(LinkList &L,int data);

void DestroyData(LinkList &L);
#endif