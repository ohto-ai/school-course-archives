
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include "StudentInfoWiget.h"


StudentInfo students[]{
	{
		.stuName = "刘一"
		, .stuNumber = "202200601"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌202"
		, .gender = "女"
		, .mail = "liu1@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15912152872"
		, .website = "www.liu1.com"
		, .birth = "2002-2-3"
		, .nationality = "汉"
		, .politicalOrientation = "共产党员"
		, .postcode = "221122"
		, .enrollmentTime = "2020-9-1"
		, .experience = ""
		, .comments = ""
	}
	, {
		.stuName = "陈二"
		, .stuNumber = "202190603"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌192"
		, .gender = "女"
		, .mail = "zhagn3@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "汉"
		, .politicalOrientation = "共青团员"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "曾扶过老太太过马路"
		, .comments = "2019年校级三好学生"
	}
	, {
		.stuName = "张三"
		, .stuNumber = "202200603"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌202"
		, .gender = "女"
		, .mail = "zhagn3@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-10-3"
		, .nationality = "汉"
		, .politicalOrientation = "群众"
		, .postcode = "221122"
		, .enrollmentTime = "2020-9-1"
		, .experience = "曾扶过老太太过马路"
		, .comments = "2020年校级三好学生"
		, .photo = "girl.png"
	}
	, {
		.stuName = "李四"
		, .stuNumber = "202200604"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌202"
		, .gender = "男"
		, .mail = "li4@gmail.com"
		, .address = "江苏徐州"
		, .phoneNumber = "15151511223"
		, .website = "www.li4happy.com"
		, .birth = "2002-1-12"
		, .nationality = "汉"
		, .politicalOrientation = "共青团员"
		, .postcode = "231117"
		, .enrollmentTime = "2020-9-1"
		, .experience = "无"
		, .comments = "2020年大胃王比赛第一名"
		, .photo = "boy.png"
	}
	, {
		.stuName = "王五"
		, .stuNumber = "202190603"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌192"
		, .gender = "女"
		, .mail = "zhagn3@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "汉"
		, .politicalOrientation = "共青团员"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "曾扶过老太太过马路"
		, .comments = "2019年校级三好学生"
	}
	, {
		.stuName = "赵六"
		, .stuNumber = "202190603"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌192"
		, .gender = "女"
		, .mail = "zhagn3@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "汉"
		, .politicalOrientation = "共青团员"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "曾扶过老太太过马路"
		, .comments = "2019年校级三好学生"
	}
	, {
		.stuName = "孙七"
		, .stuNumber = "202190603"
		, .departmentName = "计算机工程学院"
		, .majorName = "数字媒体技术"
		, .className = "数嵌192"
		, .gender = "女"
		, .mail = "zhagn3@gmail.com"
		, .address = "江苏南京"
		, .phoneNumber = "15951511223"
		, .website = "www.zhang3.com"
		, .birth = "2001-1-3"
		, .nationality = "汉"
		, .politicalOrientation = "共青团员"
		, .postcode = "221122"
		, .enrollmentTime = "2019-9-1"
		, .experience = "曾扶过老太太过马路"
		, .comments = "2019年校级三好学生"
	}
	, {
			.stuName = "周八"
			, .stuNumber = "202190603"
			, .departmentName = "计算机工程学院"
			, .majorName = "数字媒体技术"
			, .className = "数嵌192"
			, .gender = "女"
			, .mail = "zhagn3@gmail.com"
			, .address = "江苏南京"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "汉"
			, .politicalOrientation = "共青团员"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "曾扶过老太太过马路"
			, .comments = "2019年校级三好学生"
		}
	, {
			.stuName = "吴九"
			, .stuNumber = "202190603"
			, .departmentName = "计算机工程学院"
			, .majorName = "数字媒体技术"
			, .className = "数嵌192"
			, .gender = "女"
			, .mail = "zhagn3@gmail.com"
			, .address = "江苏南京"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "汉"
			, .politicalOrientation = "共青团员"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "曾扶过老太太过马路"
			, .comments = "2019年校级三好学生"
		}
	, {
			.stuName = "郑十"
			, .stuNumber = "202190603"
			, .departmentName = "计算机工程学院"
			, .majorName = "数字媒体技术"
			, .className = "数嵌192"
			, .gender = "女"
			, .mail = "zhagn3@gmail.com"
			, .address = "江苏南京"
			, .phoneNumber = "15951511223"
			, .website = "www.zhang3.com"
			, .birth = "2001-1-3"
			, .nationality = "汉"
			, .politicalOrientation = "共青团员"
			, .postcode = "221122"
			, .enrollmentTime = "2019-9-1"
			, .experience = "曾扶过老太太过马路"
			, .comments = "2019年校级三好学生"
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

    list.insertItem(0, "刘一");
    list.insertItem(1, "陈二");
    list.insertItem(2, "张三");
    list.insertItem(3, "李四");
    list.insertItem(4, "王五");
    list.insertItem(5, "赵六");
    list.insertItem(6, "孙七");
    list.insertItem(7, "周八");
    list.insertItem(8, "吴九");
    list.insertItem(9, "郑十");
	studentInfoWiget.stickStudent(students[0]);

     // 设置主布局框即水平分割窗的标题
    splitterMain.setWindowTitle("学生信息管理");
    splitterMain.setMinimumSize(splitterMain.minimumSize());
    splitterMain.setMaximumSize(splitterMain.maximumSize());
    splitterMain.show();
    return a.exec();
}
