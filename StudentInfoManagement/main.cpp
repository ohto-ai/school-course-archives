
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include "StudentInfoWiget.h"


StudentInfo students[]{
	{
		.stuName = "��һ"
		, .stuNumber = "202200601"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ202"
		, .gender = "Ů"
		, .mail = "liu1@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15912152872"
		, .website = "www.liu1.com"
		, .birth = "2002-2-3"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "221122"
		, .enrollmentTime = "2020-9-1"
		, .experience = ""
		, .comments = ""
	}
	, {
		.stuName = "�¶�"
		, .stuNumber = "202190603"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ192"
		, .gender = "Ů"
		, .mail = "zhagn3@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "��������̫̫����·"
		, .comments = "2019��У������ѧ��"
	}
	, {
		.stuName = "����"
		, .stuNumber = "202200603"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ202"
		, .gender = "Ů"
		, .mail = "zhagn3@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-10-3"
		, .nationality = "��"
		, .politicalOrientation = "Ⱥ��"
		, .postcode = "221122"
		, .enrollmentTime = "2020-9-1"
		, .experience = "��������̫̫����·"
		, .comments = "2020��У������ѧ��"
		, .photo = "girl.png"
	}
	, {
		.stuName = "����"
		, .stuNumber = "202200604"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ202"
		, .gender = "��"
		, .mail = "li4@gmail.com"
		, .address = "��������"
		, .phoneNumber = "15151511223"
		, .website = "www.li4happy.com"
		, .birth = "2002-1-12"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "231117"
		, .enrollmentTime = "2020-9-1"
		, .experience = "��"
		, .comments = "2020���θ��������һ��"
		, .photo = "boy.png"
	}
	, {
		.stuName = "����"
		, .stuNumber = "202190603"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ192"
		, .gender = "Ů"
		, .mail = "zhagn3@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "��������̫̫����·"
		, .comments = "2019��У������ѧ��"
	}
	, {
		.stuName = "����"
		, .stuNumber = "202190603"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ192"
		, .gender = "Ů"
		, .mail = "zhagn3@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "��������̫̫����·"
		, .comments = "2019��У������ѧ��"
	}
	, {
		.stuName = "����"
		, .stuNumber = "202190603"
		, .departmentName = "���������ѧԺ"
		, .majorName = "����ý�弼��"
		, .className = "��Ƕ192"
		, .gender = "Ů"
		, .mail = "zhagn3@gmail.com"
		, .address = "�����Ͼ�"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "��"
		, .politicalOrientation = "������Ա"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "��������̫̫����·"
		, .comments = "2019��У������ѧ��"
	}
	, {
			.stuName = "�ܰ�"
			, .stuNumber = "202190603"
			, .departmentName = "���������ѧԺ"
			, .majorName = "����ý�弼��"
			, .className = "��Ƕ192"
			, .gender = "Ů"
			, .mail = "zhagn3@gmail.com"
			, .address = "�����Ͼ�"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "��"
			, .politicalOrientation = "������Ա"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "��������̫̫����·"
			, .comments = "2019��У������ѧ��"
		}
	, {
			.stuName = "���"
			, .stuNumber = "202190603"
			, .departmentName = "���������ѧԺ"
			, .majorName = "����ý�弼��"
			, .className = "��Ƕ192"
			, .gender = "Ů"
			, .mail = "zhagn3@gmail.com"
			, .address = "�����Ͼ�"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "��"
			, .politicalOrientation = "������Ա"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "��������̫̫����·"
			, .comments = "2019��У������ѧ��"
		}
	, {
			.stuName = "֣ʮ"
			, .stuNumber = "202190603"
			, .departmentName = "���������ѧԺ"
			, .majorName = "����ý�弼��"
			, .className = "��Ƕ192"
			, .gender = "Ů"
			, .mail = "zhagn3@gmail.com"
			, .address = "�����Ͼ�"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "��"
			, .politicalOrientation = "������Ա"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "��������̫̫����·"
			, .comments = "2019��У������ѧ��"
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
