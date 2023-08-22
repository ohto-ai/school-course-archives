#include "TBPushButton.h"

TBPushButton::TBPushButton(QWidget *parent)
	: QPushButton(parent)
{
}

TBPushButton::~TBPushButton()
{
}

void TBPushButton::mouseReleaseEvent(QMouseEvent* e)
{
	if (rect().contains(e->pos()))
		switch (e->button())
		{
		case Qt::LeftButton:
			emit leftClicked();
			break;
		case Qt::RightButton:
			emit rightClicked();
			break;
		case Qt::MidButton:
			emit midClicked();
			break;
		default:
			break;
		}
	return QPushButton::mouseReleaseEvent(e);
}
