#pragma once
#include <QPainter>

namespace thatboy
{
	namespace  qt
	{
		// 保留类的默认构造与赋值函数
#define DEFAULT_CONSTRUCT(_class) \
		_class() = default; \
		_class(const _class&) = default; \
		_class(_class&&) = default; \
		_class& operator=(const _class&) = default;

		/// <summary>
		/// 绘制对象类
		/// </summary>
		struct PaintObject
		{
			virtual void draw(QPainter&) = 0;
			virtual void drawHalf(QPainter& p)
			{
				draw(p);
			}
			virtual void drawSelected(QPainter& p)
			{
				draw(p);
			}
			virtual QString exportSvgObject() = 0;
		};

		/// <summary>
		/// 形状类
		/// </summary>
		struct PaintShapeObject
			: virtual public PaintObject
			, virtual public QPen
		{
		};

		/// <summary>
		/// 线条
		/// </summary>
		struct LineObject
			: virtual public PaintShapeObject
			, virtual public QLine

		{
			DEFAULT_CONSTRUCT(LineObject)
				using QLine::QLine;
			LineObject(const QLine& l) :QLine(l) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawLine(*this);
			}
			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba())&0XFFFFFF);
				painter.setPen(pen);
				painter.drawLine(*this);
			}

			virtual QString exportSvgObject()
			{
				return QString().sprintf(R"(<line x1="%d" y1="%d" x2="%d" y2="%d" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, p1().x(), p1().y(), p2().x(), p2().y(), QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
			}
		};

		/// <summary>
		/// 矩形
		/// </summary>
		struct RectangleObject
			: virtual public PaintShapeObject
			, virtual public QRect
		{
			DEFAULT_CONSTRUCT(RectangleObject)
				using QRect::QRect;
			RectangleObject(const QRect& r) :QRect(r) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawRect(*this);
			}
			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawRect(*this);
			}

			virtual QString exportSvgObject()
			{
				return QString().sprintf(R"(<rect x="%d" y="%d" width="%d" height="%d" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, x(), y(), QRect::width(), height(), QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
			}
		};

		/// <summary>
		/// 圆形
		/// </summary>
		struct CircleObject
			: virtual public PaintShapeObject
			, virtual public QPoint
		{
			DEFAULT_CONSTRUCT(CircleObject)
				int r{ 0 };
			void setR(int _r) { r = _r; }

			using QPoint::QPoint;
			CircleObject(const QPoint& p) :QPoint(p) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawEllipse(*this, r, r);
			}
			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawEllipse(*this, r, r);
			}

			virtual QString exportSvgObject()
			{
				return QString().sprintf(R"(<circle cx="%d" cy="%d" r="%d" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, x(), y(), r, QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
			}
		};

		/// <summary>
		/// 椭圆
		/// </summary>
		struct EllipseObject
			: virtual public PaintShapeObject
			, virtual public QRect
		{
			DEFAULT_CONSTRUCT(EllipseObject)
				using QRect::QRect;
			EllipseObject(const QRect& r) :QRect(r) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawEllipse(*this);
			}
			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawEllipse(*this);
			}

			virtual QString exportSvgObject()
			{
				return QString().sprintf(R"(<ellipse cx="%d" cy="%d" rx="%d" ry="%d" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, center().x(), center().y(), QRect::width() / 2, height() / 2, QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
			}
		};

		/// <summary>
		/// 圆角矩形
		/// </summary>
		struct RoundedRectangleObject
			: virtual public PaintShapeObject
			, virtual public QRect
		{
			DEFAULT_CONSTRUCT(RoundedRectangleObject)
				int xR{ 15 };
			int yR{ 15 };
			void setR(int _xr, int _yr) { xR = _xr; yR = _yr; }

			using QRect::QRect;
			RoundedRectangleObject(const QRect& r) :QRect(r) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawRoundRect(*this, xR, yR);
			}

			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawRoundRect(*this, xR, yR);
			}

			virtual QString exportSvgObject()
			{
				return QString().sprintf(R"(<rect x="%d" y="%d" width="%d" height="%d" rx="%d" ry="%d" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, x(), y(), QRect::width(), height(), xR, yR, QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
			}
		};

		/// <summary>
		/// 多边形
		/// </summary>
		struct PolygonObject
			: virtual public  PaintShapeObject
			, virtual public  QPolygon
		{
			DEFAULT_CONSTRUCT(PolygonObject)
				using QPolygon::QPolygon;
			PolygonObject(const QPolygon& p) :QPolygon(p) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawPolygon(*this);
			}

			virtual void drawHalf(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawPolyline(*this);
			}

			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawPolygon(*this);
			}


			virtual QString exportSvgObject()
			{
				QString svg;
				svg += R"(<polygon points=")";
				for (auto& pt : *this)
					svg += QString().sprintf("%d,%d ", pt.x(), pt.y());
				svg += QString().sprintf(R"(" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
				return svg;
			}
		};

		/// <summary>
		/// 连续线段
		/// </summary>
		struct PolylineObject
			: virtual public  PaintShapeObject
			, virtual public  QPolygon
		{
			DEFAULT_CONSTRUCT(PolylineObject)
				using QPolygon::QPolygon;
			PolylineObject(const QPolygon& p) :QPolygon(p) {}

			virtual void draw(QPainter& painter)
			{
				painter.setPen(*this);
				painter.drawPolyline(*this);
			}

			virtual void drawSelected(QPainter& painter)
			{
				QPen pen = *this;
				pen.setColor((~(*this).color().rgba()) & 0XFFFFFF);
				painter.setPen(pen);
				painter.drawPolyline(*this);
			}


			virtual QString exportSvgObject()
			{
				QString svg;
				svg += R"(<polyline points=")";
				for (auto& pt : *this)
					svg += QString().sprintf("%d,%d ", pt.x(), pt.y());
				svg += QString().sprintf(R"(" stroke="#%02X%02X%02X" stroke-width="%d" fill="none"/>)"
					, QPen::color().red(), QPen::color().green(), QPen::color().blue(), QPen::width());
				return svg;
			}
		};
#undef DEFAULT_CONSTRUCT
	}
}