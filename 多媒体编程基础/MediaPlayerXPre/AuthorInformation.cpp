#include "AuthorInformation.h"

AuthorInformation::AuthorInformation(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btnMail, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("mailto:zhu.thatboy@outlook.com")); });
    connect(ui.btnGithub, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("https://github.com/thatboy-echo")); });
    connect(ui.btnWebsite, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("https://thatboy.info")); });
}
