#include "Dialog.h"
#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8") 
#endif // Q_OS_WIN
Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
	, mainLayout(this)
{
	setWindowTitle(tr("各种标准对话框的实例"));

	fileBtn.setText(tr("文件标准对话框实例"));
	colorBtn.setText(tr("颜色标准对话框实例"));
	fontBtn.setText(tr("字体标准对话框实例"));

	colorFrame.setFrameShape(QFrame::Box);
	colorFrame.setAutoFillBackground(true);

	fontLineEdit.setText(tr("Welcome!你好"));

	mainLayout.addWidget(&fileBtn, 0, 0);
	mainLayout.addWidget(&fileLineEdit, 0, 1);
	mainLayout.addWidget(&colorBtn, 1, 0);
	mainLayout.addWidget(&colorFrame, 1, 1);
	mainLayout.addWidget(&fontBtn, 2, 0);
	mainLayout.addWidget(&fontLineEdit, 2, 1);
	
	connect(&fileBtn, &QPushButton::clicked, this, [&]() 
		{
			fileLineEdit.setText(QFileDialog::getOpenFileName(this, "打开文件", "/", "C++ 源文件(*.cpp);;C 源文件(*.c);;头文件(*.h)"));
		});

	connect(&colorBtn, &QPushButton::clicked, this, [&]()
		{
			auto c = QColorDialog::getColor(Qt::blue);
			if (c.isValid())
				colorFrame.setPalette(c);
		});
	connect(&fontBtn, &QPushButton::clicked, this, [&]()
		{
			bool ok;
			auto font = QFontDialog::getFont(&ok);
			if (ok)
				fontLineEdit.setFont(font);
		});
}
