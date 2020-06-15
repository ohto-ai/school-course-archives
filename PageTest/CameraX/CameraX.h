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
    /* ����ͷ�豸 */
    QCamera* camera;
    /* ��ͼ���� */
    QCameraImageCapture* imageCapture;
    /* ����ͷȡ�������� */
    QCameraViewfinder* viewfinder;

private slots:

    void setCamera(const QCameraInfo& cameraInfo);
    void changeCameraDevice(QAction* action);
};
