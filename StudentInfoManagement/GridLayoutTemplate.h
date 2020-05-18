#pragma once

#include <QGridLayout>
#include <initializer_list>

class GridLayoutTemplate : public QGridLayout
{
	Q_OBJECT

public:
	GridLayoutTemplate(QWidget *parent = nullptr);
	~GridLayoutTemplate();

	int curRow = 0;
	void pushWidgets(std::initializer_list<QWidget*>);
};
