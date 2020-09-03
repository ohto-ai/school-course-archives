#pragma once

#include <QDialog>
#include "ui_OptionDialog.h"

class OptionDialog : public QDialog
{
	Q_OBJECT

public:
	friend class MediaPlayerXPre;
	OptionDialog(QWidget *parent = Q_NULLPTR);
	~OptionDialog();

private:
	Ui::OptionDialog ui;
};
