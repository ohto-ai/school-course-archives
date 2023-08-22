#pragma once

#include <QDialog>
#include "ui_FindDialog.h"

class FindDialog : public QDialog
{
	Q_OBJECT

public:
	FindDialog(QWidget *parent = Q_NULLPTR);
	~FindDialog();
	Ui::FindDialog ui;

private:
};
