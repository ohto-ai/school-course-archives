#include "ImageView.h"

ImageView::ImageView(QWidget* parent)
	: QWidget(parent)
{
}

ImageView::~ImageView()
{
}

void ImageView::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		mouseCoord = event->pos();
	default:
		break;
	}
}

void ImageView::mouseMoveEvent(QMouseEvent* event)
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

void ImageView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.scale(scale, scale);
	painter.drawImage(drawCoord / scale, _image);
}

void ImageView::wheelEvent(QWheelEvent* event)
{
	scale *= event->delta() > 0 ? 1.1 : 0.9;
	update();
}

void ImageView::mouseDoubleClickEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		if (_image.isNull())
			loadDialog();
		autoScale();
		break;
	case Qt::RightButton:
		scale = 1;
		update();
	default:
		break;
	}
}

QImage& ImageView::image()
{
	return _image;
}

void ImageView::load(QImage img)
{
	_image = img;
	autoScale();
}

void ImageView::load(QString file)
{
	if (file.isEmpty())
		return;
	_image.load(file);
	autoScale();
}

void ImageView::loadDialog()
{
	return load(QFileDialog::getOpenFileName(this, "Open", "", "Image file(*.bmp;*.png;*.jpg;*.jpeg;)"));
}

void ImageView::autoScale()
{
	if (_image.width() < rect().width() && _image.height() < rect().height())
		scale = 1;
	else if ((qreal)rect().width() / rect().height() < (qreal)_image.width() / _image.height())
		scale = (qreal)rect().width() / _image.width();
	else
		scale = (qreal)rect().height() / _image.height();
	drawCoord = QPoint(-(_image.width() * scale - rect().width()) / 2, -(_image.height() * scale - rect().height()) / 2);
	update();
}

