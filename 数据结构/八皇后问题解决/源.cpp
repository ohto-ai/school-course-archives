#define _CRT_SECURE_NO_WARNINGS
#include "../../DataStructureRebuild/DataStructureRebuild/TBString.h"		// 使用顺序表（可以使用 string 类作相应替换）
#include "../../DataStructureRebuild/DataStructureRebuild/TBSeqList.h"		// 使用字符串（可以使用 vector 类作相应替换）
#include <easyx.h>

using namespace std;

constexpr int QueenConstNumber = 8;
int QueenMatrix[QueenConstNumber]{ NULL };					// 保存当前进度
thatboy::TBSeqList<thatboy::TBSeqList<int>> Solutions;		// 保存所有解法

void Clear();				// 清除
void Solve();				// 求解
void SetNext(int);			// 放置本行
bool JudgePos(int, int);	// 检查本行
void PrevSet(int, int);		// 预先放置
void ShowBoard(const thatboy::TBSeqList<int>&);		// 二维形式输出一个解法
void ShowBoardEx(const thatboy::TBSeqList<int>&);	// 二维形式输出一个解法

int main()
{
	int PreNumber = 0;	// 预置点个数
	int row, col;			// 预置点坐标
	Clear();
	TCHAR InStr[MAX_PATH] = { NULL };
	InputBox(InStr, MAX_PATH, TEXT("请输入预置皇后个数(0-8)"), TEXT("预置皇后"), TEXT("0"));
	sscanf(InStr, "%d", &PreNumber);
	for (int i = 0; i < PreNumber; i++)
	{
		InputBox(InStr, MAX_PATH, (thatboy::TBString("请输入第") + (i + 1) + "个皇后的行和列，形如\"0 0\"。").C_Str(), TEXT("坐标"), TEXT("0 0"));
		sscanf(InStr, "%d %d", &row, &col);
		try
		{
			PrevSet(row, col);
		}
		catch (const char* err_str)
		{
			MessageBox(NULL, err_str, TEXT("放置错误没有添加"), MB_ICONERROR);
		}
	}

	Solve();				// 求解

	if (Solutions.Empty())
	{
		cout << "未找到解法";
	}
	else
	{
		cout << "找到" << Solutions.Size() << "个解法" << endl;
		cout << "行扫描显示" << endl;
		for (size_t i = 0; i < Solutions.Size(); ++i)
		{
			cout << "[行扫描]解法" << i + 1 << endl;
			for (int j = 0; j < QueenConstNumber; ++j)
			{
				cout << '(' << j << ',' << Solutions[i][j] << ") ";
			}
			cout << endl;
		}
		cout << "列扫描显示" << endl;
		for (size_t i = 0; i < Solutions.Size(); ++i)
		{
			cout << "[列扫描]解法" << i + 1 << endl;
			for (int j = 0; j < QueenConstNumber; ++j)
			{
				cout << '(' << Solutions[i][j] << ',' << j << ") ";
			}
			cout << endl;
		}
	}
	cout << "按下任意键查看图像显示" << endl;
	std::cin.get();

	if (!Solutions.Empty())
	{
		initgraph(360, 400);
		MOUSEMSG Msg = { NULL };
		settextstyle(30, 0, TEXT("楷体"));
		BeginBatchDraw();
		for (int SolPtr = 0;;)
		{
			ShowBoard(Solutions[SolPtr]);
			outtextxy(150, 365, (thatboy::TBString("[行]解法") + (SolPtr + 1)).C_Str());
			FlushBatchDraw();
			Msg = GetMouseMsg();
			SolPtr = (SolPtr + Solutions.Size() - Msg.wheel / 120) % Solutions.Size();
			if (Msg.uMsg == WM_LBUTTONDBLCLK)
				break;

		}
		EndBatchDraw();

		BeginBatchDraw();
		for (int SolPtr = 0;;)
		{
			ShowBoardEx(Solutions[SolPtr]);
			outtextxy(150, 365, (thatboy::TBString("[列]解法") + (SolPtr + 1)).C_Str());
			FlushBatchDraw();
			Msg = GetMouseMsg();
			SolPtr = (SolPtr + Solutions.Size() - Msg.wheel / 120) % Solutions.Size();
			if (Msg.uMsg == WM_LBUTTONDBLCLK)
				break;

		}
		EndBatchDraw();
		closegraph();
		std::cin.get();
	}
	return 0;
}

void Clear()
{
	Solutions.Clear();
	for (auto& it : QueenMatrix)
		it = -1;
}

void Solve()
{
	for (int FirstEmptyRow = 0; FirstEmptyRow < QueenConstNumber; ++FirstEmptyRow)
	{
		if (QueenMatrix[FirstEmptyRow] == -1)
		{
			SetNext(FirstEmptyRow);
			return;
		}
	}
}

void SetNext(int row)
{
	if (row >= QueenConstNumber)	// 结束，保存解法
		Solutions.PushBack(thatboy::TBSeqList<int>(QueenMatrix, QueenConstNumber));
	else if (row < 0)
		return;
	else if (QueenMatrix[row] != -1) // 此行已放置皇后
	{
		int col = QueenMatrix[row];
		QueenMatrix[row] = -1;
		if (JudgePos(row, col))
		{
			SetNext(row + 1);	// 设置下一层
		}	
	}
	else
	{
		for (int col = 0; col < QueenConstNumber; ++col)	// 遍历每一列
		{
			if (JudgePos(row, col))
			{
				QueenMatrix[row] = col;	// 设置这一层
				SetNext(row + 1);
				QueenMatrix[row] = -1;	// 恢复这一层
			}
		}
	}
}

bool JudgePos(int row, int col)
{
	/* 检查row col是否可放置 */
	/* 
	 由于采用一维数组，同一行，无须检查
	 同一列，q[i]=col
	 斜着 q[i]-1=col-row或者q[i]=col+row
	*/
	for (int i = 0; i < QueenConstNumber; ++i)
		if (i != row && QueenMatrix[i] != -1 && (QueenMatrix[i] == col || QueenMatrix[i] - i == col - row || QueenMatrix[i] + i == col + row))
			return false;
	return true;
}

void PrevSet(int row, int col)
{
	if (row < 0 || row >= QueenConstNumber || col < 0 || col >= QueenConstNumber)
		throw "下标越界错误";
	if (QueenMatrix[row] != -1)
		throw "同行重复错误";
	if (JudgePos(row, col))
		QueenMatrix[row] = col;
	else
		throw "同列重复错误";
}

void ShowBoard(const thatboy::TBSeqList<int>&sol)
{
	cleardevice();
	for (size_t row = 0; row < QueenConstNumber; row++)
	{
		for (size_t col = 0; col < QueenConstNumber; ++col)
		{
			rectangle(col * 40 + 20, row * 40 + 20, col * 40 + 60, row * 40 + 60);
		}
	}
	for (size_t row = 0; row < QueenConstNumber; row++)
	{
		solidcircle(sol[row] * 40 + 40, row * 40 + 40, 20);
	}
}
void ShowBoardEx(const thatboy::TBSeqList<int>& sol)
{
	cleardevice();
	for (size_t col = 0; col < QueenConstNumber; col++)
	{
		for (size_t row = 0; row < QueenConstNumber; ++row)
		{
			rectangle(col * 40 + 20, row * 40 + 20, col * 40 + 60, row * 40 + 60);
		}
	}
	for (size_t col = 0; col < QueenConstNumber; col++)
	{
		solidcircle(col * 40 + 40, sol[col] * 40 + 40, 20);
	}
}