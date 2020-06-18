#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QWheelEvent>
#include <QFileDialog>

class ImageView : public QWidget
{
	Q_OBJECT

public:
	ImageView(QWidget* parent = Q_NULLPTR);
	~ImageView();
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	virtual void wheelEvent(QWheelEvent*);
	virtual void mouseDoubleClickEvent(QMouseEvent*);

	QImage& image();
	void load(QImage);
	void load(QString);
	void loadDialog();
	void autoScale();
	qreal& rotate();
	void setMirror(bool, bool);
	void setMirrorHor(bool);
	void setMirrorVer(bool);
private:
	bool mirrorHorizontally{ false };
	bool mirrorVertically{ false };
	qreal _rotate{ 0 };
	QImage _image;
	qreal scale{ 1.0 };
	QPointF drawCoord;
	QPoint mouseCoord;
};
