#include "pch.h"
#include "EasyXSharp.h"

#pragma region EasyXSharpFunctionDefinition

using namespace EasyXSharp;

// ����ͼ

void SpriteImage::Load(LPCTSTR ImgFile, int SrcImageRows, int SrcImageCols, int SpriteImageCols, int UseImageNum)					// ��ͼƬ�ļ���ȡͼ��(bmp/gif/jpg/png/tif/emf/wmf/ico
{
	IMAGE WholeImage;
	IMAGE SingleSprite;
	IMAGE* CurImage = GetWorkingImage();
	int SpriteWidth;
	int SpriteHeight;

	if (SrcImageRows <= 0)
		SrcImageRows = 1;
	if (SrcImageCols <= 0)
		SrcImageCols = 1;
	if (UseImageNum <= 0)
		UseImageNum = SrcImageRows * SrcImageCols;
	if (SpriteImageCols <= 0)
		SpriteImageCols = SrcImageCols;

	::loadimage(&WholeImage, ImgFile);
	SpriteWidth = WholeImage.getwidth() / SrcImageCols;
	SpriteHeight = WholeImage.getheight() / SrcImageRows;

	SpriteCols = SpriteImageCols;

	SetWorkingImage(&WholeImage);

	Table.clear();
	for (int i = 0; i < SrcImageRows; ++i)
	{
		for (int j = 0; j < SrcImageCols && i * SrcImageCols + j < UseImageNum; ++j)
		{
			::getimage(&SingleSprite, j * SpriteWidth, i * SpriteHeight, SpriteWidth, SpriteHeight);
			Table.push_back(SingleSprite);
		}
	}
	SetWorkingImage(CurImage);
}

void SpriteImage::Load(LPCTSTR ResType, LPCTSTR ResName, int SrcImageRows, int SrcImageCols, int SpriteImageCols, int UseImageNum)	// ����Դ�ļ���ȡͼ��(bmp/gif/jpg/png/tif/emf/wmf/ico)
{
	IMAGE WholeImage;
	IMAGE SingleSprite;
	IMAGE* CurImage = GetWorkingImage();
	int SpriteWidth;
	int SpriteHeight;

	if (SrcImageRows <= 0)
		SrcImageRows = 1;
	if (SrcImageCols <= 0)
		SrcImageCols = 1;
	if (UseImageNum <= 0)
		UseImageNum = SrcImageRows * SrcImageCols;
	if (SpriteImageCols <= 0)
		SpriteImageCols = SrcImageCols;

	::loadimage(&WholeImage, ResType, ResName);
	SpriteWidth = WholeImage.getwidth() / SrcImageCols;
	SpriteHeight = WholeImage.getheight() / SrcImageRows;

	SpriteCols = SpriteImageCols;

	SetWorkingImage(&WholeImage);

	Table.clear();
	for (int i = 0; i < SrcImageRows; ++i)
	{
		for (int j = 0; j < SrcImageCols && i * SrcImageCols + j < UseImageNum; ++j)
		{
			::getimage(&SingleSprite, j * SpriteWidth, i * SpriteHeight, SpriteWidth, SpriteHeight);
			Table.push_back(SingleSprite);
		}
	}
	SetWorkingImage(CurImage);
}

void SpriteImage::Load(const IMAGE& WholeImage, int SrcImageRows, int SrcImageCols, int SpriteImageCols, int UseImageNum)						// ��ͼƬ���ؾ���ͼ
{
	IMAGE SingleSprite;
	IMAGE* CurImage = GetWorkingImage();
	int SpriteWidth;
	int SpriteHeight;

	if (SrcImageRows <= 0)
		SrcImageRows = 1;
	if (SrcImageCols <= 0)
		SrcImageCols = 1;
	if (UseImageNum <= 0)
		UseImageNum = SrcImageRows * SrcImageCols;
	if (SpriteImageCols <= 0)
		SpriteImageCols = SrcImageCols;

	SpriteWidth = WholeImage.getwidth() / SrcImageCols;
	SpriteHeight = WholeImage.getheight() / SrcImageRows;

	SpriteCols = SpriteImageCols;

	SetWorkingImage((IMAGE*)(&WholeImage));

	Table.clear();
	for (int i = 0; i < SrcImageRows; ++i)
	{
		for (int j = 0; j < SrcImageCols && i * SrcImageCols + j < UseImageNum; ++j)
		{
			::getimage(&SingleSprite, j * SpriteWidth, i * SpriteHeight, SpriteWidth, SpriteHeight);
			Table.push_back(SingleSprite);
		}
	}
	SetWorkingImage(CurImage);
}

// �Ƴ�ָ��֡
void SpriteImage::Erase(int from, int to)
{
	for (auto it = Table.begin() + from; it != Table.begin() + to;)
	{
		it = Table.erase(it);
	}
}
// ����ͼ��ߴ�
void SpriteImage::Resize(int width, int height)	// ����ÿ��ͼ���С
{
	for (auto& sprite : Table)
	{
		sprite.Resize(width, height);
	}
}
// ����ͼ��
void SpriteImage::Zoom(int width, int height)	// ����ÿ��ͼ��
{
	for (auto& sprite : Table)
	{
		ZoomAlgorithm::Zoom(sprite, width, height);
	}
}

#pragma endregion

IMAGE& EasyXSharp::ZoomAlgorithm::ZoomNearestInterpolation(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)
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

	size_t SrcRowOff;
	size_t DstRowOff;
	size_t DstX, DstY;

	for (DstY = 0; DstY < DstHeight; ++DstY)
	{
		// ���������ƫ��
		SrcRowOff = (DstY * SrcHeight / DstHeight) * SrcWidth;
		DstRowOff = DstY * DstWidth;
		for (DstX = 0; DstX < DstWidth; ++DstX)
		{
			// ӳ�䵽ԭͼ
			// SrcX = DstX * SrcWidth / DstWidth;
			// SrcY = DstY * SrcHeight / DstHeight;
			DstBuff[DstX + DstRowOff] = SrcBuff[DstX * SrcWidth / DstWidth + SrcRowOff];
		}
	}
	return  Dst;
}

IMAGE& EasyXSharp::ZoomAlgorithm::ZoomNearestInterpolation(IMAGE& Dst, size_t DstWidth, size_t DstHeight)
{
	IMAGE Src(Dst);
	return  ZoomNearestInterpolation(Dst, Src, DstWidth, DstHeight);

}

IMAGE& EasyXSharp::ZoomAlgorithm::ZoomBilinearInterpolation_i(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)	//�����͡�
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
		// ���������ƫ��
		size_t RemY = DstY * SrcHeight % DstWidth;
		size_t SrcY1 = DstY * SrcHeight / DstWidth;
		size_t SrcY2 = RemY > 0 ? SrcY1 + 1 : SrcY1;
		size_t DstRowOff = DstY * DstWidth;
		size_t SrcRowOff = SrcY1 * SrcWidth;

		if (SrcY1 >= SrcHeight)
			SrcY1 = SrcHeight - 1;
		if (SrcY2 >= SrcHeight)
			SrcY2 = SrcHeight - 1;

		for (DstX = 0; DstX < DstWidth; ++DstX)
		{
			// ӳ�䵽ԭͼ		
			size_t RemX = DstX * SrcWidth % DstWidth;
			size_t SrcX1 = DstX * SrcWidth / DstWidth;
			size_t SrcX2 = RemX > 0 ? SrcX1 + 1 : SrcX1;

			// ���㸨�����ʽ
			size_t ExpX = RemX * DstWidth;
			size_t ExpY = RemY * DstWidth;
			size_t RemX_Y = RemX * RemY;
			size_t SquDstWidth = DstWidth * DstWidth;
			size_t Exp11 = SquDstWidth - ExpX - ExpY + RemX_Y;
			size_t Exp12 = ExpY - RemX_Y;
			size_t Exp21 = ExpX - RemX_Y;
			size_t Exp22 = RemX_Y;

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

			R = (R11 * Exp11
				 + R12 * Exp12
				 + R21 * Exp21
				 + R22 * Exp22) / SquDstWidth;
			G = (G11 * Exp11
				 + G12 * Exp12
				 + G21 * Exp21
				 + G22 * Exp22) / SquDstWidth;
			B = (B11 * Exp11
				 + B12 * Exp12
				 + B21 * Exp21
				 + B22 * Exp22) / SquDstWidth;

			DstBuff[DstX + DstRowOff] = RGB(R, G, B);
		}
	}
	return  Dst;
}

IMAGE& EasyXSharp::ZoomAlgorithm::ZoomBilinearInterpolation_i_s(IMAGE& Dst, const IMAGE& Src, size_t DstWidth, size_t DstHeight)	//������|������ݷ�Χ��
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
		// ���������ƫ��
		size_t RemY = DstY * SrcHeight % DstWidth;
		size_t SrcY1 = DstY * SrcHeight / DstWidth;
		size_t SrcY2 = RemY > 0 ? SrcY1 + 1 : SrcY1;
		size_t DstRowOff = DstY * DstWidth;
		size_t SrcRowOff = SrcY1 * SrcWidth;

		for (DstX = 0; DstX < DstWidth; ++DstX)
		{
			// ӳ�䵽ԭͼ		
			size_t RemX = DstX * SrcWidth % DstWidth;
			size_t SrcX1 = DstX * SrcWidth / DstWidth;
			size_t SrcX2 = RemX > 0 ? SrcX1 + 1 : SrcX1;

			// ���㸨�����ʽ
			size_t ExpX = RemX * DstWidth;
			size_t ExpY = RemY * DstWidth;
			size_t RemX_Y = RemX * RemY;
			size_t SquDstWidth = DstWidth * DstWidth;
			size_t Exp11 = SquDstWidth - ExpX - ExpY + RemX_Y;
			size_t Exp12 = ExpY - RemX_Y;
			size_t Exp21 = ExpX - RemX_Y;
			size_t Exp22 = RemX_Y;

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

			R = (R11 * Exp11
				 + R12 * Exp12
				 + R21 * Exp21
				 + R22 * Exp22) / SquDstWidth;
			G = (G11 * Exp11
				 + G12 * Exp12
				 + G21 * Exp21
				 + G22 * Exp22) / SquDstWidth;
			B = (B11 * Exp11
				 + B12 * Exp12
				 + B21 * Exp21
				 + B22 * Exp22) / SquDstWidth;

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
