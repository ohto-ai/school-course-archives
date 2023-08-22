#include "CameraX.h"
#include <QListWidgetItem>

Q_DECLARE_METATYPE(QCameraInfo)
CameraX::CameraX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // 添加设备列表
    QActionGroup* videoDevicesGroup = new QActionGroup(this);
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
    connect(ui.btnCaputre, &QPushButton::clicked, [this] {imageCapture->capture(); });
}

void CameraX::setCamera(const QCameraInfo& cameraInfo)
{
    auto deviceDescription = cameraInfo.description();
    delete camera;
    delete imageCapture;
    camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(camera);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(viewfinder);

    connect(imageCapture, &QCameraImageCapture::imageCaptured, [this, deviceDescription](int id, const QImage& img)
        {
            QListWidgetItem* pItem = new QListWidgetItem(QIcon(QPixmap::fromImage(img).scaled(QSize(200, 160)))
                , QString::asprintf("%s_%08d", deviceDescription.toStdString().c_str(), id));
            ui.listImage->insertItem(ui.listImage->count(), pItem);
        });

}
void CameraX::start()
{
    camera->start();
}
void CameraX::stop()
{
    camera->stop();
}
void CameraX::changeCameraDevice(QAction* action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
    camera->start();
}