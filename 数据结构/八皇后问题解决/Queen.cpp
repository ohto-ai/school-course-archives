#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>		
#include <iostream>
#include <easyx.h>

using namespace std;

constexpr int QueenNumber = 8;
int QueenMatrix[QueenNumber]{ NULL };					// 保存当前进度
vector<vector<int>> Solutions;		// 保存所有解法

void Clear();				// 清除
void Solve();				// 求解
void SetNext(int);			// 放置本行
bool JudgePos(int, int);	// 检查本行
void PrevSet(int, int);		// 预先放置
void ShowBoard(const vector<int>&);		// 二维形式输出一个解法
void ShowBoardEx(const vector<int>&);	// 二维形式输出一个解法

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
		InputBox(InStr, MAX_PATH, (string("请输入第") + to_string(i + 1) + "个皇后的行和列，形如\"0 0\"。").c_str(), TEXT("坐标"), TEXT("0 0"));
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

	if (Solutions.empty())
	{
		cout << "未找到解法" << endl;
	}
	else
	{
		cout << "找到" << Solutions.size() << "个解法" << endl;
		cout << "行扫描显示" << endl;
		for (size_t i = 0; i < Solutions.size(); ++i)
		{
			cout << "[行扫描]解法" << i + 1 << endl;
			for (int j = 0; j < QueenNumber; ++j)
			{
				cout << '(' << j << ',' << Solutions[i][j] << ") ";
			}
			cout << endl;
		}
		cout << "列扫描显示" << endl;
		for (size_t i = 0; i < Solutions.size(); ++i)
		{
			cout << "[列扫描]解法" << i + 1 << endl;
			for (int j = 0; j < QueenNumber; ++j)
			{
				cout << '(' << Solutions[i][j] << ',' << j << ") ";
			}
			cout << endl;
		}
		cout << "按下任意键查看图像显示" << endl;
		cin.get();

		initgraph(360, 400);
		MOUSEMSG Msg = { NULL };
		settextstyle(30, 0, TEXT("楷体"));
		BeginBatchDraw();
		for (int SolPtr = 0;;)
		{
			ShowBoard(Solutions[SolPtr]);
			outtextxy(150, 365, (string("[行]解法") + to_string(SolPtr + 1)).c_str());
			FlushBatchDraw();
			Msg = GetMouseMsg();
			SolPtr = (SolPtr + Solutions.size() - Msg.wheel / 120) % Solutions.size();
			if (Msg.uMsg == WM_LBUTTONDBLCLK)
				break;

		}

		for (int SolPtr = 0;;)
		{
			ShowBoardEx(Solutions[SolPtr]);
			outtextxy(150, 365, (string("[列]解法") + to_string(SolPtr + 1)).c_str());
			FlushBatchDraw();
			Msg = GetMouseMsg();
			SolPtr = (SolPtr + Solutions.size() - Msg.wheel / 120) % Solutions.size();
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
	Solutions.clear();
	for (auto& it : QueenMatrix)
		it = -1;
}

void Solve()
{
	SetNext(0);
}

void SetNext(int row)
{
	if (row >= QueenNumber)	// 结束，保存解法
		Solutions.push_back(vector<int>(QueenMatrix, QueenMatrix + QueenNumber));
	else if (row < 0)
		return;
	else if (QueenMatrix[row] != -1) // 此行已放置皇后
	{
		if (JudgePos(row, QueenMatrix[row]))
		{
			SetNext(row + 1);	// 设置下一层
		}	
	}
	else
	{
		for (int col = 0; col < QueenNumber; ++col)	// 遍历每一列
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
	for (int i = 0; i < QueenNumber; ++i)
		if (i != row && QueenMatrix[i] != -1 && (QueenMatrix[i] == col || QueenMatrix[i] - i == col - row || QueenMatrix[i] + i == col + row))
			return false;
	return true;
}

void PrevSet(int row, int col)
{
	if (row < 0 || row >= QueenNumber || col < 0 || col >= QueenNumber)
		throw "下标越界错误";
	if (QueenMatrix[row] != -1)
		throw "同行重复错误";
	if (JudgePos(row, col))
		QueenMatrix[row] = col;
	else
		throw "同列重复错误";
}

void ShowBoard(const vector<int>&sol)
{
	cleardevice();
	for (size_t row = 0; row < QueenNumber; row++)
	{
		for (size_t col = 0; col < QueenNumber; ++col)
		{
			rectangle(col * 40 + 20, row * 40 + 20, col * 40 + 60, row * 40 + 60);
		}
	}
	for (size_t row = 0; row < QueenNumber; row++)
	{
		solidcircle(sol[row] * 40 + 40, row * 40 + 40, 20);
	}
}
void ShowBoardEx(const vector<int>& sol)
{
	cleardevice();
	for (size_t col = 0; col < QueenNumber; col++)
	{
		for (size_t row = 0; row < QueenNumber; ++row)
		{
			rectangle(col * 40 + 20, row * 40 + 20, col * 40 + 60, row * 40 + 60);
		}
	}
	for (size_t col = 0; col < QueenNumber; col++)
	{
		solidcircle(col * 40 + 40, sol[col] * 40 + 40, 20);
	}
}