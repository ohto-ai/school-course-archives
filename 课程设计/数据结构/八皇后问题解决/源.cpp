#define _CRT_SECURE_NO_WARNINGS
#include "../../DataStructureRebuild/DataStructureRebuild/TBString.h"		// ʹ��˳�������ʹ�� string ������Ӧ�滻��
#include "../../DataStructureRebuild/DataStructureRebuild/TBSeqList.h"		// ʹ���ַ���������ʹ�� vector ������Ӧ�滻��
#include <easyx.h>

using namespace std;

constexpr int QueenConstNumber = 8;
int QueenMatrix[QueenConstNumber]{ NULL };					// ���浱ǰ����
thatboy::TBSeqList<thatboy::TBSeqList<int>> Solutions;		// �������нⷨ

void Clear();				// ���
void Solve();				// ���
void SetNext(int);			// ���ñ���
bool JudgePos(int, int);	// ��鱾��
void PrevSet(int, int);		// Ԥ�ȷ���
void ShowBoard(const thatboy::TBSeqList<int>&);		// ��ά��ʽ���һ���ⷨ
void ShowBoardEx(const thatboy::TBSeqList<int>&);	// ��ά��ʽ���һ���ⷨ

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
		InputBox(InStr, MAX_PATH, (thatboy::TBString("�������") + (i + 1) + "���ʺ���к��У�����\"0 0\"��").C_Str(), TEXT("����"), TEXT("0 0"));
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

	if (Solutions.Empty())
	{
		cout << "δ�ҵ��ⷨ";
	}
	else
	{
		cout << "�ҵ�" << Solutions.Size() << "���ⷨ" << endl;
		cout << "��ɨ����ʾ" << endl;
		for (size_t i = 0; i < Solutions.Size(); ++i)
		{
			cout << "[��ɨ��]�ⷨ" << i + 1 << endl;
			for (int j = 0; j < QueenConstNumber; ++j)
			{
				cout << '(' << j << ',' << Solutions[i][j] << ") ";
			}
			cout << endl;
		}
		cout << "��ɨ����ʾ" << endl;
		for (size_t i = 0; i < Solutions.Size(); ++i)
		{
			cout << "[��ɨ��]�ⷨ" << i + 1 << endl;
			for (int j = 0; j < QueenConstNumber; ++j)
			{
				cout << '(' << Solutions[i][j] << ',' << j << ") ";
			}
			cout << endl;
		}
	}
	cout << "����������鿴ͼ����ʾ" << endl;
	std::cin.get();

	if (!Solutions.Empty())
	{
		initgraph(360, 400);
		MOUSEMSG Msg = { NULL };
		settextstyle(30, 0, TEXT("����"));
		BeginBatchDraw();
		for (int SolPtr = 0;;)
		{
			ShowBoard(Solutions[SolPtr]);
			outtextxy(150, 365, (thatboy::TBString("[��]�ⷨ") + (SolPtr + 1)).C_Str());
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
			outtextxy(150, 365, (thatboy::TBString("[��]�ⷨ") + (SolPtr + 1)).C_Str());
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
	if (row >= QueenConstNumber)	// ����������ⷨ
		Solutions.PushBack(thatboy::TBSeqList<int>(QueenMatrix, QueenConstNumber));
	else if (row < 0)
		return;
	else if (QueenMatrix[row] != -1) // �����ѷ��ûʺ�
	{
		int col = QueenMatrix[row];
		QueenMatrix[row] = -1;
		if (JudgePos(row, col))
		{
			SetNext(row + 1);	// ������һ��
		}	
	}
	else
	{
		for (int col = 0; col < QueenConstNumber; ++col)	// ����ÿһ��
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
	/* ���row col�Ƿ�ɷ��� */
	/* 
	 ���ڲ���һά���飬ͬһ�У�������
	 ͬһ�У�q[i]=col
	 б�� q[i]-1=col-row����q[i]=col+row
	*/
	for (int i = 0; i < QueenConstNumber; ++i)
		if (i != row && QueenMatrix[i] != -1 && (QueenMatrix[i] == col || QueenMatrix[i] - i == col - row || QueenMatrix[i] + i == col + row))
			return false;
	return true;
}

void PrevSet(int row, int col)
{
	if (row < 0 || row >= QueenConstNumber || col < 0 || col >= QueenConstNumber)
		throw "�±�Խ�����";
	if (QueenMatrix[row] != -1)
		throw "ͬ���ظ�����";
	if (JudgePos(row, col))
		QueenMatrix[row] = col;
	else
		throw "ͬ���ظ�����";
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