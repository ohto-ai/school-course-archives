#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QFontDialog>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QPrinter>
#include <QScrollBar>
#include "ui_NotepadXWindow.h"
#include "FindDialog.h"

#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")
#endif

class NotepadXWindow : public QMainWindow
{
	Q_OBJECT

public:
	NotepadXWindow(QWidget *parent = Q_NULLPTR);
	~NotepadXWindow() = default;

private:
	friend class MultiMidiaSystem;
	Ui::NotepadXWindow ui;
	QString workingFileName;
	FindDialog findDialog{ this };
};
