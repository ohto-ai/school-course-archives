#pragma once

#include <QPushButton>
#include <QMouseEvent>

class TBPushButton : public QPushButton
{
	Q_OBJECT

public:
	TBPushButton(QWidget *parent);
	~TBPushButton();

	void mouseReleaseEvent(QMouseEvent*) override;
signals:
	void leftClicked();
	void rightClicked();
	void midClicked();	
	
};
