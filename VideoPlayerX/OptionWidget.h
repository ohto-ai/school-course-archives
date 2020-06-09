#pragma once

#include <QWidget>
#include "ui_OptionWidget.h"

class OptionWidget : public QWidget
{
	Q_OBJECT

public:
	OptionWidget(QWidget *parent = Q_NULLPTR);
	~OptionWidget();

private:
	Ui::OptionWidget ui;
};
