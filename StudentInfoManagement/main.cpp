
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include "StudentInfoWiget.h"


StudentInfo students[]{
	{
		  "刘一"
		, "202200601"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌202"
		, "女"
		, "liu1@gmail.com"
		, "江苏南京"
		, "15912152872"
		, "www.liu1.com"
		, "2002-2-3"
		, "汉"
		, "共产党员"
		, "221122"
		, "2020-9-1"
		, ""
		, ""
	}
	, {
		"陈二"
		, "202190603"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌192"
		, "女"
		, "zhagn3@gmail.com"
		, "江苏南京"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "汉"
		, "共青团员"
		, "221122"
		, "2019-9-1"
		, "曾扶过老太太过马路"
		, "2019年校级三好学生"
	}
	, {
		"张三"
		, "202200603"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌202"
		, "女"
		, "zhagn3@gmail.com"
		, "江苏南京"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-10-3"
		, "汉"
		, "群众"
		, "221122"
		, "2020-9-1"
		, "曾扶过老太太过马路"
		, "2020年校级三好学生"
		, "girl.png"
	}
	, {
		"李四"
		, "202200604"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌202"
		, "男"
		, "li4@gmail.com"
		, "江苏徐州"
		, "15151511223"
		, "www.li4happy.com"
		, "2002-1-12"
		, "汉"
		, "共青团员"
		, "231117"
		, "2020-9-1"
		, "无"
		, "2020年大胃王比赛第一名"
		, "boy.png"
	}
	, {
		"王五"
		, "202190603"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌192"
		, "女"
		, "zhagn3@gmail.com"
		, "江苏南京"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "汉"
		, "共青团员"
		, "221122"
		, "2019-9-1"
		, "曾扶过老太太过马路"
		, "2019年校级三好学生"
	}
	, {
		"赵六"
		, "202190603"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌192"
		, "女"
		, "zhagn3@gmail.com"
		, "江苏南京"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "汉"
		, "共青团员"
		, "221122"
		, "2019-9-1"
		, "曾扶过老太太过马路"
		, "2019年校级三好学生"
	}
	, {
		"孙七"
		, "202190603"
		, "计算机工程学院"
		, "数字媒体技术"
		, "数嵌192"
		, "女"
		, "zhagn3@gmail.com"
		, "江苏南京"
		, "15951511223"
		, "www.zhang3.com"
		, "2001-1-3"
		, "汉"
		, "共青团员"
		, "221122"
		, "2019-9-1"
		, "曾扶过老太太过马路"
		, "2019年校级三好学生"
	}
	, {
			"周八"
			, "202190603"
			, "计算机工程学院"
			, "数字媒体技术"
			, "数嵌192"
			, "女"
			, "zhagn3@gmail.com"
			, "江苏南京"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "汉"
			, "共青团员"
			, "221122"
			, "2019-9-1"
			, "曾扶过老太太过马路"
			, "2019年校级三好学生"
		}
	, {
			"吴九"
			, "202190603"
			, "计算机工程学院"
			, "数字媒体技术"
			, "数嵌192"
			, "女"
			, "zhagn3@gmail.com"
			, "江苏南京"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "汉"
			, "共青团员"
			, "221122"
			, "2019-9-1"
			, "曾扶过老太太过马路"
			, "2019年校级三好学生"
		}
	, {
			"郑十"
			, "202190603"
			, "计算机工程学院"
			, "数字媒体技术"
			, "数嵌192"
			, "女"
			, "zhagn3@gmail.com"
			, "江苏南京"
			, "15951511223"
			, "www.zhang3.com"
			, "2001-1-3"
			, "汉"
			, "共青团员"
			, "221122"
			, "2019-9-1"
			, "曾扶过老太太过马路"
			, "2019年校级三好学生"
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
