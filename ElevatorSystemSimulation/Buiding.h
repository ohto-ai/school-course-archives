#include"buidingfloors.h"
#include"Elevator.h"
#ifndef ident_Buiding
#define ident_Buiding

class Buiding
{
public:
	Buiding()
	{
		TotalPeopleNumber=0;
	}
  buidingfloors m_floor[11];//�˴���ʼ��ʮ��������󣬵�0��Ԫ�ز���
  Elevator m_Elevator[10];//��ʼ�����Ǹ����ݶ���
  int GetTotalpeopleNumber();
  void ChangeTotalpeopleNumber(int AddPersonNumber);//�ı��¥�е�����
private:
	int TotalPeopleNumber;
	
};
#endif