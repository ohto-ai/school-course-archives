#include "PictureProcessX.h"
#include <algorithm>

constexpr size_t MaxGaussKernelSize = 7;
constexpr double GaussKernel[MaxGaussKernelSize][MaxGaussKernelSize * 2 + 1][MaxGaussKernelSize * 2 + 1]{
	{
		 {0.0947, 0.1183, 0.0947}
		,{0.1183, 0.1478, 0.1183}
		,{0.0947, 0.1183, 0.0947}
	}
	,{
		 {0.0144, 0.0281, 0.0351, 0.0281, 0.0144}
		,{0.0281, 0.0547, 0.0683, 0.0547, 0.0281}
		,{0.0351, 0.0683, 0.0853, 0.0683, 0.0351}
		,{0.0281, 0.0547, 0.0683, 0.0547, 0.0281}
		,{0.0144, 0.0281, 0.0351, 0.0281, 0.0144}
	}
	,{
		 {0.0013, 0.0041, 0.0079, 0.0099, 0.0079, 0.0041, 0.0013}
		,{0.0041, 0.0124, 0.0241, 0.0301, 0.0241, 0.0124, 0.0041}
		,{0.0079, 0.0241, 0.0470, 0.0587, 0.0470, 0.0241, 0.0079}
		,{0.0099, 0.0301, 0.0587, 0.0733, 0.0587, 0.0301, 0.0099}
		,{0.0079, 0.0241, 0.0470, 0.0587, 0.0470, 0.0241, 0.0079}
		,{0.0041, 0.0124, 0.0241, 0.0301, 0.0241, 0.0124, 0.0041}
		,{0.0013, 0.0041, 0.0079, 0.0099, 0.0079, 0.0041, 0.0013}
	}
	,{
		 {0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001}
		,{0.0003, 0.0013, 0.0040, 0.0077, 0.0096, 0.0077, 0.0040, 0.0013, 0.0003}
		,{0.0008, 0.0040, 0.0120, 0.0234, 0.0292, 0.0234, 0.0120, 0.0040, 0.0008}
		,{0.0016, 0.0077, 0.0234, 0.0456, 0.0569, 0.0456, 0.0234, 0.0077, 0.0016}
		,{0.0020, 0.0096, 0.0292, 0.0569, 0.0711, 0.0569, 0.0292, 0.0096, 0.0020}
		,{0.0016, 0.0077, 0.0234, 0.0456, 0.0569, 0.0456, 0.0234, 0.0077, 0.0016}
		,{0.0008, 0.0040, 0.0120, 0.0234, 0.0292, 0.0234, 0.0120, 0.0040, 0.0008}
		,{0.0003, 0.0013, 0.0040, 0.0077, 0.0096, 0.0077, 0.0040, 0.0013, 0.0003}
		,{0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001}
	}
	,{
		 {0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000}
		,{0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000}
		,{0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001}
		,{0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0567, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002}
		,{0.0003, 0.0020, 0.0096, 0.0291, 0.0567, 0.0708, 0.0567, 0.0291, 0.0096, 0.0020, 0.0003}
		,{0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0567, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002}
		,{0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001}
		,{0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000}
		,{0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000}
	}
	,{

		 {0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000, 0.0000}
		,{0.0000, 0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001, 0.0000}
		,{0.0000, 0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0566, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002, 0.0000}
		,{0.0000, 0.0003, 0.0020, 0.0096, 0.0291, 0.0566, 0.0707, 0.0566, 0.0291, 0.0096, 0.0020, 0.0003, 0.0000}
		,{0.0000, 0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0566, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002, 0.0000}
		,{0.0000, 0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001, 0.0000}
		,{0.0000, 0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
	}
	,{
		 {0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0566, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0003, 0.0020, 0.0096, 0.0291, 0.0566, 0.0707, 0.0566, 0.0291, 0.0096, 0.0020, 0.0003, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0002, 0.0016, 0.0077, 0.0233, 0.0454, 0.0566, 0.0454, 0.0233, 0.0077, 0.0016, 0.0002, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0001, 0.0008, 0.0039, 0.0120, 0.0233, 0.0291, 0.0233, 0.0120, 0.0039, 0.0008, 0.0001, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0003, 0.0013, 0.0039, 0.0077, 0.0096, 0.0077, 0.0039, 0.0013, 0.0003, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0001, 0.0003, 0.0008, 0.0016, 0.0020, 0.0016, 0.0008, 0.0003, 0.0001, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0001, 0.0002, 0.0003, 0.0002, 0.0001, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
		,{0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
	}
};

PictureProcessX::PictureProcessX(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, [this]
		{
			imageWriteLock.lock();
			ui.imageView->loadDialog();
			oriImage = ui.imageView->image();
			imageWriteLock.unlock();
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
	connect(ui.sliderLight, &QSlider::sliderReleased, [this] {updateImageView(); });

	// 高斯
	ui.spinGauss->setMinimum(1);
	ui.sliderGauss->setMinimum(1);
	ui.spinGauss->setMaximum(MaxGaussKernelSize);
	ui.sliderGauss->setMaximum(MaxGaussKernelSize);
	connect(ui.sliderGauss, &QSlider::valueChanged, ui.spinGauss, &QSpinBox::setValue);
	connect(ui.spinGauss, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.sliderGauss, &QSlider::setValue);
	connect(ui.sliderGauss, &QSlider::valueChanged, [this](int)
		{
			if (!ui.checkLivePreview->isChecked())
				if (ui.sliderGauss->isSliderDown())
					return;
			updateImageView();
		});
	connect(ui.sliderGauss, &QSlider::sliderReleased, [this] {updateImageView(); });

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
	connect(ui.sliderBinarize, &QSlider::sliderReleased, [this] {updateImageView(); });

	// 旋转
	connect(ui.dialRotate, &QDial::valueChanged, ui.spinRotate, &QSpinBox::setValue);
	connect(ui.spinRotate, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.dialRotate, &QDial::setValue);
	connect(ui.dialRotate, &QDial::valueChanged, [this](int)
		{
			//if (!ui.checkLivePreview->isChecked())
			//    if (ui.dialRotate->isSliderDown())
			//        return;
			ui.imageView->rotate() = ui.dialRotate->value();
			update();
			// updateImageView();
		});
	connect(ui.dialRotate, &QDial::sliderReleased, [this]
		{
			ui.imageView->rotate() = ui.dialRotate->value();
			update();
			//updateImageView();
		});

	connect(ui.checkReverseColor, &QCheckBox::clicked, [this](bool) {updateImageView(); });
	connect(ui.checkGray, &QCheckBox::clicked, [this](bool) {updateImageView(); });
	connect(ui.checkBinarize, &QCheckBox::clicked, [this](bool) {updateImageView(); });
	connect(ui.checkLight, &QCheckBox::clicked, [this](bool) {updateImageView(); });
	connect(ui.checkGauss, &QCheckBox::clicked, [this](bool) {updateImageView(); });

	connect(ui.checkBinarize, &QCheckBox::clicked, ui.sliderBinarize, &QWidget::setEnabled);
	connect(ui.checkBinarize, &QCheckBox::clicked, ui.spinBinarize, &QWidget::setEnabled);

	connect(ui.checkLight, &QCheckBox::clicked, ui.sliderLight, &QWidget::setEnabled);
	connect(ui.checkLight, &QCheckBox::clicked, ui.spinLight, &QWidget::setEnabled);

	connect(ui.checkGauss, &QCheckBox::clicked, ui.sliderGauss, &QWidget::setEnabled);
	connect(ui.checkGauss, &QCheckBox::clicked, ui.spinGauss, &QWidget::setEnabled);

	// 旋转
	connect(ui.checkRotate, &QCheckBox::clicked, ui.dialRotate, &QWidget::setEnabled);
	connect(ui.checkRotate, &QCheckBox::clicked, ui.spinRotate, &QWidget::setEnabled);
	connect(ui.checkRotate, &QCheckBox::clicked, [this](bool b)
		{
			ui.imageView->rotate() = b ? ui.dialRotate->value() : 0;
			update();
		});

	connect(ui.checkMirrorHorizontally, &QCheckBox::clicked, ui.imageView, &ImageView::setMirrorHor);
	connect(ui.checkMirrorVertically, &QCheckBox::clicked, ui.imageView, &ImageView::setMirrorVer);
}

void PictureProcessX::gauss()
{
	static std::atomic_int waiting_thread = 0;
	if (++waiting_thread > 1)// 只保留最后一个待完成的线程
	{
		--waiting_thread;
		return;
	}
	auto dstImage{ ui.imageView->image() };
	auto srcImage{ ui.imageView->image() };
	auto dstBits = dstImage.bits();
	auto srcBits = srcImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;

	auto& kernel = GaussKernel[ui.sliderGauss->value() - 1];
	int sizeKernel = ui.sliderGauss->value() * 2 + 1;

	for (int x = sizeKernel / 2; x < dstImage.width() - sizeKernel / 2; x++)
	{
		for (int y = sizeKernel / 2; y < dstImage.height() - sizeKernel / 2; y++)
		{
			double r = 0;
			double g = 0;
			double b = 0;
			for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
			{
				for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
				{
					auto thisPixel = srcBits + (y + j) * bytePerLine + (x + i) * pxByte;
					r += thisPixel[2] * kernel[sizeKernel / 2 + i][sizeKernel / 2 + j];
					g += thisPixel[1] * kernel[sizeKernel / 2 + i][sizeKernel / 2 + j];
					b += thisPixel[0] * kernel[sizeKernel / 2 + i][sizeKernel / 2 + j];
				}
			}
			auto thisPixel = dstBits + y * bytePerLine + x * pxByte;
			if (r > 255)
				thisPixel[2] = 255;
			else if (r < 0)
				thisPixel[2] = 0;
			else
				thisPixel[2] = r;
			if (g > 255)
				thisPixel[1] = 255;
			else if (g < 0)
				thisPixel[1] = 0;
			else
				thisPixel[1] = g;
			if (b > 255)
				thisPixel[0] = 255;
			else if (b < 0)
				thisPixel[0] = 0;
			else
				thisPixel[0] = b;
		}
	}

	imageWriteLock.lock();
	memcpy(ui.imageView->image().bits(), dstImage.bits(), dstImage.byteCount());
	imageWriteLock.unlock();

	--waiting_thread;
	update();
}

void PictureProcessX::light()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	auto srcBits = oriImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;

	float light = (ui.sliderLight->value() - ui.sliderLight->minimum()) / 100.0;
	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			auto thisPix = dstBits + i * bytePerLine + j * pxByte;
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

	update();
}

void PictureProcessX::reverseColor()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	auto srcBits = oriImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;

	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			auto thisPix = dstBits + i * bytePerLine + j * pxByte;
			thisPix[0] = ~thisPix[0];
			thisPix[1] = ~thisPix[1];
			thisPix[2] = ~thisPix[2];
		}
	}
	update();
}

void PictureProcessX::gray()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	auto srcBits = oriImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;		
	
	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			auto thisPix = dstBits + i * bytePerLine + j * pxByte;
			thisPix[0] = thisPix[1] = thisPix[2] = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
		}
	}
	update();
}

void PictureProcessX::binarize()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	auto srcBits = oriImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;

	int threshold = ui.sliderBinarize->value();
	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			auto thisPix = dstBits + i * bytePerLine + j * pxByte;
			auto gray = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
			if (gray > 255)gray = 255;
			gray = gray >= threshold ? 255 : 0;
			thisPix[0] = thisPix[1] = thisPix[2] = gray;
		}
	}
	update();
}

void PictureProcessX::updateImageView()
{
	auto& dstImage = ui.imageView->image();
	if (dstImage.isNull())
		return;
	if (dstImage.depth() != 24 && dstImage.depth() != 32 && dstImage.depth() != 8)
		return;

	imageWriteLock.lock();
	memcpy(dstImage.bits(), oriImage.bits(), oriImage.byteCount());
	imageWriteLock.unlock();


	// 亮度
	if (ui.checkLight->isChecked())
		light();

	// 高斯模糊
	if (ui.checkGauss->isChecked())
	{
		std::thread th(&PictureProcessX::gauss, this);
		th.detach();
	}

	// 反色
	if (ui.checkReverseColor->isChecked())
		reverseColor();

	// 灰度
	if (ui.checkGray->isChecked())
		gray();

	// 二值化
	if (ui.checkBinarize->isChecked())
		binarize();

	update();
}