#ifndef defi_Time
#define defi_Time
void TimeStateChange(void);
void InitGraph(void);
extern int TimeButton[10][11];
extern int AllStopTime[10];
extern int AllCurrentfloor[10];
extern int AllElevatorPersonNumber[10];
extern int AllFloorPersonNumber[11];
extern int AllElevatorState[10];
extern int AllFloorElevatorNumber[11];
#endif