#ifndef SHAPES_H
#define SHAPES_H

//#include <QApplication>
#include <QPainter>
#include "vector.h"

using std::string;
using namespace project;

namespace Shapes {

// Specification for Shape class
class Shape
{
public:
	enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Text};

	Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape);
	virtual ~Shape() { }

	ShapeType getShape() const;
	const QPen& getPen() const;
	const QBrush& getBrush() const;

	void setShape(ShapeType shape);
	void setPen (Qt::GlobalColor color, int width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join);
	void setPenColor(Qt::GlobalColor color);
	void setPenWidth(int width);
	void setPenStyle(Qt::PenStyle style);
	void setPenCapStyle(Qt::PenCapStyle cap);
	void setPenJoinStyle(Qt::PenJoinStyle join);

	void setBrush(Qt::GlobalColor color, Qt::BrushStyle style);
	void setBrushColor(Qt::GlobalColor color);
	void setBrushStyle(Qt::BrushStyle style);

	void defaultStyle();
	void drawRectangle(int width, int height);
	void drawID();

	void setXY(int x, int y);
	int getX();
	int getY();
	int getId();

	virtual void draw(const int translateX, const int translateY) = 0;

protected:
	QPainter& getQPainter();

private:
	QPainter qpainter;

	int x {0};
	int y {0};
	int id;
	ShapeType shape;
	QPen pen;
	QBrush brush;
};


// Specification for Line class
class Line : public Shape
{
public:
	Line(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Line} {}
	~Line() override {}

	void setPoints(const QPoint& pointBegin, const QPoint& pointEnd);

	void draw(const int translateX = 0, const int translateY = 0) override;

private:
	QPoint pointBegin;
	QPoint pointEnd;
};


// Specification for Polyline class
class Polyline : public Shape
{
public:
	Polyline(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Polyline} {}
	~Polyline() override {}

	void setPoint(const QPoint& point);

	void draw(const int translateX = 0, const int translateY = 0) override;

private:
	vector<QPoint> points;
};


class Polygon : public Shape
{
public:
	Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Polygon} {}
	~Polygon() override {}

	void setPoint(const QPoint& point);

	void draw(const int translateX = 0, const int translateY = 0) override;

private:
	project::vector<QPoint> points;
};

class Rectangle : public Shape
{
public:
	Rectangle(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Rectangle} {}
	~Rectangle() override {}

	void setRectangle(const QRect& rect);

	void draw(const int translateX = 0, const int translateY = 0) override;
private:
	QRect rect;
};

class Ellipse : public Shape
{
public:
	Ellipse(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Ellipse} {}
	~Ellipse() override {}

	void setEllipse(const QRect& rect);

	void draw(const int translateX = 0, const int translateY = 0) override;
private:
	QRect rect;
};

class Text : public Shape
{
public:
	Text(QPaintDevice* device = nullptr, int id = -1) : Shape{device, id, ShapeType::Text} {}
	~Text() override {}

	void setText(const QRect& rect, const QString& text);
	void setFont(const QString& family, QFont::Weight weight, QFont::Style style, int size, Qt::AlignmentFlag alignment);

	void setFont(const QString& family);
	void setString(const QString& text);
	void setRect(const QRect& rect);
	void setWeight(QFont::Weight weight);
	void setStyle(QFont::Style style);
	void setPointSize(int size);
	void setAlignment(Qt::AlignmentFlag alignment);

	void draw(const int translateX = 0, const int translateY = 0) override;

private:
	QFont font;
	QString text;
	QRect rect;
	Qt::AlignmentFlag alignment;
};

} // end of Shapes namespace

#endif // SHAPES_H
