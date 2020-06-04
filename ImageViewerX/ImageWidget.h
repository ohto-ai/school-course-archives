#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QWheelEvent>
#include <QFileDialog>

class ImageWidget : public QWidget
{
	Q_OBJECT

public:
	ImageWidget(QWidget *parent = Q_NULLPTR);
	~ImageWidget();
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	virtual void wheelEvent(QWheelEvent*);
	virtual void mouseDoubleClickEvent(QMouseEvent*);

	void load(QString);
	void autoScale();
private:
	QImage image;
	qreal scale = 1.0;
	QPoint drawCoord;
	QPoint mouseCoord;
};
