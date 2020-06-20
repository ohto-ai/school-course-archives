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
    QCamera* camera{ nullptr };
    /* ��ͼ���� */
    QCameraImageCapture* imageCapture{ nullptr };
    /* ����ͷȡ�������� */
    QCameraViewfinder* viewfinder{ nullptr };
    friend class MultiMediaSystem;

public:
    void start();
    void stop();
private slots:

    void setCamera(const QCameraInfo& cameraInfo);
    void changeCameraDevice(QAction* action);
};
