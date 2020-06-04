#include "ImageWidget.h"

ImageWidget::ImageWidget(QWidget *parent)
	: QWidget(parent)
{
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		mouseCoord = event->pos();
	default:
		break;
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent* event)
{
	switch (event->buttons())
	{
	case Qt::LeftButton:
		drawCoord += (event->pos() - mouseCoord);
		mouseCoord = event->pos();
		update();
	default:
		break;
	}
}

void ImageWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.scale(scale, scale);
	painter.drawImage(drawCoord / scale, image);
}

void ImageWidget::wheelEvent(QWheelEvent* event)
{
	scale *= event->delta() > 0 ? 1.1 : 0.9;
	update();
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		if(image.isNull())
			load(QFileDialog::getOpenFileName(this, "Open", "/", "Image file(*.bmp;*.png;*.jpg;*.jpeg;)"));
		autoScale();
		break;
	case Qt::RightButton:
		scale = 1;
		update();
	default:
		break;
	}
}

void ImageWidget::load(QString file)
{
	if (file.isEmpty())
		return;
	image.load(file); 
	autoScale();
}

void ImageWidget::autoScale()
{
	if (image.width() < rect().width() && image.height() < rect().height())
		scale = 1;
	else if ((qreal)rect().width() / rect().height() < (qreal)image.width() / image.height())
		scale = (qreal)rect().width() / image.width();
	else
		scale = (qreal)rect().height() / image.height();
	drawCoord = QPoint(-(image.width()*scale - rect().width()) / 2, -(image.height() * scale - rect().height()) / 2);
	update();
}

