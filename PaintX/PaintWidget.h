#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "ui_PaintWidget.h"

class PaintWidget : public QWidget
{
	Q_OBJECT

public:
	PaintWidget(QWidget *parent = Q_NULLPTR);
	~PaintWidget();

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
private:

	enum : int
	{
		PAINT_PENCIL				// Ç¦±Ê
		, PAINT_LINE				// Ö±Ïß
		, PAINT_CIRCLE				// Ô²ÐÎ
		, PAINT_RECTANGLE			// ¾ØÐÎ
		, PAINT_ROUNDEDRECTANGLE	// Ô²½Ç¾ØÐÎ
		, PAINT_POLYGON				// ¶à±ßÐÎ
		, PAINT_FILL				// ÓÍÆáÍ°
		, PAINT_ERASER				// ÏðÆ¤²Á
		, PAINT_PICKER				// È¡É«Æ÷
	};
	QColor foreColor = Qt::black;
	QColor backColor = Qt::white;

	Ui::PaintWidget ui;
	QPoint mousePressCoord;
	QPoint mouseReleaseCoord;
};
