#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>		
#include <iostream>
#include <easyx.h>

using namespace std;

constexpr int QueenNumber = 8;
int QueenMatrix[QueenNumber]{ NULL };					// ���浱ǰ����
vector<vector<int>> Solutions;		// �������нⷨ

void Clear();				// ���
void Solve();				// ���
void SetNext(int);			// ���ñ���
bool JudgePos(int, int);	// ��鱾��
void PrevSet(int, int);		// Ԥ�ȷ���
void ShowBoard(const vector<int>&);		// ��ά��ʽ���һ���ⷨ
void ShowBoardEx(const vector<int>&);	// ��ά��ʽ���һ���ⷨ

int main()
{
	int PreNumber = 0;	// Ԥ�õ����
	int row, col;			// Ԥ�õ�����
	Clear();
	TCHAR InStr[MAX_PATH] = { NULL };
	InputBox(InStr, MAX_PATH, TEXT("������Ԥ�ûʺ����(0-8)"), TEXT("Ԥ�ûʺ�"), TEXT("0"));
	sscanf(InStr, "%d", &PreNumber);
	for (int i = 0; i < PreNumber; i++)
	{
		InputBox(InStr, MAX_PATH, (string("�������") + to_string(i + 1) + "���ʺ���к��У�����\"0 0\"��").c_str(), TEXT("����"), TEXT("0 0"));
		sscanf(InStr, "%d %d", &row, &col);
		try
		{
			PrevSet(row, col);
		}
		catch (const char* err_str)
		{
			MessageBox(NULL, err_str, TEXT("���ô���û�����"), MB_ICONERROR);
		}
	}

	Solve();				// ���

	if (Solutions.empty())
	{
		cout << "δ�ҵ��ⷨ" << endl;
	}
	else
	{
		cout << "�ҵ�" << Solutions.size() << "���ⷨ" << endl;
		cout << "��ɨ����ʾ" << endl;
		for (size_t i = 0; i < Solutions.size(); ++i)
		{
			cout << "[��ɨ��]�ⷨ" << i + 1 << endl;
			for (int j = 0; j < QueenNumber; ++j)
			{
				cout << '(' << j << ',' << Solutions[i][j] << ") ";
			}
			cout << endl;
		}
		cout << "��ɨ����ʾ" << endl;
		for (size_t i = 0; i < Solutions.size(); ++i)
		{
			cout << "[��ɨ��]�ⷨ" << i + 1 << endl;
			for (int j = 0; j < QueenNumber; ++j)
			{
				cout << '(' << Solutions[i][j] << ',' << j << ") ";
			}
			cout << endl;
		}
		cout << "����������鿴ͼ����ʾ" << endl;
		cin.get();

		initgraph(360, 400);
		MOUSEMSG Msg = { NULL };
		settextstyle(30, 0, TEXT("����"));
		BeginBatchDraw();
		for (int SolPtr = 0;;)
		{
			ShowBoard(Solutions[SolPtr]);
			outtextxy(150, 365, (string("[��]�ⷨ") + to_string(SolPtr + 1)).c_str());
			FlushBatchDraw();
			Msg = GetMouseMsg();
			SolPtr = (SolPtr + Solutions.size() - Msg.wheel / 120) % Solutions.size();
			if (Msg.uMsg == WM_LBUTTONDBLCLK)
				break;

		}

		for (int SolPtr = 0;;)
		{
			ShowBoardEx(Solutions[SolPtr]);
			outtextxy(150, 365, (string("[��]�ⷨ") + to_string(SolPtr + 1)).c_str());
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
	if (row >= QueenNumber)	// ����������ⷨ
		Solutions.push_back(vector<int>(QueenMatrix, QueenMatrix + QueenNumber));
	else if (row < 0)
		return;
	else if (QueenMatrix[row] != -1) // �����ѷ��ûʺ�
	{
		if (JudgePos(row, QueenMatrix[row]))
		{
			SetNext(row + 1);	// ������һ��
		}	
	}
	else
	{
		for (int col = 0; col < QueenNumber; ++col)	// ����ÿһ��
		{
			if (JudgePos(row, col))
			{
				QueenMatrix[row] = col;	// ������һ��
				SetNext(row + 1);
				QueenMatrix[row] = -1;	// �ָ���һ��
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
		throw "�±�Խ�����";
	if (QueenMatrix[row] != -1)
		throw "ͬ���ظ�����";
	if (JudgePos(row, col))
		QueenMatrix[row] = col;
	else
		throw "ͬ���ظ�����";
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