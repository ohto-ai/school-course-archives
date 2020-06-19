
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include "StudentInfoWiget.h"


StudentInfo students[]{
	{
		  "��һ"
		, "202200601"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ202"
		, "Ů"
		, "liu1@gmail.com"
		, "�����Ͼ�"
		, "15912152872"
		, "www.liu1.com"
		, "2002-2-3"
		, "��"
		, "������Ա"
		, "221122"
		, "2020-9-1"
		, ""
		, ""
	}
	, {
		"�¶�"
		, "202190603"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ192"
		, "Ů"
		, "zhagn3@gmail.com"
		, "�����Ͼ�"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "��"
		, "������Ա"
		, "221122"
		, "2019-9-1"
		, "��������̫̫����·"
		, "2019��У������ѧ��"
	}
	, {
		"����"
		, "202200603"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ202"
		, "Ů"
		, "zhagn3@gmail.com"
		, "�����Ͼ�"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-10-3"
		, "��"
		, "Ⱥ��"
		, "221122"
		, "2020-9-1"
		, "��������̫̫����·"
		, "2020��У������ѧ��"
		, "girl.png"
	}
	, {
		"����"
		, "202200604"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ202"
		, "��"
		, "li4@gmail.com"
		, "��������"
		, "15151511223"
		, "www.li4happy.com"
		, "2002-1-12"
		, "��"
		, "������Ա"
		, "231117"
		, "2020-9-1"
		, "��"
		, "2020���θ��������һ��"
		, "boy.png"
	}
	, {
		"����"
		, "202190603"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ192"
		, "Ů"
		, "zhagn3@gmail.com"
		, "�����Ͼ�"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "��"
		, "������Ա"
		, "221122"
		, "2019-9-1"
		, "��������̫̫����·"
		, "2019��У������ѧ��"
	}
	, {
		"����"
		, "202190603"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ192"
		, "Ů"
		, "zhagn3@gmail.com"
		, "�����Ͼ�"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "��"
		, "������Ա"
		, "221122"
		, "2019-9-1"
		, "��������̫̫����·"
		, "2019��У������ѧ��"
	}
	, {
		"����"
		, "202190603"
		, "���������ѧԺ"
		, "����ý�弼��"
		, "��Ƕ192"
		, "Ů"
		, "zhagn3@gmail.com"
		, "�����Ͼ�"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "��"
		, "������Ա"
		, "221122"
		, "2019-9-1"
		, "��������̫̫����·"
		, "2019��У������ѧ��"
	}
	, {
			"�ܰ�"
			, "202190603"
			, "���������ѧԺ"
			, "����ý�弼��"
			, "��Ƕ192"
			, "Ů"
			, "zhagn3@gmail.com"
			, "�����Ͼ�"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "��"
			, "������Ա"
			, "221122"
			, "2019-9-1"
			, "��������̫̫����·"
			, "2019��У������ѧ��"
		}
	, {
			"���"
			, "202190603"
			, "���������ѧԺ"
			, "����ý�弼��"
			, "��Ƕ192"
			, "Ů"
			, "zhagn3@gmail.com"
			, "�����Ͼ�"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "��"
			, "������Ա"
			, "221122"
			, "2019-9-1"
			, "��������̫̫����·"
			, "2019��У������ѧ��"
		}
	, {
			"֣ʮ"
			, "202190603"
			, "���������ѧԺ"
			, "����ý�弼��"
			, "��Ƕ192"
			, "Ů"
			, "zhagn3@gmail.com"
			, "�����Ͼ�"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "��"
			, "������Ա"
			, "221122"
			, "2019-9-1"
			, "��������̫̫����·"
			, "2019��У������ѧ��"
		}
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QSplitter splitterMain(Qt::Horizontal);
    splitterMain.setOpaqueResize(true);

    QListWidget list(&splitterMain);
	StudentInfoWidget studentInfoWiget(&splitterMain);
   QObject::connect(&list, &QListWidget::currentRowChanged, &studentInfoWiget, [&](int n) {studentInfoWiget.stickStudent(students[n]); });

    list.insertItem(0, "��һ");
    list.insertItem(1, "�¶�");
    list.insertItem(2, "����");
    list.insertItem(3, "����");
    list.insertItem(4, "����");
    list.insertItem(5, "����");
    list.insertItem(6, "����");
    list.insertItem(7, "�ܰ�");
    list.insertItem(8, "���");
    list.insertItem(9, "֣ʮ");
	studentInfoWiget.stickStudent(students[0]);

     // ���������ֿ�ˮƽ�ָ�ı���
    splitterMain.setWindowTitle("ѧ����Ϣ����");
    splitterMain.setMinimumSize(splitterMain.minimumSize());
    splitterMain.setMaximumSize(splitterMain.maximumSize());
    splitterMain.show();
    return a.exec();
}
