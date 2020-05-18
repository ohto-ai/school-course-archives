#pragma once

#include <QDialog>
#include "ui_About.h"

class About : public QDialog
{
	Q_OBJECT

public:
	About(QWidget *parent = Q_NULLPTR);
	~About();

private:
	Ui::About ui;
};
