#include "PictureProcessX.h"
#include <algorithm>

PictureProcessX::PictureProcessX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionOpen, &QAction::triggered, [this]
        {
            ui.imageView->loadDialog();
            oriImage = ui.imageView->image();
            updateImageView();
        }
    );

    // 亮度
    connect(ui.sliderLight, &QSlider::valueChanged, ui.spinLight, &QSpinBox::setValue);
    connect(ui.spinLight, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.sliderLight, &QSlider::setValue);
    connect(ui.sliderLight, &QSlider::valueChanged, [this](int) 
        {
            if (!ui.checkLivePreview->isChecked())
                if (ui.sliderLight->isSliderDown())
                    return;
            updateImageView(); 
        });
    connect(ui.sliderLight, &QSlider::sliderReleased, [this]
        {
            updateImageView();
        });

    // 二值化
    connect(ui.sliderBinarize, &QSlider::valueChanged, ui.spinBinarize, &QSpinBox::setValue);
    connect(ui.spinBinarize, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.sliderBinarize, &QSlider::setValue);
    connect(ui.sliderBinarize, &QSlider::valueChanged, [this](int)
        {
            if (!ui.checkLivePreview->isChecked())
                if (ui.sliderBinarize->isSliderDown())
                    return;
            updateImageView();
        });
    connect(ui.sliderBinarize, &QSlider::sliderReleased, [this]
        {
            updateImageView();
        });

    // 反相
    connect(ui.checkReverseColor, &QCheckBox::clicked, [this](bool) {updateImageView(); });
    // 灰度
    connect(ui.checkGray, &QCheckBox::clicked, [this](bool) {updateImageView(); });
    connect(ui.checkBinarize, &QCheckBox::clicked, [this](bool) {updateImageView(); });
    connect(ui.checkLight, &QCheckBox::clicked, [this](bool) {updateImageView(); });


    connect(ui.checkBinarize, &QCheckBox::clicked, ui.sliderBinarize, &QWidget::setEnabled);
    connect(ui.checkBinarize, &QCheckBox::clicked, ui.spinBinarize, &QWidget::setEnabled);

    connect(ui.checkLight, &QCheckBox::clicked, ui.sliderLight, &QWidget::setEnabled);
    connect(ui.checkLight, &QCheckBox::clicked, ui.spinLight, &QWidget::setEnabled);

    connect(ui.checkGauss, &QCheckBox::clicked, ui.sliderGauss, &QWidget::setEnabled);
    connect(ui.checkGauss, &QCheckBox::clicked, ui.spinGauss, &QWidget::setEnabled);
}

void PictureProcessX::updateImageView()
{
    ui.imageView->image() = oriImage;
    auto& img = ui.imageView->image();
    auto imageBits = img.bits();
    int bytePerLine = img.bytesPerLine();
    int pxByte = img.depth() / 8;
    if (img.isNull())
        return;
    if (img.depth() != 24 && img.depth() != 32 && img.depth() != 8)
        return;

    // 亮度
    if (ui.checkLight->isChecked())
    {
        float light = (ui.sliderLight->value() - ui.sliderLight->minimum()) / 100.0;
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                auto thisPix = imageBits + i * bytePerLine + j * pxByte;
                auto b = thisPix[0] * light;
                auto g = thisPix[1] * light;
                auto r = thisPix[2] * light;
                if (b > 255)b = 255;
                if (g > 255)g = 255;
                if (r > 255)r = 255;
                thisPix[0] = b;
                thisPix[1] = g;
                thisPix[2] = r;
            }
        }
    }

    // 反色
    if (ui.checkReverseColor->isChecked())
    {
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                auto thisPix = imageBits + i * bytePerLine + j * pxByte;
                thisPix[0] = ~thisPix[0];
                thisPix[1] = ~thisPix[1];
                thisPix[2] = ~thisPix[2];
            }
        }
    }

    // 灰度
    if (ui.checkGray->isChecked())
    {
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                auto thisPix = imageBits + i * bytePerLine + j * pxByte;
                thisPix[0] = thisPix[1] = thisPix[2] = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
            }
        }
    }

    // 二值化
    if (ui.checkBinarize->isChecked())
    {
        int threshold = ui.sliderBinarize->value();
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                auto thisPix = imageBits + i * bytePerLine + j * pxByte;
                auto gray = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
                if (gray > 255)gray = 255;
                gray = gray >= threshold ? 255 : 0;
                thisPix[0] = thisPix[1] = thisPix[2] = gray;
            }
        }
    }

    // 直方图
    if (ui.checkHist->isChecked())
    {
        int hist[256] = { 0 };

        // 统计
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                auto thisPix = imageBits + i * bytePerLine + j * pxByte;
                auto gray = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
                if (gray > 255)gray = 255;
                hist[gray]++;
            }
        }

        // 
        int maxHist = *std::max_element(hist, hist + 256);
        QImage histImage(256, maxHist, QImage::Format::Format_ARGB32);

    }


    update();
}
