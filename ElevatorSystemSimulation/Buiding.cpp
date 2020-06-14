#include<iostream>
#include <stdlib.h>
#include"Buiding.h"
using namespace std;
void Buiding::ChangeTotalpeopleNumber(int AddPersonNumber)
{
	TotalPeopleNumber+=AddPersonNumber;
}
int Buiding::GetTotalpeopleNumber()
{
	return TotalPeopleNumber;
}



