#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "ui_PaintWidget.h"
#include "PaintObject.h"
#include <list>

class PaintWidget : public QWidget
{
	Q_OBJECT

public:
	enum PaintMode : int
	{
		PAINT_NULL
		, PAINT_PENCIL				// Ǧ��
		, PAINT_LINE				// ֱ��
		, PAINT_CIRCLE				// Բ��
		, PAINT_ELLIPSE				// ��Բ
		, PAINT_RECTANGLE			// ����
		, PAINT_ROUNDEDRECTANGLE	// Բ�Ǿ���
		, PAINT_POLYGON				// �����
	};


	PaintWidget(QWidget *parent = Q_NULLPTR);
	~PaintWidget();

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

	void setForeColor(QColor);
	QColor getForeColor();

	void setPenWidth(int);

	void setBackColor(QColor);
	QColor getBackColor();

	void switchPaintMode(PaintMode);

	void clearPaint();
private:
	QPen thisPen{ Qt::black };
	QColor backColor = Qt::white;


	Ui::PaintWidget ui;
	PaintMode paintMode{ PAINT_NULL };

	bool continusStatus = false;	// ����������

	std::vector<thatboy::qt::PaintObject*> paintObjList;	// ���ƶ����б�
};
