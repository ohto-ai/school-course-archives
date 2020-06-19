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
			currentObject = new thatboy::qt::PolylineObject();
			dynamic_cast<thatboy::qt::PolylineObject*>(currentObject)->append(event->pos());
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_LINE:
			currentObject = new thatboy::qt::LineObject(QLine(event->pos(), event->pos()));
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_CIRCLE:
			currentObject = new thatboy::qt::CircleObject(QPoint(event->pos()));
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_ELLIPSE:
			currentObject = new thatboy::qt::EllipseObject(QRect(event->pos(), event->pos()));
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_RECTANGLE:
			currentObject = new thatboy::qt::RectangleObject(QRect(event->pos(), event->pos()));
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_ROUNDEDRECTANGLE:
			currentObject = new thatboy::qt::RoundedRectangleObject(QRect(event->pos(), event->pos()));
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			break;
		case PaintWidget::PAINT_POLYGON:
			if (currentObject == nullptr)
			{
				currentObject = new thatboy::qt::PolygonObject();
				dynamic_cast<thatboy::qt::PolygonObject*>(currentObject)->append(event->pos());
			}
			dynamic_cast<thatboy::qt::PaintShapeObject*>(currentObject)->QPen::operator=(thisPen);
			dynamic_cast<thatboy::qt::PolygonObject*>(currentObject)->append(event->pos());
			break;
		default:
			break;
		}
		break;

	case Qt::RightButton:
		pushPaintObject();
		break;
	default:
		break;
	}
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		switch (paintMode)
		{
		case PaintWidget::PAINT_NULL:
			break;
		case PaintWidget::PAINT_ROUNDEDRECTANGLE:
		case PaintWidget::PAINT_RECTANGLE:
		case PaintWidget::PAINT_ELLIPSE:
			dynamic_cast<QRect*>(currentObject)->operator=(dynamic_cast<QRect*>(currentObject)->normalized());
		case PaintWidget::PAINT_PENCIL:
		case PaintWidget::PAINT_LINE:
		case PaintWidget::PAINT_CIRCLE:
			pushPaintObject();
			break;
		case PaintWidget::PAINT_POLYGON:
			break;
		default:
			break;
		}
		break;

	case Qt::RightButton:
		pushPaintObject();
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
			dynamic_cast<thatboy::qt::PolylineObject*>(currentObject)->append(event->pos());
			break;
		case PaintWidget::PAINT_LINE:
			dynamic_cast<thatboy::qt::LineObject*>(currentObject)->setP2(event->pos());
			break;
		case PaintWidget::PAINT_CIRCLE:
		{
			auto& circle = *dynamic_cast<thatboy::qt::CircleObject*>(currentObject);
			circle.setR(sqrt((event->pos().x() - circle.x()) * (event->pos().x() - circle.x())
				+ (event->pos().y() - circle.y()) * (event->pos().y() - circle.y())));
		}
		break;
		case PaintWidget::PAINT_ELLIPSE:
			dynamic_cast<thatboy::qt::EllipseObject*>(currentObject)->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_RECTANGLE:
			dynamic_cast<thatboy::qt::RectangleObject*>(currentObject)->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_ROUNDEDRECTANGLE:
			dynamic_cast<thatboy::qt::RoundedRectangleObject*>(currentObject)->setBottomRight(event->pos());
			break;
		case PaintWidget::PAINT_POLYGON:
			dynamic_cast<thatboy::qt::PolygonObject*>(currentObject)->back() = event->pos();
			break;
		default:
			break;
		}
		update();
	}
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter;// (this);
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(rect(), backColor);
	for (auto& obj : paintObjList)
		obj->draw(painter);
	if (currentObject)
		currentObject->drawHalf(painter);

	if (selectedObject)
	{
		selectedObject->draw(painter);
	}

	painter.end();
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
	pushPaintObject();
	paintMode = mode;
}

void PaintWidget::clearPaint()
{
	continusStatus = false;
	currentObject = nullptr;
	paintObjList.clear();
	update();
}

QString PaintWidget::exportSvg() const
{
	QString svg;
	svg += QString::asprintf(R"(<!DOCTYPE html>
<html>
<body>
<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="%d" height="%d">
)", width(), height());
	for (auto obj : paintObjList)
		svg += obj->exportSvgObject() + "\n";
	svg += R"(
</svg>

</body>
</html>)";

	return svg;
}

void PaintWidget::exportQPicture(QString file) const
{
	QPicture picture;
	QPainter painter;
	painter.begin(&picture);
	for (auto& obj : paintObjList)
		obj->draw(painter);
	painter.end();
	picture.save(file);
}

void PaintWidget::setPaintObjectCreateCallBack(std::function<void(PaintMode, const thatboy::qt::PaintObject*)> func)
{
	onPaintObjectCreate = func;
}



bool PaintWidget::removePaintObject(int ptr)
{
	if (ptr >= 0 && ptr < paintObjList.size())
		paintObjList.erase(paintObjList.begin() + ptr);
	else
		return false;
	return true;
}

bool PaintWidget::selectPaintObject(int ptr)
{
	if (ptr >= 0 && ptr < paintObjList.size())
		selectedObject = &paintObjList[ptr];
	else
		return false;
	return true;
}

void PaintWidget::pushPaintObject()
{
	if (currentObject != nullptr)
	{
		paintObjList.push_back(currentObject);
		if (onPaintObjectCreate)
			onPaintObjectCreate(paintMode, currentObject);
		currentObject = nullptr;
		update();
	}
}
