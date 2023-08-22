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
  buidingfloors m_floor[11];//此处初始化十个层类对象，第0号元素不用
  Elevator m_Elevator[10];//初始化好是个电梯对象
  int GetTotalpeopleNumber();
  void ChangeTotalpeopleNumber(int AddPersonNumber);//改变大楼中的人数
private:
	int TotalPeopleNumber;
	
};
#endif