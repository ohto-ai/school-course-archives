#pragma once

#include <QtWidgets/QDialog>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVariant>
#include <QMediaRecorder>
#include "ui_CameraX.h"

class CameraX : public QDialog
{
    Q_OBJECT

public:
    CameraX(QWidget *parent = Q_NULLPTR);

private:
    Ui::CameraXClass ui;
    /* 摄像头设备 */
    QCamera* camera;
    /* 截图部件 */
    QCameraImageCapture* imageCapture;
    /* 摄像头取景器部件 */
    QCameraViewfinder* viewfinder;

private slots:

    void setCamera(const QCameraInfo& cameraInfo);
    void changeCameraDevice(QAction* action);
};
