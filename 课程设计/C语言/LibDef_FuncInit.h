void InitStudent(int N)
{
	char NAME[3][512]={
	"赵钱孙李周吴郑王冯陈褚卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜\
戚谢邹喻柏水窦章云苏潘葛奚范彭郎鲁韦昌马苗凤花方俞任袁柳酆鲍史唐\
费廉岑薛雷贺倪汤滕殷罗毕郝邬安常乐于时傅皮卞齐康伍余元卜顾孟平黄\
和尹姚邵湛汪祁毛禹狄米贝明戴谈宋茅庞熊纪舒屈项祝董梁",

		"穆萧臧计伏成希熙惜欢广斐瑾浓夕曦清安柳欢扬素尤曦苒昀悠冉囿莜筱然木沐宥祖筱宛段研需段研\
戈欢瑾戈淡祖欢含休含休梵欢安柔黎施虞辛馨沁念惜土许黛游优尘步群广石记柔幽馥黛游优悠尤陌沫宛界拉林",

		"西兮希西欢兮辛馨沁扬黎浓漫兹欢素尘欢漫穗熙卡兹莜宥幽石沐穗卡米夕霓米密卢锋木欢霓\
淡娴柳昀密昔斐绯格歆土许步群染然楚翳馥囿昔需歆界拉念梵娴冉记绯格施虞林陌沫清楚翳染广苒卢\
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
		AddStudent(Num,Name,"计算机工程学院");
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
		sprintf(Name,"预存书籍%s",Num);
		AddBook(Num,Name,"计算机工程学院出版社",(double)(40.0+rand()%30+(rand()%100)/100.0 ));
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