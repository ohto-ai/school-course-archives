#pragma once

#include <QtWidgets/QMainWindow>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVariant>
#include <QMediaRecorder>
#include "ui_CameraX.h"

class CameraX : public QMainWindow
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
    friend class MultiMidiaSystem;

private slots:

    void setCamera(const QCameraInfo& cameraInfo);
    void changeCameraDevice(QAction* action);
};
