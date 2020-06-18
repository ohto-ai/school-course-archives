#pragma once

#include <QtWidgets/QMainWindow>
#include <mutex>
#include <thread>
#include <atomic>
#include "ui_PictureProcessX.h"

class PictureProcessX : public QMainWindow
{
	Q_OBJECT

public:
	PictureProcessX(QWidget* parent = Q_NULLPTR);

	std::mutex imageWriteLock;
	void gauss();
	void light();
	void reverseColor();
	void gray();
	void binarize();
private:
	void updateImageView();

	Ui::PictureProcessXClass ui;
	QImage oriImage;
};
