#include "PaintWidget.h"

PaintWidget::PaintWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PaintWidget::~PaintWidget()
{
	//for (auto ptr : paintObjList)
	//	delete ptr;
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		switch (paintMode)
		{
		case PaintWidget::PAINT_NULL:
			break;
		case PaintWidget::PAINT_PENCIL:
			paintObjList.push_back(new thatboy::qt::PolylineObject());
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_PENCIL, paintObjList.back());
			dynamic_cast<thatboy::qt::PolylineObject*>(paintObjList.back())->append(event->pos());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_LINE:
			paintObjList.push_back(new thatboy::qt::LineObject(QLine(event->pos(), event->pos())));
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_LINE, paintObjList.back());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_CIRCLE:
			paintObjList.push_back(new thatboy::qt::CircleObject(QPoint(event->pos())));
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_CIRCLE, paintObjList.back());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_ELLIPSE:
			paintObjList.push_back(new thatboy::qt::EllipseObject(QRect(event->pos(), event->pos())));
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_ELLIPSE, paintObjList.back());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_RECTANGLE:
			paintObjList.push_back(new thatboy::qt::RectangleObject(QRect(event->pos(), event->pos())));
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_RECTANGLE, paintObjList.back());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_ROUNDEDRECTANGLE:
			paintObjList.push_back(new thatboy::qt::RoundedRectangleObject(QRect(event->pos(), event->pos())));
			if (onPaintObjectCreate)
				onPaintObjectCreate(PAINT_ROUNDEDRECTANGLE, paintObjList.back());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_POLYGON:

			if (continusStatus)
			{
				dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
				dynamic_cast<thatboy::qt::PolygonObject*>(paintObjList.back())->append(event->pos());
			}
			else
			{
				continusStatus = true;
				paintObjList.push_back(new thatboy::qt::PolygonObject());
				if (onPaintObjectCreate)
					onPaintObjectCreate(PAINT_POLYGON, paintObjList.back());
				dynamic_cast<thatboy::qt::PaintShapeObject*>(paintObjList.back())->QPen::operator=(thisPen);
				dynamic_cast<thatboy::qt::PolygonObject*>(paintObjList.back())->append(event->pos());
				dynamic_cast<thatboy::qt::PolygonObject*>(paintObjList.back())->append(event->pos());
			}
			break;
		default:
			break;
		}
		break;

	case Qt::RightButton:
		continusStatus = false;
		break;
	default:
		break;
	}
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		switch (paintMode)
		{
		case PaintWidget::PAINT_NULL:
			break;
		case PaintWidget::PAINT_PENCIL:
			dynamic_cast<thatboy::qt::PolylineObject*>(paintObjList.back())->append(event->pos());
			break;
		case PaintWidget::PAINT_LINE:
			dynamic_cast<thatboy::qt::LineObject*>(paintObjList.back())->setP2(event->pos());
			break;
		case PaintWidget::PAINT_CIRCLE:
		{
			auto& circle = *dynamic_cast<thatboy::qt::CircleObject*>(paintObjList.back());
			circle.setR(sqrt((event->pos().x() - circle.x()) * (event->pos().x() - circle.x())
				+ (event->pos().y() - circle.y()) * (event->pos().y() - circle.y())));
		}
		break;
		case PaintWidget::PAINT_ELLIPSE:
			dynamic_cast<thatboy::qt::EllipseObject*>(paintObjList.back())->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_RECTANGLE:
			dynamic_cast<thatboy::qt::RectangleObject*>(paintObjList.back())->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_ROUNDEDRECTANGLE:
			dynamic_cast<thatboy::qt::RoundedRectangleObject*>(paintObjList.back())->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_POLYGON:
			dynamic_cast<thatboy::qt::PolygonObject*>(paintObjList.back())->back() = event->pos();
			break;
		default:
			break;
		}
		update();
	}
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(rect(), backColor);
	for (auto& obj : paintObjList)
		obj->draw(painter);
}

void PaintWidget::setForeColor(QColor c)
{
	thisPen.setColor(c);
}

QColor PaintWidget::getForeColor()const
{
	return thisPen.color();
}

void PaintWidget::setPenWidth(int w)
{
	thisPen.setWidth(w);
}

void PaintWidget::setBackColor(QColor c)
{
	backColor = c;
}

QColor PaintWidget::getBackColor()const
{
	return backColor;
}

void PaintWidget::switchPaintMode(PaintMode mode)
{
	continusStatus = false;
	paintMode = mode;
}

void PaintWidget::clearPaint()
{
	continusStatus = false;
	paintObjList.clear();
	update();
}

QString PaintWidget::exportSvg() const
{
	QString svg;
	svg += R"(<!DOCTYPE html>
<html>
<body>
<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="800" height="800">
)";
	for (auto obj : paintObjList)
		svg += obj->exportSvgObject() + "\n";
	svg += R"(
</svg>

</body>
</html>)";

	return svg;
}

void PaintWidget::setPaintObjectCreateCallBack(std::function<void(PaintMode, const thatboy::qt::PaintObject*)> func)
{
	onPaintObjectCreate = func;
}