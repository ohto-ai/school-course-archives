#pragma once
#include <QPainter>

namespace thatboy
{
	namespace  qt
	{

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
		};

#undef DEFAULT_CONSTRUCT

	}
}



