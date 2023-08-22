#pragma once

#include <QtWidgets/QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include "ui_AuthorInformation.h"

class AuthorInformation : public QMainWindow
{
    Q_OBJECT

public:
    AuthorInformation(QWidget *parent = Q_NULLPTR);

private:
    Ui::AuthorInformationClass ui;
};
