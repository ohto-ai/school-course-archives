#pragma once

#include <QDialog>
#include "GlobalConfig.h"
#include "ui_OptionDialog.h"

class OptionDialog : public QDialog
{
	Q_OBJECT

public:
	friend class MediaPlayerXPre;
	OptionDialog(QWidget *parent = Q_NULLPTR);
	~OptionDialog();

	void moveEvent(QMoveEvent* e) override;
	void resizeEvent(QResizeEvent* e) override;
private:
	Ui::OptionDialog ui;
};
