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
		PAINT_PENCIL				// Ǧ��
		, PAINT_LINE				// ֱ��
		, PAINT_CIRCLE				// Բ��
		, PAINT_RECTANGLE			// ����
		, PAINT_ROUNDEDRECTANGLE	// Բ�Ǿ���
		, PAINT_POLYGON				// �����
		, PAINT_FILL				// ����Ͱ
		, PAINT_ERASER				// ��Ƥ��
		, PAINT_PICKER				// ȡɫ��
	};
	QColor foreColor = Qt::black;
	QColor backColor = Qt::white;

	Ui::PaintWidget ui;
	QPoint mousePressCoord;
	QPoint mouseReleaseCoord;
};
