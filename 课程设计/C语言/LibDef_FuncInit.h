void InitStudent(int N)
{
	char NAME[3][512]={
	"��Ǯ��������֣��������������������������ʩ�ſײ��ϻ���κ�ս�\
��л������ˮ��������˸��ɷ�����³Τ������ﻨ������Ԭ��ۺ��ʷ��\
�����Ѧ�׺����������ޱϺ�����������ʱ��Ƥ���뿵����Ԫ������ƽ��\
����Ҧ��տ����ë����ױ�����̸��é���ܼ�������ף����",

		"����갼Ʒ���ϣ��ϧ������ŨϦ���尲������������������Ƚ��ݯ��Ȼľ�����������������\
�껶誸국�滶���ݺ����󻶰�����ʩ����ܰ����ϧ���������ų���Ⱥ��ʯ�����������������İĭ�������",

		"����ϣ��������ܰ������Ũ���Ȼ��س�������������ݯ���ʯ���뿨��Ϧ������¬��ľ����\
������������糸������ȺȾȻ�����������짽��������Ƚ��糸�ʩ����İĭ�����Ⱦ����¬\
                                                      "
	};
	char Name[20];

	char Num[20];
	 
	int Len[3]=
	{
		strlen(NAME[0]),
		strlen(NAME[1]),
		strlen(NAME[2])
	};

	int i;
	int rPos[3];
	for(i=0;i<N;++i)
	{
		rPos[0]=rand()%(Len[0]/2);
		rPos[1]=rand()%(Len[1]/2);
		rPos[2]=rand()%(Len[2]/2);
		sprintf(Num,"2021706%02d",i+1);
		sprintf(Name,"%c%c%c%c%c%c",NAME[0][rPos[0]*2],NAME[0][rPos[0]*2+1],
			NAME[1][rPos[1]*2],NAME[1][rPos[1]*2+1],
			NAME[2][rPos[2]*2],NAME[2][rPos[2]*2+1]);
		AddStudent(Num,Name,"���������ѧԺ");
	}
}
void InitBook(int N)
{
	int i;
	char Num[20];
	char Name[20];
	for(i=0;i<N;++i)
	{
		sprintf(Num,"00%02d",i+1);
		sprintf(Name,"Ԥ���鼮%s",Num);
		AddBook(Num,Name,"���������ѧԺ������",(double)(40.0+rand()%30+(rand()%100)/100.0 ));
	}
}
void InitBorrow(int N)
{
	int i;
	for(i=0;i<N;++i)
	{
		LogBor(FindStudent(0,0,0),FindBook(0,0,0));
	}
}