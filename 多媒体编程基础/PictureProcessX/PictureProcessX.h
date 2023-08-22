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

	void light();
	void binarize();
	void mosaic();
	void emboss();

	void neon();
	void gauss();
	void exposure();
	void diffuse();

	void nostalgic();
	void blackWhiteComics();

	void reverseColor();
	void gray();
private:
	friend class MultiMediaSystem;
	void updateImageView();

	Ui::PictureProcessXClass ui;
	QImage oriImage;
};
