#include "CameraX.h"

Q_DECLARE_METATYPE(QCameraInfo)
CameraX::CameraX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QActionGroup* videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    QList<QCameraInfo>cameras = QCameraInfo::availableCameras();
  
    for (const auto& cameraInfo : cameras)
    {
        auto videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);
        ui.menuDevice->addAction(videoDeviceAction);
    }
    viewfinder = new QCameraViewfinder(this);
    ui.layoutCamera->addWidget(viewfinder);
    connect(videoDevicesGroup, &QActionGroup::triggered, this, &CameraX::changeCameraDevice);
    setCamera(QCameraInfo::defaultCamera());
}

void CameraX::setCamera(const QCameraInfo& cameraInfo)
{
    delete camera;
    delete imageCapture;
    camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(camera);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(viewfinder);
    camera->start();//Æô¶¯ÉãÏñÍ·
}
void CameraX::changeCameraDevice(QAction* action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}