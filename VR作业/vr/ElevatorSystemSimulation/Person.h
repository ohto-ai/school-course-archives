#ifndef identi_Person
#define identi_Person
#define InWork 5
#define OutWork 6
class Person
{
public:
	int m_InBuiding;//0��ʾ���ڴ�¥�У�1��ʾ�ڴ�¥��
	int m_PatientTime;
	int m_WorkTime;
	Person()
	{
		InitPatientTime();//��ʼ���������ʱ��
		m_PositionFloor=1;//ÿ���˶���ʼ��Ϊ�ڵ�һ�㿪ʼ�����¥
		m_InBuiding=0;//��ʾ���ڴ�¥��
		m_WorkState=OutWork;//һ��ʼÿ���˶�û���ڹ���
		InitAimFloor();
	}
	int GetState();//��ȡ����״̬��5��ʾ������6��ʾ�ȴ�����
	void SetInWorkState();//���ù���״̬����״̬����Ϊ����״̬
	void SetOutWorkState();//����Ϊ�ǹ���״̬
	void SetInBuiding();//������m_InBuiding��Ϊ1����ʾ�ڴ�¥��
    int GetAimfloor();//��ȡĿ���,���ڲ�������
	void SetCurrentfloor();//ֻҪһ�����ϵ��ݻ��߳���������ʱ�䣬��ֱ�ӽ�m_PositionFloor=m_Aimfloor
	void InitCurrentfloor();//��ʼ��¥�㣬�����ڵ�һ�㣬�������ڵ�һ��
	int GetCurrentfloor();//������ڲ���
	void InitWorkTime();//��ʼ������ʱ��
	void InitAimFloor();//��ʼ��Ŀ��㣬ע��Ŀ��㲻��Ϊ���ڲ�
	int GetPatientTime();
	void InitPatientTime();
private:
	int m_Aimfloor;
	int m_WorkState;//��Inwork��outwork��ʾ
	int m_PositionFloor;//���ڲ���
};
#endif