#include "Dialog.h"
#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8") 
#endif // Q_OS_WIN
Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
	, mainLayout(this)
{
	setWindowTitle(tr("���ֱ�׼�Ի����ʵ��"));

	fileBtn.setText(tr("�ļ���׼�Ի���ʵ��"));
	colorBtn.setText(tr("��ɫ��׼�Ի���ʵ��"));
	fontBtn.setText(tr("�����׼�Ի���ʵ��"));

	colorFrame.setFrameShape(QFrame::Box);
	colorFrame.setAutoFillBackground(true);

	fontLineEdit.setText(tr("Welcome!���"));

	mainLayout.addWidget(&fileBtn, 0, 0);
	mainLayout.addWidget(&fileLineEdit, 0, 1);
	mainLayout.addWidget(&colorBtn, 1, 0);
	mainLayout.addWidget(&colorFrame, 1, 1);
	mainLayout.addWidget(&fontBtn, 2, 0);
	mainLayout.addWidget(&fontLineEdit, 2, 1);
	
	connect(&fileBtn, &QPushButton::clicked, this, [&]() 
		{
			fileLineEdit.setText(QFileDialog::getOpenFileName(this, "���ļ�", "/", "C++ Դ�ļ�(*.cpp);;C Դ�ļ�(*.c);;ͷ�ļ�(*.h)"));
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
