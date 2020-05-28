#include "PaintWidget.h"

PaintWidget::PaintWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PaintWidget::~PaintWidget()
{
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		mousePressCoord = event->pos();
		break;
	default:
		break;
	}
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		mouseReleaseCoord = event->pos();
		update();
	}
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(QPen(QColor(11, 67, 127), 3));
	painter.drawLine(mousePressCoord, mouseReleaseCoord);
}
