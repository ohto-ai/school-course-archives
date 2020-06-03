#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "ui_PaintWidget.h"
#include "PaintObject.h"
#include <list>
#include <functional>

class PaintWidget : public QWidget
{
	Q_OBJECT

public:
	enum PaintMode : int
	{
		PAINT_NULL
		, PAINT_PENCIL				// 铅笔
		, PAINT_LINE				// 直线
		, PAINT_CIRCLE				// 圆形
		, PAINT_ELLIPSE				// 椭圆
		, PAINT_RECTANGLE			// 矩形
		, PAINT_ROUNDEDRECTANGLE	// 圆角矩形
		, PAINT_POLYGON				// 多边形
	};

	PaintWidget(QWidget* parent = Q_NULLPTR);
	~PaintWidget();

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

	void setForeColor(QColor);
	QColor getForeColor()const;
	void setPenWidth(int);
	void setBackColor(QColor);
	QColor getBackColor()const;
	void switchPaintMode(PaintMode);
	void clearPaint();
	QString exportSvg()const;
	void setPaintObjectCreateCallBack(std::function<void(PaintMode, const thatboy::qt::PaintObject*)>);
private:
	void pushPaintObject();

	Ui::PaintWidget ui;
	QPen thisPen{ Qt::black,1,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin };
	QColor backColor = Qt::white;

	PaintMode paintMode{ PAINT_NULL };
	bool continusStatus = false;	// 在连续画线（多边形）

	thatboy::qt::PaintObject* currentObject = nullptr;
	std::function<void(PaintMode, const thatboy::qt::PaintObject*)> onPaintObjectCreate;
	std::vector<thatboy::qt::PaintObject*> paintObjList;	// 绘制对象列表
};
