#include "GridLayoutTemplate.h"

GridLayoutTemplate::GridLayoutTemplate(QWidget *parent)
	: QGridLayout(parent)
{
}

GridLayoutTemplate::~GridLayoutTemplate()
{
}

void GridLayoutTemplate::pushWidgets(std::initializer_list<QWidget*>widgetList)
{
	int nCol = 0;
	for (auto& widget : widgetList)
		QGridLayout::addWidget(widget, curRow, nCol++);
	curRow++;
}
