#pragma once
#ifndef EASYX_SHARP_H
#define EASYX_SHARP_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <vector>
#include <easyx.h>

#define _EASYX_FUN_DEPRECATED \
_declspec(deprecated("此函数可能已弃用。请考虑改用其他函数。若要禁用弃用，请使用 _USE_EASYXSHARP_DEPRECATED_FUNCTION"))


namespace EasyXSharp
{
	using PIMAGE = IMAGE * ;
	using PCOLORREF = COLORREF * ;

	// 位操作
	namespace BinOperator
	{		
		// 叠加
		IMAGE & operator += (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(DstBuff[i]);
				BYTE g1 = GetGValue(DstBuff[i]);
				BYTE b1 = GetBValue(DstBuff[i]);

				BYTE r2 = GetRValue(SrcBuff[i]);
				BYTE g2 = GetGValue(SrcBuff[i]);
				BYTE b2 = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r1 + r2 > 255 ? 255 : r1 + r2,
					g1 + g2 > 255 ? 255 : g1 + g2,
					b1 + b2 > 255 ? 255 : b1 + b2
				);
			}
			return img1;
		}
		// 相减
		IMAGE & operator -= (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(DstBuff[i]);
				BYTE g1 = GetGValue(DstBuff[i]);
				BYTE b1 = GetBValue(DstBuff[i]);

				BYTE r2 = GetRValue(SrcBuff[i]);
				BYTE g2 = GetGValue(SrcBuff[i]);
				BYTE b2 = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r1 - r2 > 0 ? r1 - r2 : 0,
					g1 - g2 > 0 ? g1 - g2 : 0,
					b1 - b2 > 0 ? b1 - b2 : 0
				);
			}
			return img1;
		}
		// 异或
		IMAGE & operator ^= (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth() * img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] ^= SrcBuff[i];
			}
			return img1;
		}
		// 相与
		IMAGE & operator &= (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth() * img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] &= SrcBuff[i];
			}
			return img1;
		}
		// 相或
		IMAGE & operator |= (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth() * img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] |= SrcBuff[i];
			}
			return img1;
		}

		IMAGE & operator += (IMAGE & img, COLORREF val)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			BYTE r2 = GetRValue(val);
			BYTE g2 = GetGValue(val);
			BYTE b2 = GetBValue(val);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(Buff[i]);
				BYTE g1 = GetGValue(Buff[i]);
				BYTE b1 = GetBValue(Buff[i]);

				Buff[i] = RGB(
					r1 + r2 > 255 ? 255 : r1 + r2,
					g1 + g2 > 255 ? 255 : g1 + g2,
					b1 + b2 > 255 ? 255 : b1 + b2
				);
			}
			return img;
		}
		IMAGE & operator -= (IMAGE & img, COLORREF val)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			BYTE r2 = GetRValue(val);
			BYTE g2 = GetGValue(val);
			BYTE b2 = GetBValue(val);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(Buff[i]);
				BYTE g1 = GetGValue(Buff[i]);
				BYTE b1 = GetBValue(Buff[i]);

				Buff[i] = RGB(
					r1 - r2 > 0 ? r1 - r2 : 0,
					g1 - g2 > 0 ? g1 - g2 : 0,
					b1 - b2 > 0 ? b1 - b2 : 0
				);
			}
			return img;
		}
		IMAGE & operator ^= (IMAGE & img, COLORREF val)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] ^= val;
			}
			return img;
		}
		IMAGE & operator &= (IMAGE & img, COLORREF val)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] &= val;
			}
			return img;
		}
		IMAGE & operator |= (IMAGE & img, COLORREF val)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] |= val;
			}
			return img;
		}

		// 取反
		IMAGE & operator ~	(IMAGE & img)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] = ~Buff[i];
			}
			return img;
		}

		// 保留大值
		IMAGE & ReserveUpper (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(DstBuff[i]);
				BYTE g1 = GetGValue(DstBuff[i]);
				BYTE b1 = GetBValue(DstBuff[i]);

				BYTE r2 = GetRValue(SrcBuff[i]);
				BYTE g2 = GetGValue(SrcBuff[i]);
				BYTE b2 = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r1 > r2 ? r1 : r2,
					g1 > g2 ? g1 : g2,
					b1 > b2 ? b1 : b2
				);
			}
			return img1;
		}
		// 保留大值
		IMAGE & ReserveLower (IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(DstBuff[i]);
				BYTE g1 = GetGValue(DstBuff[i]);
				BYTE b1 = GetBValue(DstBuff[i]);

				BYTE r2 = GetRValue(SrcBuff[i]);
				BYTE g2 = GetGValue(SrcBuff[i]);
				BYTE b2 = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r1 < r2 ? r1 : r2,
					g1 < g2 ? g1 : g2,
					b1 < b2 ? b1 : b2
				);
			}
			return img1;
		}		// 差异
		// 差异
		IMAGE & Difference(IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r1 = GetRValue(DstBuff[i]);
				BYTE g1 = GetGValue(DstBuff[i]);
				BYTE b1 = GetBValue(DstBuff[i]);

				BYTE r2 = GetRValue(SrcBuff[i]);
				BYTE g2 = GetGValue(SrcBuff[i]);
				BYTE b2 = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r1 > r2 ? r1 - r2 : r2 - r1,
					g1 > g2 ? g1 - g2 : g2 - g1,
					b1 > b2 ? b1 - b2 : b2 - b1
				);
			}
			return img1;
		}
		// 二值化差异
		IMAGE & DifferenceBinarization(IMAGE & img1, IMAGE & img2)
		{
			if (img1.getwidth() != img2.getwidth() || img1.getheight() != img2.getheight())
				return img1;
			size_t BuffSize = img1.getwidth()*img1.getheight();
			PCOLORREF DstBuff = GetImageBuffer(&img1);
			PCOLORREF SrcBuff = GetImageBuffer(&img2);
			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] = ((DstBuff[i] & 0XFFFFFF) == (SrcBuff[i] & 0XFFFFFF)) ? WHITE : BLACK;
			}
			return img1;
		}

	}

	// 图像操作
	namespace ImageOperator
	{
		enum ColorChannel :COLORREF
		{
			R_Channel = 0XFF0000,
			G_Channel = 0X00FF00,
			B_Channel = 0X0000FF,

			A_Channel = 0XFF000000,

			R_Channel_BGR = 0X0000FF,	// 内存中
			G_Channel_BGR = 0X00FF00,	// 内存中
			B_Channel_BGR = 0XFF0000,	// 内存中

			RGB_Channel = 0XFFFFFF,
			RGBA_Channel = 0XFFFFFFFF
		};
		BYTE GetGrayValue(COLORREF col)
		{
			// Gray = (R*38 + G*75 + B*15) >> 7
			return BYTE((GetRValue(col) * 38 + GetGValue(col) * 75 + GetBValue(col) * 15) >> 7);
		}
		COLORREF Gray(COLORREF col)
		{
			BYTE gray = GetGrayValue(col);
			return RGB(gray, gray, gray);
		}
		BYTE GetGrayValue_BGR(COLORREF col)
		{
			// Gray = (R*38 + G*75 + B*15) >> 7
			return BYTE((GetBValue(col) * 38 + GetGValue(col) * 75 + GetRValue(col) * 15) >> 7);
		}
		COLORREF Gray_BGR(COLORREF col)
		{
			BYTE gray = GetGrayValue_BGR(col);
			return RGB(gray, gray, gray);
		}

		IMAGE & ReplaceColor(IMAGE & Image, COLORREF SrcCol, COLORREF DstCol,BYTE GrayTolerance)
		{
			BYTE SrcMaxGrayValue, SrcMinGrayValue;
			size_t BuffSize = Image.getwidth() * Image.getheight();
			PCOLORREF ImgBuff = GetImageBuffer(&Image);

			DstCol = BGR(DstCol);
			SrcMaxGrayValue = SrcMinGrayValue = GetGrayValue(SrcCol);

			SrcMaxGrayValue = SrcMaxGrayValue + GrayTolerance > 255 ? 255 : SrcMaxGrayValue + GrayTolerance;
			SrcMinGrayValue = SrcMaxGrayValue - GrayTolerance < 0 ? 0 : SrcMaxGrayValue - GrayTolerance;

			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE GrayVal = GetGrayValue(ImgBuff[i]);
				if (GrayVal >= SrcMinGrayValue && GrayVal <= SrcMaxGrayValue)
					ImgBuff[i] = DstCol;
			}
			return Image;
		}
		IMAGE & ReplaceColor(IMAGE & Image, COLORREF SrcCol, COLORREF DstCol)
		{
			size_t BuffSize = Image.getwidth() * Image.getheight();
			PCOLORREF ImgBuff = GetImageBuffer(&Image);
			SrcCol = BGR(SrcCol) & 0XFFFFFF;
			DstCol = BGR(DstCol);
			for (size_t i = 0; i < BuffSize; i++)
			{
				if ((ImgBuff[i] & 0XFFFFFF) == SrcCol)
					ImgBuff[i] = DstCol;
			}
			return Image;
		}
		// 纯粹颜色替换
		IMAGE & ReplaceColorBoard(IMAGE & Image, IMAGE & ColorBoard)
		{
			if (ColorBoard.getwidth() != 4096 || ColorBoard.getheight() != 4096)
				return Image;
			size_t BuffSize = Image.getwidth()*Image.getheight();
			PCOLORREF ImgBuff = GetImageBuffer(&Image);
			PCOLORREF ColBuff = GetImageBuffer(&ColorBoard);
			for (size_t i = 0; i < BuffSize; i++)
			{
				ImgBuff[i] = ColBuff[ImgBuff[i] && 0XFFFFFF];
			}
			return Image;
		}
		// 桌面截图
		IMAGE & CaptureDesktop(IMAGE & Img)
		{
			// TODO:WIN10的系统缩放导致此函数获取的宽高有错误
			WORD Width = GetSystemMetrics(SM_CXSCREEN);					// 通过 Windows API 获取桌面的宽
			WORD Height = GetSystemMetrics(SM_CYSCREEN);				// 通过 Windows API 获取桌面的高
			Img.Resize(Width, Height);									// 调整 Img 的大小
			HDC dstDC = GetImageHDC(&Img);								// 获取 IMAGE 对象的 DC
			HDC srcDC = GetDC(NULL);									// 获取桌面 DC
			BitBlt(dstDC, 0, 0, Width, Height, srcDC, 0, 0, SRCCOPY);	// DC拷贝
			return Img;
		}
		// 进程截图
		IMAGE & CaptureWnd(IMAGE & Img, HWND hwnd)
		{
			if (!hwnd)
				hwnd = GetDesktopWindow();
			RECT rect;
			::GetWindowRect(hwnd, &rect);
			int Width = rect.right - rect.left;						//获得宽度
			int Height = rect.bottom - rect.top;						//获得高度
			Img.Resize(Width, Height);									// 调整 Img 的大小
			HDC dstDC = GetImageHDC(&Img);								// 获取 IMAGE 对象的 DC
			HDC srcDC = GetDC(hwnd);									// 获取进程 DC
			BitBlt(dstDC, 0, 0, Width, Height, srcDC, 0, 0, SRCCOPY);	// DC拷贝
			return Img;
		}
		// 直方图
		IMAGE & Histogram(IMAGE & Dst, const IMAGE &Src, size_t MaxHeight = 0, ColorChannel Channel = RGB_Channel)
		{
			PCOLORREF Buff = GetImageBuffer((PIMAGE)&Src);
			size_t BuffSize = Src.getwidth() * Src.getheight();
			size_t Value[256] = { NULL };
			BYTE CMax = 0;

			switch (Channel)
			{
				case EasyXSharp::ImageOperator::R_Channel:
					for (size_t i = 0; i < BuffSize; i++)
					{
						BYTE ColPtr = GetBValue(Buff[i]);
						++Value[ColPtr];

						if (Value[ColPtr] > Value[CMax])
							CMax = ColPtr;
					}
					break;
				case EasyXSharp::ImageOperator::G_Channel:
					for (size_t i = 0; i < BuffSize; i++)
					{
						BYTE ColPtr = GetGValue(Buff[i]);
						++Value[ColPtr];

						if (Value[ColPtr] > Value[CMax])
							CMax = ColPtr;
					}
					break;
				case EasyXSharp::ImageOperator::B_Channel:
					for (size_t i = 0; i < BuffSize; i++)
					{
						BYTE ColPtr = GetRValue(Buff[i]);
						++Value[ColPtr];

						if (Value[ColPtr] > Value[CMax])
							CMax = ColPtr;
					}
					break;
				default:
					for (size_t i = 0; i < BuffSize; i++)
					{
						BYTE ColPtr = GetGrayValue(Buff[i]);
						++Value[ColPtr];

						if (Value[ColPtr] > Value[CMax])
							CMax = ColPtr;
					}
					break;
			}

			size_t Width = 256;
			size_t Height = Value[CMax];

			if (MaxHeight > 0 && Height > MaxHeight)
			{
				size_t MaxValue = Height;
				Height = MaxHeight;
				Dst.Resize(Width, MaxHeight);
				Buff = GetImageBuffer(&Dst);

				for (size_t i = 0; i < Width; ++i)
				{
					size_t Lim = Value[i] * MaxHeight / MaxValue;
					for (size_t j = 0; j < Lim; ++j)
						Buff[i + (Height - 1 - j) * Width] = WHITE;
					for (size_t j = Lim; j < Height; ++j)
						Buff[i + (Height - 1 - j) * Width] = BLACK;
				}
			}
			else
			{
				Dst.Resize(Width, Height);
				Buff = GetImageBuffer(&Dst);

				for (size_t i = 0; i < Width; ++i)
				{
					size_t Lim = Value[i];
					for (size_t j = 0; j < Lim; ++j)
						Buff[i + (Height - 1 - j) * Width] = WHITE;
					for (size_t j = Lim; j < Height; ++j)
						Buff[i + (Height - 1 - j) * Width] = BLACK;
				}
			}
			return  Dst;
		}
		// 提取通道
		IMAGE & ReserveChannel(IMAGE & Img, ColorChannel Channel)
		{
			return BinOperator::operator&=(Img, Channel);
		}
		// 平均灰度
		BYTE AveGrayValue(const IMAGE & SrcImg)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();
			
			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);
			
			unsigned long long GrayValue = 0;

			for (size_t i = 0; i < BuffSize; i++)
			{
				GrayValue += ImageOperator::GetGrayValue_BGR(SrcBuff[i]);
			}
			if (BuffSize == 0)
				return 0;
			return static_cast<BYTE>(GrayValue / BuffSize);
		}
		// 平均灰度
		double AveGrayValuelf(const IMAGE & SrcImg)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();

			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);

			unsigned long long GrayValue = 0;

			for (size_t i = 0; i < BuffSize; i++)
			{
				GrayValue += ImageOperator::GetGrayValue_BGR(SrcBuff[i]);
			}
			if (BuffSize == 0)
				return 0;
			return (GrayValue / (double)BuffSize);
		}
	}

	// 图像效果
	namespace ImageEffect
	{
		// TODO 将移植的代码修复完毕

		// 底片
		IMAGE & Negative(IMAGE & img)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] = ~Buff[i];
			}
			return img;
		}
		// 底片
		IMAGE & Negative(IMAGE & DstImg, const IMAGE & SrcImg)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();

			DstImg.Resize(SrcImg.getwidth(), SrcImg.getheight());

			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);
			PCOLORREF DstBuff = GetImageBuffer(&DstImg);

			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] = ~SrcBuff[i];
			}
			return DstImg;
		}

		// 曝光
		IMAGE & Exposure(IMAGE & img)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r = GetRValue(Buff[i]);
				BYTE g = GetGValue(Buff[i]);
				BYTE b = GetBValue(Buff[i]);

				Buff[i] = RGB(
					r > 128 ? ~r : r,
					g > 128 ? ~g : g,
					b > 128 ? ~b : b
				);
			}
			return img;
		}
		// 曝光
		IMAGE & Exposure(IMAGE & DstImg, const IMAGE & SrcImg)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();

			DstImg.Resize(SrcImg.getwidth(), SrcImg.getheight());

			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);
			PCOLORREF DstBuff = GetImageBuffer(&DstImg);

			for (size_t i = 0; i < BuffSize; i++)
			{
				BYTE r = GetRValue(SrcBuff[i]);
				BYTE g = GetGValue(SrcBuff[i]);
				BYTE b = GetBValue(SrcBuff[i]);

				DstBuff[i] = RGB(
					r > 128 ? ~r : r,
					g > 128 ? ~g : g,
					b > 128 ? ~b : b
				);
			}
			return DstImg;
		}

		// 灰度
		IMAGE & Gray(IMAGE & img)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] = ImageOperator::Gray_BGR(Buff[i]);
			}
			return img;
		}
		// 灰度
		IMAGE & Gray(IMAGE & DstImg, const IMAGE & SrcImg)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();

			DstImg.Resize(SrcImg.getwidth(), SrcImg.getheight());

			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);
			PCOLORREF DstBuff = GetImageBuffer(&DstImg);

			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] = ImageOperator::Gray_BGR(SrcBuff[i]);
			}
			return DstImg;
		}

		// 二值化【根据灰度】
		IMAGE & BinarizeByGray(IMAGE & img, BYTE grayval = 128)
		{
			size_t BuffSize = img.getwidth() * img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			for (size_t i = 0; i < BuffSize; i++)
			{
				Buff[i] = ImageOperator::GetGrayValue_BGR(Buff[i]) < grayval ? BLACK : WHITE;
			}
			return img;
		}
		// 二值化【根据灰度】
		IMAGE & BinarizeByGray(IMAGE & DstImg, const IMAGE & SrcImg, BYTE grayval = 128)
		{
			size_t BuffSize = SrcImg.getwidth() * SrcImg.getheight();

			DstImg.Resize(SrcImg.getwidth(), SrcImg.getheight());

			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)&SrcImg);
			PCOLORREF DstBuff = GetImageBuffer(&DstImg);

			for (size_t i = 0; i < BuffSize; i++)
			{
				DstBuff[i] = ImageOperator::GetGrayValue_BGR(SrcBuff[i]) < grayval ? BLACK : WHITE;
			}
			return DstImg;
		}
		
		// 二值化轮廓
		IMAGE & BinOutline(IMAGE & img, BYTE grayval = 128, bool EightConnected = false)
		{
			// TODO 移植代码
			COLORREF SEED = RED;
			size_t Width = img.getwidth();
			size_t Height = img.getheight();
			size_t BuffSize = Width * Height;
			PCOLORREF Buff = GetImageBuffer(&img);

			BinarizeByGray(img, grayval);
			PIMAGE CurImage = GetWorkingImage();
			SetWorkingImage(&img);

#define Col(x,y) (Buff[(x)+(y) * Width])	
	
			// 放置种子
			if(EightConnected)// 八连通			
				for (size_t j = 1; j < Height - 1; ++j)
				{
					size_t Exp_j = j * Width;
					size_t Exp_j_1 = (j - 1)*Width;
					size_t Exp_j_2 = (j + 1)*Width;
					for (size_t i = 1; i < Width - 1; ++i)
					{
						if (
							(Buff[i - 1 + Exp_j] == SEED || Buff[i - 1 + Exp_j] == BLACK)
							&& (Buff[i + 1 + Exp_j] == SEED || Buff[i + 1 + Exp_j] == BLACK)
							&& (Buff[i + Exp_j_1] == SEED || Buff[i + Exp_j_1] == BLACK)
							&& (Buff[i + Exp_j_2] == SEED || Buff[i + Exp_j_2] == BLACK)
							&& (Buff[i - 1 + Exp_j_1] == SEED || Buff[i - 1 + Exp_j_1] == BLACK)
							&& (Buff[i + 1 + Exp_j_1] == SEED || Buff[i + 1 + Exp_j_1] == BLACK)
							&& (Buff[i - 1 + Exp_j_2] == SEED || Buff[i - 1 + Exp_j_2] == BLACK)
							&& (Buff[i + 1 + Exp_j_2] == SEED || Buff[i + 1 + Exp_j_2] == BLACK)
							)
						{
							Buff[i + j * Width] = SEED;
						}
					}
				}
			else
				for (size_t j = 1; j < Height - 1; ++j)
				{
					size_t Exp_j = j * Width;
					size_t Exp_j_1 = (j - 1)*Width;
					size_t Exp_j_2 = (j + 1)*Width;
					for (size_t i = 1; i < Width - 1; ++i)
					{
						if (
							(Buff[i - 1 + Exp_j] == SEED || Buff[i - 1 + Exp_j] == BLACK)
							&& (Buff[i + 1 + Exp_j] == SEED || Buff[i + 1 + Exp_j] == BLACK)
							&& (Buff[i + Exp_j_1] == SEED || Buff[i + Exp_j_1] == BLACK)
							&& (Buff[i + Exp_j_2] == SEED || Buff[i + Exp_j_2] == BLACK)
							)
						{
							Buff[i + j * Width] = SEED;
						}
					}
				}
#undef Col
			// 替换颜色
			ImageOperator::ReplaceColor(img, BGR(SEED), WHITE);

			SetWorkingImage(CurImage);
			return img;
		}
		// 扩散效果
		IMAGE & Diffuse(IMAGE & img, size_t Degree = 5)
		{
			// TODO 移植代码
			if (Degree == 0)
				return img;
			size_t Width = img.getwidth();
			size_t Height = img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);

			for (size_t j = 0; j < Height; j++)
			{
				int y = j + rand() % Degree - (Degree >> 1);
				if (y < 0)
					y = 0;
				else if (y >= (int)Height)
					y = Height - 1;
				for (size_t i = 0; i < Width; i++)
				{
					int x = i + rand() % Degree - (Degree >> 1);
					if (x < 0)
						x = 0;
					else if (x >= (int)Width)
						x = Width - 1;

					Buff[i + j * Width] = Buff[x + y * Width];
				}
			}
			return img;
		}
		// 浮雕效果
		IMAGE & Emboss(IMAGE & img, size_t Degree = 3)
		{
			// TODO 移植代码
			size_t Width = img.getwidth();
			size_t Height = img.getheight();
			PCOLORREF Buff = GetImageBuffer(&img);
			BYTE R, G, B;
			for (size_t i = 0; i < Width; i++)
				for (size_t j = 0; j < Height; j++)
				{
					R = GetRValue(Buff[i + j * Width]) - GetRValue(Buff[(i + Degree) % Width + ((j + Degree) % Height)*Width]) + 128;
					G = GetGValue(Buff[i + j * Width]) - GetGValue(Buff[(i + Degree) % Width + ((j + Degree) % Height)*Width]) + 128;
					B = GetBValue(Buff[i + j * Width]) - GetBValue(Buff[(i + Degree) % Width + ((j + Degree) % Height)*Width]) + 128;
					Buff[i + j * Width] = ImageOperator::Gray_BGR(RGB(R, G, B));
				}
			return img;
		}
		// 黑白漫画
		IMAGE & BlackWhiteComics(IMAGE & img)
		{
			PCOLORREF Buff = GetImageBuffer(&img);	  //获取图像内存指针
			size_t Width = img.getwidth();
			size_t Height = img.getheight();

			int R, G, B, Gray;
			for (size_t j = 0; j < Height; j++)
			{
				size_t Exp_j = j * Width;
				for (size_t i = 0; i < Width; i++)
				{
					size_t Exp_i_j = i + Exp_j;
					//计算新的RGB值
					Gray = abs((GetGValue(Buff[Exp_i_j]) << 1) - GetBValue(Buff[Exp_i_j]) + GetRValue(Buff[Exp_i_j]))* GetRValue(Buff[Exp_i_j]) >> 8;
					R = G = Gray + 10 > 0XFF ? 0XFF : Gray + 10;
					B = Gray > 0XFF ? 0XFF : Gray;;
					Buff[Exp_i_j] = RGB(B, G, R);
				}
			}
			return img;
		}
#if 0

		IMAGE*GaussBlur(IMAGE*img)
		{//高斯滤波
			COLOR*pBuf = (COLOR*)GetImageBuffer(img);	  //获取图像内存指针
			Size Width, Height, i, j;
			if (img)
			{//向图像写入
				Width = img->getwidth();			//获取宽度
				Height = img->getheight();			//获取高度
			}
			else
			{//向屏幕写入
				Width = getwidth();			//获取宽度
				Height = getheight();			//获取高度
			}
			char x, y;//模板索引坐标
			//高斯核
			char Gauss_Core[5][5] = { 1, 4, 7, 4, 1,
									4,16,26,16, 4,
									7,26,41,26, 7,
									4,16,26,16, 4,
									1, 4, 7, 4, 1 };
			COLORREF R, G, B, T;
			for (i = 2; i < Width - 2; i++)
				for (j = 2; j < Height - 2; j++)
				{
					R = G = B = 0;
					for (x = 0; x <= 4; x++)
						for (y = 0; y <= 4; y++)
						{
							T = (i + x - 2 + Width) % Width + ((j + y - 2 + Height) % Height)*Width;
							R += pBuf[T].R*Gauss_Core[x][y];
							G += pBuf[T].G*Gauss_Core[x][y];
							B += pBuf[T].B*Gauss_Core[x][y];
						}
					R /= 273;
					G /= 273;
					B /= 273;
					if (R > 0XFF)R = 0XFF;
					if (G > 0XFF)G = 0XFF;
					if (B > 0XFF)B = 0XFF;
					pBuf[i + j * Width].R = R;
					pBuf[i + j * Width].G = G;
					pBuf[i + j * Width].B = B;
				}
			return img;
		}
		IMAGE*IMAGE_Neon(IMAGE*img, BYTE Degree)
		{//霓虹效果
			COLOR*pBuf = (COLOR*)GetImageBuffer(img);	  //获取图像内存指针
			Size Width, Height, i, j;
			if (img)
			{//向图像写入
				Width = img->getwidth();			//获取宽度
				Height = img->getheight();			//获取高度
			}
			else
			{//向屏幕写入
				Width = getwidth();			//获取宽度
				Height = getheight();			//获取高度
			}
			short R, G, B;
			for (i = 0; i < Width - 1; i++)
				for (j = 0; j < Height - 1; j++)
				{
					R = Degree * sqrt((pBuf[i + j * Width].R - pBuf[i + 1 + j * Width].R)*(pBuf[i + j * Width].R - pBuf[i + 1 + j * Width].R)
									  + (pBuf[i + j * Width].R - pBuf[i + (j + 1)*Width].R)*(pBuf[i + j * Width].R - pBuf[i + 1 + (j + 1)*Width].R));
					G = Degree * sqrt((pBuf[i + j * Width].G - pBuf[i + 1 + j * Width].G)*(pBuf[i + j * Width].G - pBuf[i + 1 + j * Width].G)
									  + (pBuf[i + j * Width].G - pBuf[i + (j + 1)*Width].G)*(pBuf[i + j * Width].G - pBuf[i + 1 + (j + 1)*Width].G));
					B = Degree * sqrt((pBuf[i + j * Width].B - pBuf[i + 1 + j * Width].B)*(pBuf[i + j * Width].B - pBuf[i + 1 + j * Width].B)
									  + (pBuf[i + j * Width].B - pBuf[i + (j + 1)*Width].B)*(pBuf[i + j * Width].B - pBuf[i + 1 + (j + 1)*Width].B));
					if (R > 0XFF)R = 0XFF;
					if (G > 0XFF)G = 0XFF;
					if (B > 0XFF)B = 0XFF;
					pBuf[i + j * Width].R = R;
					pBuf[i + j * Width].G = G;
					pBuf[i + j * Width].B = B;

				}
			return img;
		}
		IMAGE*IMAGE_Nostalgic(IMAGE*img)
		{//怀旧
			COLOR*pBuf = (COLOR*)GetImageBuffer(img);	  //获取图像内存指针
			Size Width, Height, i, j;
			if (img)
			{//向图像写入
				Width = img->getwidth();			//获取宽度
				Height = img->getheight();			//获取高度
			}
			else
			{//向屏幕写入
				Width = getwidth();			//获取宽度
				Height = getheight();			//获取高度
			}
			short R, G, B;
			for (i = 0; i < Width - 1; i++)
				for (j = 0; j < Height - 1; j++)
				{
					R = 0.393*pBuf[i + j * Width].R + 0.769*pBuf[i + j * Width].G + 0.189*pBuf[i + j * Width].B;
					G = 0.349*pBuf[i + j * Width].R + 0.686*pBuf[i + j * Width].G + 0.168*pBuf[i + j * Width].B;
					B = 0.272*pBuf[i + j * Width].R + 0.534*pBuf[i + j * Width].G + 0.131*pBuf[i + j * Width].B;
					if (R > 0XFF)R = 0XFF;
					if (G > 0XFF)G = 0XFF;
					if (B > 0XFF)B = 0XFF;
					pBuf[i + j * Width].R = R;
					pBuf[i + j * Width].G = G;
					pBuf[i + j * Width].B = B;
				}
			return img;
		}

		IMAGE*IMAGE_Mosaic(IMAGE*img,Size Degree){//马赛克（Degree为区域块边缘）
		if (Degree == 0 || Degree == 1)//无需运算
			return img;
		COLOR*pBuf = (COLOR*)GetImageBuffer(img);	//获取内存指针
		Size Width, Height, i, j, x, y, height, width;
		unsigned long MosaicValueR, MosaicValueG, MosaicValueB;
		if (img)
		{//向图像写入
			Width = img->getwidth();			//获取宽度
			Height = img->getheight();			//获取高度
		}
		else
		{//向屏幕写入
			Width = getwidth();			//获取宽度
			Height = getheight();			//获取高度
		}
		for (i = 0; i < Width / Degree; i++)
		{
			for (j = 0; j < Height / Degree; j++)
			{
				MosaicValueR = MosaicValueG = MosaicValueB = 0;
				for (x = i * Degree; x < (i + 1)*Degree; x++)//统计当前区块颜色
					for (y = j * Degree; y < (j + 1)*Degree; y++)
					{
						MosaicValueR += pBuf[x + y * Width].R;
						MosaicValueG += pBuf[x + y * Width].G;
						MosaicValueB += pBuf[x + y * Width].B;
					}
				MosaicValueR /= Degree * Degree;
				MosaicValueG /= Degree * Degree;
				MosaicValueB /= Degree * Degree;
				for (x = i * Degree; x < (i + 1)*Degree; x++)//为当前区块着色
					for (y = j * Degree; y < (j + 1)*Degree; y++)
					{
						pBuf[x + y * Width].R = MosaicValueR;
						pBuf[x + y * Width].G = MosaicValueG;
						pBuf[x + y * Width].B = MosaicValueB;
					}
			}
		}
		if (height = Height % Degree)//纵向未完成
			for (i = 0; i < Width / Degree; i++)
			{
				MosaicValueR = MosaicValueG = MosaicValueB = 0;
				for (x = i * Degree; x < (i + 1)*Degree; x++)//统计当前区块颜色
					for (y = Height - height; y < Height; y++)
					{
						MosaicValueR += pBuf[x + y * Width].R;
						MosaicValueG += pBuf[x + y * Width].G;
						MosaicValueB += pBuf[x + y * Width].B;
					}
				MosaicValueR /= Degree * height;
				MosaicValueG /= Degree * height;
				MosaicValueB /= Degree * height;
				for (x = i * Degree; x < (i + 1)*Degree; x++)//为当前区块着色
					for (y = Height - height; y < Height; y++)
					{
						pBuf[x + y * Width].R = MosaicValueR;
						pBuf[x + y * Width].G = MosaicValueG;
						pBuf[x + y * Width].B = MosaicValueB;
					}
			}
		if (width = Width % Degree)//横向未完成
			for (j = 0; j < Height / Degree; j++)
			{
				MosaicValueR = MosaicValueG = MosaicValueB = 0;
				for (x = Width - width; x < Width; x++)//统计当前区块颜色
					for (y = j * Degree; y < (j + 1)*Degree; y++)
					{
						MosaicValueR += pBuf[x + y * Width].R;
						MosaicValueG += pBuf[x + y * Width].G;
						MosaicValueB += pBuf[x + y * Width].B;
					}
				MosaicValueR /= Degree * width;
				MosaicValueG /= Degree * width;
				MosaicValueB /= Degree * width;
				for (x = Width - width; x < Width; x++)//为当前区块着色
					for (y = j * Degree; y < (j + 1)*Degree; y++)
					{
						pBuf[x + y * Width].R = MosaicValueR;
						pBuf[x + y * Width].G = MosaicValueG;
						pBuf[x + y * Width].B = MosaicValueB;
					}
		}
		if (height&&width)
		{//横纵均未完成
			for (x = Width - width; x < Width; x++)
				for (y = Height - height; y < Height; y++)
				{
					MosaicValueR += pBuf[x + y * Width].R;
					MosaicValueG += pBuf[x + y * Width].G;
					MosaicValueB += pBuf[x + y * Width].B;
				}
			MosaicValueR /= width * height;
			MosaicValueG /= width * height;
			MosaicValueB /= width * height;
			for (x = Width - width; x < Width; x++)
				for (y = Height - height; y < Height; y++)
				{
					pBuf[x + y * Width].R = MosaicValueR;
					pBuf[x + y * Width].G = MosaicValueG;
					pBuf[x + y * Width].B = MosaicValueB;
				}
		}
		return img;
}
		IMAGE*IMAGE_LightMap(IMAGE*img)
		{//亮度图像
			COLOR*pBuf = (COLOR*)GetImageBuffer(img);	//获取内存指针
			Size Width, Height, i, j;
			if (img)
			{//向图像写入
				Width = img->getwidth();			//获取宽度
				Height = img->getheight();			//获取高度
			}
			else
			{//向屏幕写入
				Width = getwidth();			//获取宽度
				Height = getheight();			//获取高度
			}
			for (i = 0; i < Width; i++)
				for (j = 0; j < Height; j++)
					pBuf[i + j * Width].R =
					pBuf[i + j * Width].G =
					pBuf[i + j * Width].B =
					pBuf[i + j * Width].R > pBuf[i + j * Width].G ? (pBuf[i + j * Width].R > pBuf[i + j * Width].B ? pBuf[i + j * Width].R : pBuf[i + j * Width].B) :
					(pBuf[i + j * Width].G > pBuf[i + j * Width].B ? pBuf[i + j * Width].G : pBuf[i + j * Width].B) +
					pBuf[i + j * Width].R < pBuf[i + j * Width].G ? (pBuf[i + j * Width].R < pBuf[i + j * Width].B ? pBuf[i + j * Width].R : pBuf[i + j * Width].B) :
					(pBuf[i + j * Width].G < pBuf[i + j * Width].B ? pBuf[i + j * Width].G : pBuf[i + j * Width].B);
			return img;
		}
		
		IMAGE & IMAGE_Blur(PIMAGE img = NULL, BYTE Degree = 2)
		{//模糊处理
			if (!Degree)
				return img;
			COLOR*pBuf = (COLOR*)GetImageBuffer(img);	//获取内存指针
			Size Width, Height, i, j;
			if (img)
			{//向图像写入
				Width = img->getwidth();			//获取宽度
				Height = img->getheight();			//获取高度
			}
			else
			{//向屏幕写入
				Width = getwidth();			//获取宽度
				Height = getheight();			//获取高度
			}
			Long R, G, B, T;
			char x, y;
			for (i = 0; i < Width; i++)
				for (j = 0; j < Height; j++)
				{
					R = G = B = 0;
					for (x = -Degree; x <= Degree; x++)
						for (y = -Degree; y <= Degree; y++)
						{
							T = (i + x + Width) % Width + ((j + y + Height) % Height)*Width;
							R += pBuf[T].R;
							G += pBuf[T].G;
							B += pBuf[T].B;
						}
					R /= (Degree * 2 + 1)*(Degree * 2 + 1);
					G /= (Degree * 2 + 1)*(Degree * 2 + 1);
					B /= (Degree * 2 + 1)*(Degree * 2 + 1);
					pBuf[i + j * Width].R = R > 0XFF ? 0XFF : R;
					pBuf[i + j * Width].G = G > 0XFF ? 0XFF : G;
					pBuf[i + j * Width].B = B > 0XFF ? 0XFF : B;
				}
			return img;
		}
#endif // 0
	}

	// 类型转换
	namespace TypeConversion
	{
		// 双精度转换整型【四舍五入】
		inline int lf2i(double lf)
		{
			return static_cast<int>(lf + 0.5);
		}
		// 整型转换双精度型
		inline double i2lf(int i)
		{
			return static_cast<double>(i);
		}
	}

	// 文字输出
	namespace TextPrint
	{
		enum AlignMethod :BYTE
		{
			ALIGN_LEFT = 0B0001,			// 左对齐
			ALIGN_RIGHT = 0B0010,			// 右对齐
			ALIGN_H_CENTER = 0B0011,		// 水平居中
			MASK_ALIGN_HORIZONTAL = 0B0011,	// 水平对齐掩码
			ALIGN_TOP = 0B0100,				// 上方对齐
			ALIGN_BOTTOM = 0B1000,			// 底部对齐
			ALIGN_V_CENTER = 0B1100,		// 垂直居中
			MASK_ALIGN_VERTICAL = 0B1100,	// 垂直对齐掩码
			ALIGN_HV_CENTER = 0B1111		// 水平垂直居中
		};
		void OutTextAt(int x, int y, TCHAR c, AlignMethod align = ALIGN_LEFT)
		{
			int TextWidth = textwidth(c);
			int TextHeight = textheight(c);

			// 检测水平对齐方式
			switch (align&MASK_ALIGN_HORIZONTAL)
			{
				case ALIGN_LEFT:
					break;
				case ALIGN_RIGHT:
					x -= TextWidth;
					break;
				case ALIGN_H_CENTER:
					x -= (TextWidth >> 1);
					break;
			}
			// 检测垂直对齐方式
			switch (align&MASK_ALIGN_VERTICAL)
			{
				case ALIGN_TOP:
					break;
				case ALIGN_BOTTOM:
					y -= TextHeight;
					break;
				case ALIGN_V_CENTER:
					y -= (TextHeight >> 1);
					break;
			}
		}
		void OutTextAt(int x, int y, LPCTSTR str, AlignMethod align = ALIGN_LEFT)
		{
			int TextWidth = textwidth(str);
			int TextHeight = textheight(str);

			// 检测水平对齐方式
			switch (align&MASK_ALIGN_HORIZONTAL)
			{
				case ALIGN_LEFT:
					break;
				case ALIGN_RIGHT:
					x -= TextWidth;
					break;
				case ALIGN_H_CENTER:
					x -= (TextWidth >> 1);
					break;
			}
			// 检测垂直对齐方式
			switch (align&MASK_ALIGN_VERTICAL)
			{
				case ALIGN_TOP:
					break;
				case ALIGN_BOTTOM:
					y -= TextHeight;
					break;
				case ALIGN_V_CENTER:
					y -= (TextHeight >> 1);
					break;
			}
			::outtextxy(x, y, str);
		}
	}


	// 时间相关
	namespace TimeControl
	{
		// 绝对延时
		void AccurateSleep(DWORD Milliseconds)
		{
			static clock_t oldclock = clock();
			oldclock += Milliseconds * CLOCKS_PER_SEC / 1000;
			if (clock() > oldclock)
				oldclock = clock();
			else
				while (clock() < oldclock)
					Sleep(1);
		}
		// FPS
		inline double GetFPS()
		{
			static constexpr int FPS_COUNT = 4;
			static unsigned int _Tick = 0;
			static DWORD StartTime = GetTickCount();
			static double fps;
			if (_Tick > FPS_COUNT)
			{
				_Tick = 0;
				DWORD CurrentTime = GetTickCount();
				DWORD PastTime = CurrentTime - StartTime;
				fps = FPS_COUNT / (PastTime / 1000.0f);
				StartTime = CurrentTime;
			}
			++_Tick;
			return fps;
		}
	}

	// 图像输出
	namespace ImagePrint
	{

	}

	// 缩放算法
	namespace ZoomAlgorithm
	{
		// 缩放-临近插值算法
		IMAGE& ZoomNearestInterpolation(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight);
		IMAGE& ZoomNearestInterpolation(IMAGE& Dst, size_t DstWidth, size_t DstHeight);

		// 缩放-双线插值算法
		IMAGE& ZoomBilinearInterpolation_i(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight);
		IMAGE& ZoomBilinearInterpolation_i_s(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight);
		IMAGE& ZoomBilinearInterpolation_lf(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)	//【双精度型】
		{
			size_t SrcWidth = (size_t)Src.getwidth();
			size_t SrcHeight = (size_t)Src.getheight();

			if (DstWidth == 0 && DstHeight == 0 || SrcWidth == 0 || SrcHeight == 0)
			{
				return Dst = Src;
			}
			else if (DstHeight == 0)
			{
				DstHeight = DstWidth * SrcHeight / SrcWidth;
			}
			else if (DstWidth == 0)
			{
				DstWidth = DstHeight * SrcWidth / SrcHeight;
			}
			Dst.Resize(DstWidth, DstHeight);

			PCOLORREF DstBuff = GetImageBuffer(&Dst);
			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)& Src);

			size_t DstX, DstY;

			int R, G, B;

			for (DstY = 0; DstY < DstHeight; ++DstY)
			{
				// 计算行起点偏移
				size_t RemY = DstY * SrcHeight % DstWidth;
				size_t SrcY1 = DstY * SrcHeight / DstWidth;
				size_t SrcY2 = RemY > 0 ? SrcY1 + 1 : SrcY1;
				size_t DstRowOff = DstY * DstWidth;
				size_t SrcRowOff = SrcY1 * SrcWidth;
				double dy = RemY / static_cast<double>(DstWidth);

				for (DstX = 0; DstX < DstWidth; ++DstX)
				{
					// 映射到原图		
					size_t RemX = DstX * SrcWidth % DstWidth;
					size_t SrcX1 = DstX * SrcWidth / DstWidth;
					size_t SrcX2 = RemX > 0 ? SrcX1 + 1 : SrcX1;
					double dx = RemX / static_cast<double>(DstWidth);

					// 计算辅助表达式
					double Exp11 = (1 - dx) * (1 - dy);
					double Exp12 = (1 - dx) * dy;
					double Exp21 = dx * (1 - dy);
					double Exp22 = dx * dy;

					COLORREF C11 = SrcBuff[SrcX1 + SrcY1 * SrcWidth];
					COLORREF C12 = SrcBuff[SrcX1 + SrcY2 * SrcWidth];
					COLORREF C21 = SrcBuff[SrcX2 + SrcY1 * SrcWidth];
					COLORREF C22 = SrcBuff[SrcX2 + SrcY2 * SrcWidth];

					BYTE R11 = GetRValue(C11);
					BYTE R12 = GetRValue(C12);
					BYTE R21 = GetRValue(C21);
					BYTE R22 = GetRValue(C22);

					BYTE G11 = GetGValue(C11);
					BYTE G12 = GetGValue(C12);
					BYTE G21 = GetGValue(C21);
					BYTE G22 = GetGValue(C22);

					BYTE B11 = GetBValue(C11);
					BYTE B12 = GetBValue(C12);
					BYTE B21 = GetBValue(C21);
					BYTE B22 = GetBValue(C22);


					R = static_cast<int>(static_cast<double>(R11) * Exp11
							 + static_cast<double>(R12) * Exp12
							 + static_cast<double>(R21) * Exp21
							 + static_cast<double>(R22) * Exp22);
					G = static_cast<int>(static_cast<double>(G11) * Exp11
							 + static_cast<double>(G12) * Exp12
							 + static_cast<double>(G21) * Exp21
							 + static_cast<double>(G22) * Exp22);
					B = static_cast<int>(static_cast<double>(B11) * Exp11
							 + static_cast<double>(B12) * Exp12
							 + static_cast<double>(B21) * Exp21
							 + static_cast<double>(B22) * Exp22);

					DstBuff[DstX + DstRowOff] = RGB(R, G, B);
				}
			}
			return  Dst;
		}
		IMAGE& ZoomBilinearInterpolation_lf_s(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)	//【双精度型|检查数据范围】
		{
			size_t SrcWidth = (size_t)Src.getwidth();
			size_t SrcHeight = (size_t)Src.getheight();

			if (DstWidth == 0 && DstHeight == 0 || SrcWidth == 0 || SrcHeight == 0)
			{
				return Dst = Src;
			}
			else if (DstHeight == 0)
			{
				DstHeight = DstWidth * SrcHeight / SrcWidth;
			}
			else if (DstWidth == 0)
			{
				DstWidth = DstHeight * SrcWidth / SrcHeight;
			}
			Dst.Resize(DstWidth, DstHeight);

			PCOLORREF DstBuff = GetImageBuffer(&Dst);
			PCOLORREF SrcBuff = GetImageBuffer((PIMAGE)& Src);

			size_t DstX, DstY;

			int R, G, B;

			for (DstY = 0; DstY < DstHeight; ++DstY)
			{
				// 计算行起点偏移
				size_t RemY = DstY * SrcHeight % DstWidth;
				size_t SrcY1 = DstY * SrcHeight / DstWidth;
				size_t SrcY2 = RemY > 0 ? SrcY1 + 1 : SrcY1;
				size_t DstRowOff = DstY * DstWidth;
				size_t SrcRowOff = SrcY1 * SrcWidth;
				double dy = RemY / static_cast<double>(DstWidth);

				for (DstX = 0; DstX < DstWidth; ++DstX)
				{
					// 映射到原图		
					size_t RemX = DstX * SrcWidth % DstWidth;
					size_t SrcX1 = DstX * SrcWidth / DstWidth;
					size_t SrcX2 = RemX > 0 ? SrcX1 + 1 : SrcX1;
					double dx = RemX / static_cast<double>(DstWidth);

					// 计算辅助表达式
					double Exp11 = (1 - dx) * (1 - dy);
					double Exp12 = (1 - dx) * dy;
					double Exp21 = dx * (1 - dy);
					double Exp22 = dx * dy;

					COLORREF C11 = SrcBuff[SrcX1 + SrcY1 * SrcWidth];
					COLORREF C12 = SrcBuff[SrcX1 + SrcY2 * SrcWidth];
					COLORREF C21 = SrcBuff[SrcX2 + SrcY1 * SrcWidth];
					COLORREF C22 = SrcBuff[SrcX2 + SrcY2 * SrcWidth];

					BYTE R11 = GetRValue(C11);
					BYTE R12 = GetRValue(C12);
					BYTE R21 = GetRValue(C21);
					BYTE R22 = GetRValue(C22);

					BYTE G11 = GetGValue(C11);
					BYTE G12 = GetGValue(C12);
					BYTE G21 = GetGValue(C21);
					BYTE G22 = GetGValue(C22);

					BYTE B11 = GetBValue(C11);
					BYTE B12 = GetBValue(C12);
					BYTE B21 = GetBValue(C21);
					BYTE B22 = GetBValue(C22);


					R = static_cast<int>(static_cast<double>(R11) * Exp11
							 + static_cast<double>(R12) * Exp12
							 + static_cast<double>(R21) * Exp21
							 + static_cast<double>(R22) * Exp22);
					G = static_cast<int>(static_cast<double>(G11) * Exp11
							 + static_cast<double>(G12) * Exp12
							 + static_cast<double>(G21) * Exp21
							 + static_cast<double>(G22) * Exp22);
					B = static_cast<int>(static_cast<double>(B11) * Exp11
							 + static_cast<double>(B12) * Exp12
							 + static_cast<double>(B21) * Exp21
							 + static_cast<double>(B22) * Exp22);

					if (R > 255)
						R = 255;
					else if (R < 0)
						R = 0;
					if (G > 255)
						G = 255;
					else if (G < 0)
						G = 0;
					if (B > 255)
						B = 255;
					else if (B < 0)
						B = 0;

					DstBuff[DstX + DstRowOff] = RGB(R, G, B);
				}
			}
			return  Dst;
		}
		IMAGE& ZoomBilinearInterpolation(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)	//【整型】
		{
			// 默认使用整型快速双线插值
			return ZoomBilinearInterpolation_i(Dst, Src, DstWidth, DstHeight);
		}
		IMAGE& ZoomBilinearInterpolation(IMAGE& Dst, size_t DstWidth, size_t DstHeight)	//【整型】
		{
			// 默认使用整型快速双线插值
			IMAGE Src(Dst);
			return ZoomBilinearInterpolation_i(Dst, Src, DstWidth, DstHeight);
		}

		// 缩放-整合
		inline IMAGE& Zoom(IMAGE& Dst, IMAGE& Src, size_t DstWidth, size_t DstHeight)
		{
			// 默认使用整型快速双线插值
			return ZoomBilinearInterpolation_i(Dst, Src, DstWidth, DstHeight);
		}
		inline IMAGE& Zoom(IMAGE& Dst, size_t DstWidth, size_t DstHeight)
		{
			// 默认使用整型快速双线插值
			IMAGE Src(Dst);
			return ZoomBilinearInterpolation_i(Dst, Src, DstWidth, DstHeight);
		}
		inline IMAGE& QuickZoom(IMAGE& Dst, IMAGE& Src, size_t DstWidth, size_t DstHeight)
		{
			return  ZoomNearestInterpolation(Dst, Src, DstWidth, DstHeight);
		}
		inline IMAGE& QuickZoom(IMAGE& Dst, size_t DstWidth, size_t DstHeight)
		{
			IMAGE Src(Dst);
			return  ZoomNearestInterpolation(Dst, Src, DstWidth, DstHeight);

		}
	}
	// 版本信息
	struct Version
	{
		DWORD MajorVersionNumber;	// 主版本号
		DWORD MinorVersionNumber;	// 子版本号
		DWORD RevisionNumber;		// 修正版本号
		DWORD BuildNumber;		// 编译版本号
		Version(DWORD mav, DWORD miv, DWORD rev, DWORD buv) :
			MajorVersionNumber(mav),
			MinorVersionNumber(miv),
			RevisionNumber(rev),
			BuildNumber(buv)
		{
		}
		Version():
			MajorVersionNumber(0),
			MinorVersionNumber(0),
			RevisionNumber(0),
			BuildNumber(0)
		{
		}

		// 版本比较

		bool operator >(const Version&v2)const
		{
			// 主版本号
			if (MajorVersionNumber > v2.MajorVersionNumber)
				return true;
			else if (MajorVersionNumber < v2.MajorVersionNumber)
				return false;
			// 子版本号
			else if (MinorVersionNumber > v2.MinorVersionNumber)
				return true;
			else if (MinorVersionNumber < v2.MinorVersionNumber)
				return false;
			// 修正版本号
			else if (RevisionNumber > v2.RevisionNumber)
				return true;
			else if (RevisionNumber < v2.RevisionNumber)
				return false;
			// 编译版本号
			else if (BuildNumber > v2.BuildNumber)
				return true;
			else
				return false;					
		}

		bool operator >=(const Version&v2)const
		{
			// 主版本号
			if (MajorVersionNumber > v2.MajorVersionNumber)
				return true;
			else if (MajorVersionNumber < v2.MajorVersionNumber)
				return false;
			// 子版本号
			else if (MinorVersionNumber > v2.MinorVersionNumber)
				return true;
			else if (MinorVersionNumber < v2.MinorVersionNumber)
				return false;
			// 修正版本号
			else if (RevisionNumber > v2.RevisionNumber)
				return true;
			else if (RevisionNumber < v2.RevisionNumber)
				return false;
			// 编译版本号
			else if (BuildNumber >= v2.BuildNumber)
				return true;
			else
				return false;
		}

		bool operator <(const Version&v2)const
		{
			// 主版本号
			if (MajorVersionNumber < v2.MajorVersionNumber)
				return true;
			else if (MajorVersionNumber > v2.MajorVersionNumber)
				return false;
			// 子版本号
			else if (MinorVersionNumber < v2.MinorVersionNumber)
				return true;
			else if (MinorVersionNumber > v2.MinorVersionNumber)
				return false;
			// 修正版本号
			else if (RevisionNumber < v2.RevisionNumber)
				return true;
			else if (RevisionNumber > v2.RevisionNumber)
				return false;
			// 编译版本号
			else if (BuildNumber < v2.BuildNumber)
				return true;
			else
				return false;
		}

		bool operator <=(const Version&v2)const
		{
			// 主版本号
			if (MajorVersionNumber < v2.MajorVersionNumber)
				return true;
			else if (MajorVersionNumber > v2.MajorVersionNumber)
				return false;
			// 子版本号
			else if (MinorVersionNumber < v2.MinorVersionNumber)
				return true;
			else if (MinorVersionNumber > v2.MinorVersionNumber)
				return false;
			// 修正版本号
			else if (RevisionNumber < v2.RevisionNumber)
				return true;
			else if (RevisionNumber > v2.RevisionNumber)
				return false;
			// 编译版本号
			else if (BuildNumber <= v2.BuildNumber)
				return true;
			else
				return false;
		}

		bool operator ==(const Version&v2)const
		{
			return MajorVersionNumber == v2.MajorVersionNumber
				&&MinorVersionNumber == v2.MinorVersionNumber
				&&RevisionNumber == v2.RevisionNumber
				&&BuildNumber == v2.BuildNumber;
		}
		
		bool operator !=(const Version&v2)const
		{
			return MajorVersionNumber != v2.MajorVersionNumber
				||MinorVersionNumber != v2.MinorVersionNumber
				||RevisionNumber != v2.RevisionNumber
				||BuildNumber != v2.BuildNumber;
		}

	};

	// 精灵图
	Version SpriteVer(0, 1, 0, 0);	// 版本信息
	class SpriteImage
	{
	protected:
		static constexpr DWORD MagticNumber = MAKELONG(MAKEWORD('S', 'P'), MAKEWORD('R', 'T'));
		static constexpr Version &SpriteVersion = SpriteVer;

		using SpriteImageTable = std::vector<IMAGE>;
		SpriteImageTable Table;	// 精灵图数组
	public:
		size_t SpriteCols = 1;				// 精灵图列数

		virtual void Load(LPCTSTR ImgFile, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);
		virtual void Load(LPCTSTR ResType, LPCTSTR ResName, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);
		virtual void Load(const IMAGE & WholeImage, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);

		// 移除指定帧
		virtual void Erase(int from, int to);
		// 重设图像尺寸
		virtual void Resize(int width, int height);
		// 缩放图像
		virtual void Zoom(int width, int height);
		// 设置列数
		virtual void SetCols(int Cols)
		{
			SpriteCols = Cols;
		}
		// 获得精灵数量
		virtual size_t Size()const
		{
			return Table.size();
		}

		// 索引
		virtual IMAGE&operator [](int ptr)
		{
			return Table[ptr];
		}
		virtual const IMAGE&At(int x, int y)const
		{
			return Table[y * SpriteCols + x];
		}
		virtual const IMAGE&At(int ptr)const
		{
			return Table[ptr];
		}
	public:
		enum SpriteFileErrorCode
		{
			SUCCESS = 0,
			CANNOT_OPEN_FILE = -1,
			NOT_SPRT_FILE = -2,
			FILE_VERSION_TOOHIGH = -3,
			FILE_VERSION_TOOLOW = -4
		};
		struct SpriteImageFileMark
		{
			DWORD MagticNumber;
			DWORD ContentOffset;			// 文件标记+文件头大小【内容偏移】
		};
		struct SpriteImageFileHeader
		{
			Version SpriteVersion;		// 版本信息
			size_t SpriteNumber;		// 精灵数量
			size_t SpriteCols;			// 精灵图列数
			int SpriteWidth;			// 精灵图宽度
			int SpriteHeight;			// 精灵图高度

			SpriteImageFileHeader() :
				SpriteVersion(),
				SpriteNumber(0),
				SpriteCols(1),
				SpriteWidth(0),
				SpriteHeight(0)
			{
			}
		};

		//// 保存sprimg文件
		//virtual SpriteFileErrorCode SaveSprimgFile(LPCTSTR SprimgFile)const;
		//// 读取sprimg文件
		//virtual SpriteFileErrorCode ReadSprimgFile(LPCTSTR SprimgFile);

		//// 保存sprimg文件
		//static SpriteFileErrorCode SaveSprimgFile(LPCTSTR SprimgFile, LPCTSTR ImgFile, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);
		//static SpriteFileErrorCode SaveSprimgFile(LPCTSTR SprimgFile, LPCTSTR ResType, LPCTSTR ResName, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);
		//static SpriteFileErrorCode SaveSprimgFile(LPCTSTR SprimgFile, const IMAGE & WholeImage, int SrcImageRows = 1, int SrcImageCols = 1, int SpriteImageCols = 0, int UseImageNum = 0);
		//static SpriteFileErrorCode SaveSprimgFile(LPCTSTR SprimgFile, const SpriteImage&Sprite);
	};
	
	// 循环动画
	class LoopAnimation :public SpriteImage
	{
		size_t FramePtr = 0;
	public:
		size_t IntervalMillisecond = 30;	// 帧间隔
		struct LoopAnimationFileHeader :public SpriteImageFileHeader
		{
			size_t IntervalMillisecond = 0;	// 精灵图帧间隔
		};

		// 获得下一帧
		const IMAGE&NextFrame()
		{
			return Table[FramePtr = (FramePtr + 1) % Size()];
		}
		// 获得当前帧
		const IMAGE&CurrentFrame()const
		{
			return Table[FramePtr];
		}
		// 设置帧位置 
		void SetFramePtr(int n)
		{
			FramePtr = n % SpriteImage::Size();
		}
		// 设置帧间隔
		void SetIntervalMillisecond(size_t Intervalmillisecond)
		{
			IntervalMillisecond = Intervalmillisecond;
		}

		//// 保存lopani文件
		//virtual SpriteFileErrorCode SaveLopaniFile(LPCTSTR LopaniFile)const;
		//// 读取lopani文件
		//virtual SpriteFileErrorCode ReadLopaniFile(LPCTSTR LopaniFile);
	};

	// 输出控件
	namespace OutputControl
	{
		// 进度条
		namespace Progress
		{
			IMAGE ProgressImage;

			void getlinestyle(LINESTYLE* pstyle)						// 获取当前画线样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::getlinestyle(pstyle);
				SetWorkingImage(CurDevice);
			}
			void setlinestyle(const LINESTYLE* pstyle)					// 设置当前画线样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setlinestyle(pstyle);
				SetWorkingImage(CurDevice);
			}
			void setlinestyle(int style, int thickness = 1, const DWORD *puserstyle = NULL, DWORD userstylecount = 0)	// 设置当前画线样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setlinestyle(style, thickness, puserstyle, userstylecount);
				SetWorkingImage(CurDevice);
			}

			void getfillstyle(FILLSTYLE* pstyle)						// 获取当前填充样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::getfillstyle(pstyle);
				SetWorkingImage(CurDevice);
			}
			void setfillstyle(const FILLSTYLE* pstyle)					// 设置当前填充样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setfillstyle(pstyle);
				SetWorkingImage(CurDevice);
			}
			void setfillstyle(int style, long hatch = NULL, PIMAGE ppattern = NULL)		// 设置当前填充样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setfillstyle(style, hatch, ppattern);
				SetWorkingImage(CurDevice);
			}
			void setfillstyle(BYTE* ppattern8x8)						// 设置当前填充样式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setfillstyle(ppattern8x8);
				SetWorkingImage(CurDevice);
			}
			
			COLORREF getlinecolor()				// 获取当前线条颜色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				COLORREF color = ::getlinecolor();
				SetWorkingImage(CurDevice);
				return color;
			}
			void setlinecolor(COLORREF color)	// 设置当前线条颜色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setlinecolor(color);
				SetWorkingImage(CurDevice);
			}
			COLORREF getfillcolor()				// 获取当前填充颜色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				COLORREF color = ::getfillcolor();
				SetWorkingImage(CurDevice);
				return color;
			}
			void setfillcolor(COLORREF color)	// 设置当前填充颜色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setfillcolor(color);
				SetWorkingImage(CurDevice);
			}
			COLORREF getbkcolor()				// 获取当前绘图背景色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				COLORREF color = ::getbkcolor();
				SetWorkingImage(CurDevice);
				return color;
			}
			void setbkcolor(COLORREF color)		// 设置当前绘图背景色
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setbkcolor(color);
				SetWorkingImage(CurDevice);
			}
			int  getbkmode()					// 获取背景混合模式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				int mode = ::getbkmode();
				SetWorkingImage(CurDevice);
				return mode;
			}
			void setbkmode(int mode)			// 设置背景混合模式
			{
				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);
				::setbkmode(mode);
				SetWorkingImage(CurDevice);
			}


#ifndef _USE_EASYXSHARP_DEPRECATED_FUNCTION
			_EASYX_FUN_DEPRECATED
#endif // !_USE_EASYXSHARP_DEPRECATED_FUNCTION
			const IMAGE & CircleProgressdraw(int Completed, int Whole, int Width = 100, int Height = 100)
			{
				static constexpr double π = 3.141592654;
				static IMAGE CircleProgressImage;
				if (Width == 0 && Height == 0)
				{
					Width = Height = 100;
				}
				if (Width == 0)
				{
					Width = Height;
				}
				else if (Height == 0)
				{
					Height = Width;
				}
				CircleProgressImage.Resize(Width, Height);
				if (Completed > Whole)
					Completed = Whole;

				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&CircleProgressImage);
				cleardevice();
				fillpie(0, 0, Width - 1, Height - 1, π / 2 - 2 * π * Completed / Whole, π / 2);

				SetWorkingImage(CurDevice);
				return CircleProgressImage;
			}
			const IMAGE & RectProgressdraw(int Completed, int Whole, int Width = 100, int Height = 20)
			{
				if (Width == 0 && Height == 0)
				{
					Width = 100;
					Height = 20;
				}
				if (Width == 0)
				{
					Width = 100;
				}
				else if (Height == 0)
				{
					Height = 20;
				}
				ProgressImage.Resize(Width, Height);
				if (Completed > Whole)
					Completed = Whole;

				PIMAGE CurDevice = GetWorkingImage();
				SetWorkingImage(&ProgressImage);

				cleardevice();
				solidrectangle(0, 0, Width * Completed / Whole, Height-1);
				rectangle(0, 0, Width - 1, Height - 1);

				SetWorkingImage(CurDevice);
				return ProgressImage;
			}
		}
	}
};

#undef _CRT_SECURE_NO_WARNINGS
#undef EASYX_FUN_DEPRECATED
#endif // !EASYX_SHARP_H