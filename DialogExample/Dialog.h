#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFrame>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

class Dialog : public QDialog
{
	Q_OBJECT
public:
	Dialog(QWidget *parent = Q_NULLPTR);
	~Dialog() = default;
protected:
	QPushButton fileBtn;
	QPushButton colorBtn;
	QPushButton fontBtn;
	QLineEdit fileLineEdit;
	QLineEdit fontLineEdit;
	QGridLayout mainLayout;
	QFrame colorFrame;
};
