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

	// 打开图片
	connect(ui.btnOpen, &QPushButton::clicked, [this]
		{
			imageWriteLock.lock();
			if(ui.imageView->loadDialog())
				oriImage = ui.imageView->image();
			imageWriteLock.unlock();
			updateImageView();
		}
	);
	connect(ui.btnSave, &QPushButton::clicked, ui.imageView, &ImageView::saveDialog);

	// 按钮更新
	connect(ui.checkReverseColor, &QCheckBox::toggled, [this](bool) {updateImageView(); });
	connect(ui.checkGray, &QCheckBox::toggled, [this](bool) {updateImageView(); });
	connect(ui.radioNostalgic, &QCheckBox::toggled, [this](bool) {updateImageView(); });
	connect(ui.radioBlackWhiteComics, &QCheckBox::toggled, [this](bool) {updateImageView(); });
	connect(ui.radioExposure, &QCheckBox::toggled, [this](bool) {updateImageView(); });

	// Slider Radio SpinBox 状态同步宏
#define SLIDER_RADIO_SPIN_SYNCHRO(NAME, MIN, MAX) \
	connect(ui.radio##NAME, &QRadioButton::toggled, [this](bool b) { ui.slider##NAME->setEnabled(b); ui.spin##NAME->setEnabled(b); updateImageView(); });\
	ui.spin##NAME->setMinimum(MIN);\
	ui.slider##NAME->setMinimum(MIN);\
	ui.spin##NAME->setMaximum(MAX);\
	ui.slider##NAME->setMaximum(MAX);\
	connect(ui.slider##NAME, &QSlider::valueChanged, ui.spin##NAME, &QSpinBox::setValue);\
	connect(ui.spin##NAME, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.slider##NAME, &QSlider::setValue);\
	connect(ui.slider##NAME, &QSlider::valueChanged, [this](int)\
		{\
			if (!ui.checkLivePreview->isChecked())\
				if (ui.slider##NAME->isSliderDown())\
					return;\
			updateImageView();\
		});\
	connect(ui.slider##NAME, &QDial::sliderReleased, [this]\
		{\
			updateImageView(); \
		});

	SLIDER_RADIO_SPIN_SYNCHRO(Light, 0, 500);					// 亮度
	SLIDER_RADIO_SPIN_SYNCHRO(Binarize, 0, 256);				// 二值化
	SLIDER_RADIO_SPIN_SYNCHRO(Mosaic, 0, 80);					// 马赛克
	SLIDER_RADIO_SPIN_SYNCHRO(Emboss, 1, 40);					// 浮雕
	SLIDER_RADIO_SPIN_SYNCHRO(Neon, 1, 40);						// 霓虹
	SLIDER_RADIO_SPIN_SYNCHRO(Gauss, 1, MaxGaussKernelSize);	// 高斯模糊
	SLIDER_RADIO_SPIN_SYNCHRO(Diffuse, 1, 40);					// 扩散

#undef SLIDER_RADIO_SPIN_SYNCHRO


	// 旋转
	connect(ui.spinRotate, static_cast<void(QSpinBox ::*)(int)>(&QSpinBox::valueChanged), ui.dialRotate, &QDial::setValue);
	connect(ui.dialRotate, &QDial::valueChanged, [this](int value)
		{
			ui.spinRotate->setValue(value);
			ui.imageView->rotate() = value;
			update();
		});
	connect(ui.dialRotate, &QDial::sliderReleased, [this]
		{
			ui.imageView->rotate() = ui.dialRotate->value();
			update();
		});
	connect(ui.checkRotate, &QCheckBox::toggled, [this](bool b)
		{
			ui.dialRotate->setEnabled(b);
			ui.spinRotate->setEnabled(b);
			ui.imageView->rotate() = b ? ui.dialRotate->value() : 0;
			update();
		});
	// 镜像
	connect(ui.checkMirrorHorizontally, &QCheckBox::toggled, ui.imageView, &ImageView::setMirrorHor);
	connect(ui.checkMirrorVertically, &QCheckBox::toggled, ui.imageView, &ImageView::setMirrorVer);
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
			thisPixel[2] = qBound<int>(0, r, 255);
			thisPixel[1] = qBound<int>(0, g, 255);
			thisPixel[0] = qBound<int>(0, b, 255);
		}
	}

	imageWriteLock.lock();
	memcpy(ui.imageView->image().bits(), dstImage.bits(), dstImage.byteCount());
	imageWriteLock.unlock();

	--waiting_thread;
	update();
}

void PictureProcessX::exposure()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		if (thisPix[0] > 128)
			thisPix[0] = ~thisPix[0];
		if (thisPix[1] > 128)
			thisPix[1] = ~thisPix[1];
		if (thisPix[2] > 128)
			thisPix[2] = ~thisPix[2];
	}
	update();
}

void PictureProcessX::diffuse()
{
	auto dstImage{ ui.imageView->image() };
	auto& srcImage{ ui.imageView->image() };
	auto dstBits = dstImage.bits();
	auto srcBits = srcImage.constBits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;
	int degree = ui.sliderDiffuse->value();
	int R, G, B;

	for (size_t i = 0; i < dstImage.height(); i++)
	{
		size_t x{ qBound<size_t>(0, i + rand() % degree - (degree >> 1), dstImage.height() - 1) };
		for (size_t j = 0; j < dstImage.width(); j++)
		{
			size_t y{ qBound<size_t>(0, j + rand() % degree - (degree >> 1), dstImage.width() - 1) };
			auto thisPix = dstBits + i * bytePerLine + j * pxByte;
			auto thatPix = srcBits + x * bytePerLine + y * pxByte;
			thisPix[0] = thatPix[0];
			thisPix[1] = thatPix[1];
			thisPix[2] = thatPix[2];
		}
	}

	imageWriteLock.lock();
	memcpy(ui.imageView->image().bits(), dstImage.bits(), dstImage.byteCount());
	imageWriteLock.unlock();
	update();
}

void PictureProcessX::nostalgic()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		QRgb& thisRgb = *reinterpret_cast<QRgb*>(thisPix);
		uchar r = qRed(thisRgb);
		uchar g = qGreen(thisRgb);
		uchar b = qBlue(thisRgb);
		thisRgb = qRgb(
			qBound<int>(0, r * 0.393 + g * 0.769 + g * 0.189, 255)
			, qBound<int>(0, r * 0.349 + g * 0.686 + g * 0.168, 255)
			, qBound<int>(0, r * 0.272 + g * 0.534 + g * 0.131, 255)
		);
	}
	
	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			QRgb& thisPix = *reinterpret_cast<QRgb*>(dstBits + i * bytePerLine + j * pxByte);
			uchar r = qRed(thisPix);
			uchar g = qGreen(thisPix);
			uchar b = qBlue(thisPix);
			thisPix = qRgb(
				qBound<int>(0, r * 0.393 + g * 0.769 + g * 0.189, 255)
				, qBound<int>(0, r * 0.349 + g * 0.686 + g * 0.168, 255)
				, qBound<int>(0, r * 0.272 + g * 0.534 + g * 0.131, 255)
			);
		}
	}
	update();
}

void PictureProcessX::blackWhiteComics()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		auto gray = abs((thisPix[1] * 2) - thisPix[0] + thisPix[2]) * thisPix[2] >> 8;
		thisPix[2] = thisPix[1] = qBound(0, gray + 10, 255);
		thisPix[0] = qBound(0, gray, 255);
	}
	update();
}

void PictureProcessX::light()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;
	float light = (ui.sliderLight->value() - ui.sliderLight->minimum()) / 100.0;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		thisPix[0] = qBound<int>(0, thisPix[0] * light, 255);
		thisPix[1] = qBound<int>(0, thisPix[1] * light, 255);
		thisPix[2] = qBound<int>(0, thisPix[2] * light, 255);
	}
	update();
}

void PictureProcessX::reverseColor()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		thisPix[0] = ~thisPix[0];
		thisPix[1] = ~thisPix[1];
		thisPix[2] = ~thisPix[2];
	}
	update();
}

void PictureProcessX::gray()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		thisPix[0] = thisPix[1] = thisPix[2] = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
	}
	update();
}

void PictureProcessX::binarize()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage = ui.imageView->image();
	auto dstBits = dstImage.bits();
	int bytePerLine = dstImage.bytesPerLine();
	auto dstBitsEnd = dstImage.bits() + dstImage.byteCount();
	int pxByte = dstImage.depth() / 8;
	int threshold = ui.sliderBinarize->value();

	for (auto thisPix = dstBits; thisPix < dstBitsEnd; thisPix += pxByte)
	{
		auto gray = (thisPix[2] * 30 + thisPix[1] * 59 + thisPix[0] * 11) / 100;
		if (gray > 255)gray = 255;
		gray = gray >= threshold ? 255 : 0;
		thisPix[0] = thisPix[1] = thisPix[2] = gray;
	}
	update();
}

void PictureProcessX::mosaic()
{
	std::lock_guard<std::mutex> lock(imageWriteLock);

	auto& dstImage{ ui.imageView->image() };
	auto& srcImage{ ui.imageView->image() };
	auto dstBits = dstImage.bits();
	auto srcBits = srcImage.constBits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;
	int degree = ui.sliderMosaic->value();

	if (degree <= 1)
		return;
	ulong MosaicValueR, MosaicValueG, MosaicValueB;

	for (int i = 0; i < dstImage.height() / degree; i++)
	{
		for (int j = 0; j < dstImage.width() / degree; j++)
		{
			MosaicValueR = MosaicValueG = MosaicValueB = 0;
			for (int y = i * degree; y < (i + 1) * degree; y++)
			{
				for (int x = j * degree; x < (j + 1) * degree; x++)
				{
					auto thisPix = srcBits + y * bytePerLine + x * pxByte;
					MosaicValueR += thisPix[2];
					MosaicValueG += thisPix[1];
					MosaicValueB += thisPix[0];
				}
			}
			MosaicValueR /= degree * degree;
			MosaicValueG /= degree * degree;
			MosaicValueB /= degree * degree;
			for (int y = i * degree; y < (i + 1) * degree; y++)
			{
				for (int x = j * degree; x < (j + 1) * degree; x++)
				{
					auto thisPix = dstBits + y * bytePerLine + x * pxByte;
					thisPix[2] = MosaicValueR;
					thisPix[1] = MosaicValueG;
					thisPix[0] = MosaicValueB;
				}
			}
		}
	}
	int height = dstImage.height() % degree;
	int width = dstImage.width() % degree;

	if (height > 0)
	{
		for (int j = 0; j < dstImage.width() / degree; j++)
		{
			MosaicValueR = MosaicValueG = MosaicValueB = 0;
			for (int y = dstImage.height() - height ; y < dstImage.height(); y++)
			{
				for (int x = j * degree; x < (j + 1) * degree; x++)
				{
					auto thisPix = srcBits + y * bytePerLine + x * pxByte;
					MosaicValueR += thisPix[2];
					MosaicValueG += thisPix[1];
					MosaicValueB += thisPix[0];
				}
			}
			MosaicValueR /= degree * height;
			MosaicValueG /= degree * height;
			MosaicValueB /= degree * height;
			for (int y = dstImage.height() - height; y < dstImage.height(); y++)
			{
				for (int x = j * degree; x < (j + 1) * degree; x++)
				{
					auto thisPix = dstBits + y * bytePerLine + x * pxByte;
					thisPix[2] = MosaicValueR;
					thisPix[1] = MosaicValueG;
					thisPix[0] = MosaicValueB;
				}
			}
		}
	}
	if (width > 0)//横向未完成
	{
		for (int i = 0; i < dstImage.height() / degree; i++)
		{
			MosaicValueR = MosaicValueG = MosaicValueB = 0;
			for (int x = dstImage.width() - width; x < dstImage.width(); x++)
			{
				for (int y = i * degree; y < (i + 1) * degree; y++)
				{
					auto thisPix = srcBits + y * bytePerLine + x * pxByte;
					MosaicValueR += thisPix[2];
					MosaicValueG += thisPix[1];
					MosaicValueB += thisPix[0];
				}
			}
			MosaicValueR /= degree * width;
			MosaicValueG /= degree * width;
			MosaicValueB /= degree * width;
			for (int x = dstImage.width() - width; x < dstImage.width(); x++)
			{
				for (int y = i * degree; y < (i + 1) * degree; y++)
				{
					auto thisPix = dstBits + y * bytePerLine + x * pxByte;
					thisPix[2] = MosaicValueR;
					thisPix[1] = MosaicValueG;
					thisPix[0] = MosaicValueB;
				}
			}
		}
	}
	if (height > 0 && width > 0)
	{
		for (int x = dstImage.width() - width; x < dstImage.width(); x++)
		{
			for (int y = dstImage.height() - height; y < dstImage.height(); y++)
			{
				auto thisPix = srcBits + y * bytePerLine + x * pxByte;
				MosaicValueR += thisPix[2];
				MosaicValueG += thisPix[1];
				MosaicValueB += thisPix[0];
			}
		}
		MosaicValueR /= width * height;
		MosaicValueG /= width * height;
		MosaicValueB /= width * height;
		for (int x = dstImage.width() - width; x < dstImage.width(); x++)
		{
			for (int y = dstImage.height() - height; y < dstImage.height(); y++)
			{
				auto thisPix = dstBits + y * bytePerLine + x * pxByte;
				thisPix[2] = MosaicValueR;
				thisPix[1] = MosaicValueG;
				thisPix[0] = MosaicValueB;
			}
		}
	}
	update();
}

void PictureProcessX::emboss()
{
	auto dstImage{ ui.imageView->image() };
	auto &srcImage{ ui.imageView->image() };
	auto dstBits = dstImage.bits();
	auto srcBits = srcImage.constBits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;
	int degree = ui.sliderEmboss->value();
	int R, G, B;
	for (int i = 0; i < dstImage.height(); i++)
	{
		for (int j = 0; j < dstImage.width(); j++)
		{
			auto thisPix = srcBits + i * bytePerLine + j * pxByte;
			auto thatPix = srcBits + (i + degree) % dstImage.height() * bytePerLine+ (j + degree) % dstImage.width() * pxByte;
			R = thisPix[2] - thatPix[2] + 128;
			G = thisPix[1] - thatPix[1] + 128;
			B = thisPix[0] - thatPix[0] + 128;
			auto thisDstPix = dstBits + i * bytePerLine + j * pxByte;
			thisDstPix[0] = qBound(0, B, 255);
			thisDstPix[1] = qBound(0, G, 255);
			thisDstPix[2] = qBound(0, R, 255);
		}
	}
	imageWriteLock.lock();
	memcpy(ui.imageView->image().bits(), dstImage.bits(), dstImage.byteCount());
	imageWriteLock.unlock();
	update();
}

void PictureProcessX::neon()
{
	auto dstImage{ ui.imageView->image() };
	auto& srcImage{ ui.imageView->image() };
	auto dstBits = dstImage.bits();
	auto srcBits = srcImage.constBits();
	int bytePerLine = dstImage.bytesPerLine();
	int pxByte = dstImage.depth() / 8;
	int degree = ui.sliderNeon->value();
	int R, G, B;
	for (int i = 0; i < dstImage.height() - 1; i++)
	{
		for (int j = 0; j < dstImage.width() - 1; j++)
		{
			auto thisPix = srcBits + i * bytePerLine + j * pxByte;
			auto thisRightPix = srcBits + i * bytePerLine + (j + 1) * pxByte;
			auto thisBottomPix = srcBits + (i + 1) * bytePerLine + j * pxByte;
			R = degree * sqrt((thisPix[2] - thisRightPix[2]) * (thisPix[2] - thisRightPix[2])
				+ (thisPix[2] - thisBottomPix[2]) * (thisPix[2] - thisBottomPix[2]));

			G = degree * sqrt((thisPix[1] - thisRightPix[1]) * (thisPix[1] - thisRightPix[1])
				+ (thisPix[1] - thisBottomPix[1]) * (thisPix[1] - thisBottomPix[1]));

			B = degree * sqrt((thisPix[0] - thisRightPix[0]) * (thisPix[0] - thisRightPix[0])
				+ (thisPix[0] - thisBottomPix[0]) * (thisPix[0] - thisBottomPix[0]));

			if (R > 255)R = 255;
			if (G > 255)G = 255;
			if (B > 255)B = 255;
			auto thisDstPix = dstBits + i * bytePerLine + j * pxByte;
			thisDstPix[0] = B;
			thisDstPix[1] = G;
			thisDstPix[2] = R;
		}
	}
	imageWriteLock.lock();
	memcpy(ui.imageView->image().bits(), dstImage.bits(), dstImage.byteCount());
	imageWriteLock.unlock();
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
	if (ui.radioLight->isChecked())
		light();
	else if (ui.radioBinarize->isChecked())
		binarize();
	else if (ui.radioMosaic->isChecked())
		mosaic();
	else if (ui.radioEmboss->isChecked())
		emboss();
	else if (ui.radioNeon->isChecked())
		neon();
	else if (ui.radioGauss->isChecked())
	{
		std::thread th(&PictureProcessX::gauss, this);
		th.detach();
	}
	else if (ui.radioExposure->isChecked())
		exposure();
	else if (ui.radioDiffuse->isChecked())
		diffuse();
	else if (ui.radioNostalgic->isChecked())
		nostalgic();
	else if (ui.radioBlackWhiteComics->isChecked())
		blackWhiteComics();

	// 反色
	if (ui.checkReverseColor->isChecked())
		reverseColor();
	// 灰度
	if (ui.checkGray->isChecked())
		gray();
	update();
}