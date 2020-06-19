#include "AuthorInformation.h"

AuthorInformation::AuthorInformation(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.labelAvatar->setPixmap(QPixmap::fromImage(QImage(":/AuthorInformation/res/photo.jpg")).scaled(
        ui.labelAvatar->width()
        , ui.labelAvatar->height()
        , Qt::KeepAspectRatio
        , Qt::SmoothTransformation));
    connect(ui.btnMail, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("mailto:zhu.thatboy@outlook.com")); });
    connect(ui.btnGithub, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("https://github.com/thatboy-echo")); });
    connect(ui.btnWebsite, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("https://thatboy.info")); });
    connect(ui.btnSignature, &QPushButton::clicked, [] {QDesktopServices::openUrl(QUrl("https://thatboy.info")); });
}
