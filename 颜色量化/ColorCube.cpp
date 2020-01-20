#include "ColorCube.h"
#include <Windows.h>
#include <fstream>


// 测试范围异常
#ifdef  _DEBUG
#define ASSERT_CUBE	\
if (bBegin > bEnd\
	|| gBegin > gEnd\
	|| rBegin > rEnd)\
	throw std::bad_exception();
#else
#define ASSERT_CUBE
#endif //  

// 初始化为256*256*256的三维数组
std::vector<std::vector<std::vector<size_t>>> thatboy::ColorCube::colorHist(256, std::vector<std::vector<size_t>>(256, std::vector<size_t>(256, 0)));
std::list<thatboy::ColorCube> thatboy::ColorCube::colorCubeSet;
std::vector<thatboy::ColorCube::ColorType> thatboy::ColorCube::colorTable;
cv::Mat thatboy::ColorCube::srcImage;

bool thatboy::ColorCube::doSplitCube(int channel)
{
	switch (channel)
	{
	case 0:
	{
		// b
		if (bBegin == bEnd)
			break;
		size_t curSize = 0;
		size_t lastSize;
		for (size_t b = bBegin; b <= bEnd; b++)
		{
			lastSize = curSize;
			for (size_t g = gBegin; g <= gEnd; g++)
				for (size_t r = rBegin; r <= rEnd; r++)
					curSize += colorHist[b][g][r];
			if (curSize >= size / 2)
			{
				if (lastSize > size - curSize)// 分给左侧
					--b;
				// 产生新的空间，计算位置和数量
				// 修改本空间的B结束位置和数量
				ColorCube newCube(b + 1, gBegin, rBegin, bEnd, gEnd, rEnd);
				bEnd = b;
				newCube.reshapeCube();
				colorCubeSet.push_back(newCube);
				reshapeCube();
				return true;
			}
		}
	}
	break;
	case 1:
	{
		// g
		if (gBegin == gEnd)
			break;
		size_t curSize = 0;
		size_t lastSize;
		for (size_t g = gBegin; g <= gEnd; g++)
		{
			lastSize = curSize;
			for (size_t b = bBegin; b <= bEnd; b++)
				for (size_t r = rBegin; r <= rEnd; r++)
					curSize += colorHist[b][g][r];
			if (curSize >= size / 2)
			{
				if (lastSize > size - curSize)// 分给左侧
					--g;
				// 产生新的空间，计算位置和数量
				// 修改本空间的B结束位置和数量
				ColorCube newCube(bBegin, g + 1, rBegin, bEnd, gEnd, rEnd);
				gEnd = g;
				newCube.reshapeCube();
				colorCubeSet.push_back(newCube);
				reshapeCube();
				return true;
			}
		}
	}
	break;
	case 2:
	{
		// r
		if (rBegin == rEnd)
			break;
		size_t curSize = 0;
		size_t lastSize;
		for (size_t r = rBegin; r <= rEnd; r++)
		{
			lastSize = curSize;
			for (size_t b = bBegin; b <= bEnd; b++)
				for (size_t g = gBegin; g <= gEnd; g++)
					curSize += colorHist[b][g][r];
			if (curSize >= size / 2)
			{
				if (lastSize > size - curSize)// 分给左侧
					--r;
				// 产生新的空间，计算位置和数量
				// 修改本空间的B结束位置和数量
				ColorCube newCube(bBegin, gBegin, r + 1, bEnd, gEnd, rEnd);
				rEnd = r;
				newCube.reshapeCube();
				colorCubeSet.push_back(newCube);
				reshapeCube();
				return true;
			}
		}
	}
	break;

	default:
		break;
	}
	return false;
}

void thatboy::ColorCube::reshapeCube()
{
    BYTE bMin = bEnd, bMax = bBegin;
    BYTE gMin = gEnd, gMax = gBegin;
    BYTE rMin = rEnd, rMax = rBegin;
#ifdef _DEBUG
	// 查看内容变化
	BYTE oribEnd = bEnd, oribBegin = bBegin;
	BYTE origEnd = gEnd, origBegin = gBegin;
	BYTE orirEnd = rEnd, orirBegin = rBegin;
#endif // 

    size = 0;
    for (size_t b = bBegin; b <= bEnd; b++)
    {
        for (size_t g = gBegin; g <= gEnd; g++)
        {
            for (size_t r = rBegin; r <= rEnd; r++)
            {
                size += colorHist[b][g][r];
                if (colorHist[b][g][r] > 0)
                {
                    if (b < bMin)
                        bMin = b;
					else if (b > bMax)
                        bMax = b;

                    if (g < gMin)
                        gMin = g;
					else if (g > gMax)
                        gMax = g;

                    if (r < rMin)
                        rMin = r;
					else if (r > rMax)
                        rMax = r;
                }
            }
        }
    }
   bBegin = bMin, bEnd = bMax;
   gBegin = gMin, gEnd = gMax;
   rBegin = rMin, rEnd = rMax;

   ASSERT_CUBE
}

bool thatboy::ColorCube::splitBrotherCube()
{
	BYTE length[3] = { bEnd - bBegin, gEnd - gBegin, rEnd - rBegin };
	auto channel = length[0] > length[1] ? length[0] > length[2] ? 0 : 2 : length[1] > length[2] ? 1 : 2;

	return doSplitCube(channel);

	//if (calcSplitCube(channel))
	//	return true;
	////length[channel] = 0;
	//if (calcSplitCube(channel))
	//	return true;
	//length[channel] = 0;
	//return calcSplitCube(channel);
}

void thatboy::ColorCube::calacCubeColor()
{
    size_t bSum = 0, gSum = 0, rSum = 0, count = 0;

    for (size_t b = bBegin; b <= bEnd; b++)
    {
        for (size_t g = gBegin; g <= gEnd; g++)
        {
            for (size_t r = rBegin; r <= rEnd; r++)
            {
                count += colorHist[b][g][r];
                bSum += b * colorHist[b][g][r];
                gSum += g * colorHist[b][g][r];
                rSum += r * colorHist[b][g][r];
            }
        }
    }
#ifdef _DEBUG
	if (count == 0)
		throw std::bad_exception();
#endif // 

    bSum /= count;
    gSum /= count;
    rSum /= count;

	cubeColor = ColorType(bSum, gSum, rSum);
}

void thatboy::ColorCube::splitCube(size_t cubeNumber)
{
    while (colorCubeSet.size() < cubeNumber) {
        colorCubeSet.sort();

		auto iter = colorCubeSet.rbegin();
		while (iter != colorCubeSet.rend())	// 不断尝试分裂
			if (iter->splitBrotherCube())
				break;
			else 
				++iter;
		if (iter == colorCubeSet.rend())	// 找不到可以分裂的空间
			break;
       // std::max_element(colorCubeSet.begin(), colorCubeSet.end())->splitBrotherCube();// 
    }
	colorCubeSet.sort();

	colorTable.clear();
	colorTable.reserve(colorCubeSet.size());
	for (auto& cube : colorCubeSet)
	{
		cube.calacCubeColor();
		colorTable.push_back(cube.cubeColor);
		for (size_t b = cube.bBegin; b <= cube.bEnd; b++)
			for (size_t g = cube.gBegin; g <= cube.gEnd; g++)
				for (size_t r = cube.rBegin; r <= cube.rEnd; r++)
					colorHist[b][g][r] = colorTable.size() - 1;
	}
}

void thatboy::ColorCube::write8bIndexBmp(std::string fileName)
{
    std::ofstream ofs(fileName, std::ios::binary);
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER bmpHeader;
	int nWidth = srcImage.cols;
	int nHeight = srcImage.rows;
	int nRowSize = (nWidth + 3) / 4 * 4;
	std::vector<BYTE> rowBuff(nRowSize, 0);		// 行缓存，已补0
	auto imageBuff = srcImage.ptr<ColorType>();
	std::vector<COLORREF> palatte(256, 0);


    // 文件头   
    fileHeader.bfType = ((WORD)('M' << 8) | 'B');
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fileHeader.bfSize = fileHeader.bfOffBits + nRowSize * nHeight + 1024;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;

    ofs.write((LPCSTR)&fileHeader, sizeof(fileHeader));

    // 图像信息头
    bmpHeader.biSize = 40;
    bmpHeader.biWidth = nWidth;
    bmpHeader.biHeight = -nHeight;
    bmpHeader.biPlanes = 1;
    bmpHeader.biBitCount = 8;
    bmpHeader.biCompression = 0;
    bmpHeader.biSizeImage = 0;
    bmpHeader.biXPelsPerMeter = 0;
    bmpHeader.biYPelsPerMeter = 0;
    bmpHeader.biClrUsed = 0;
    bmpHeader.biClrImportant = 0;

    ofs.write((LPCSTR)&bmpHeader, sizeof(bmpHeader));

    // 调色板 防止颜色不足导致内存异常
	for (size_t i = 0; i < colorTable.size() && i < 256; i++)
		palatte[i] = *(DWORD*)&colorTable[i];
	ofs.write((LPCSTR)palatte.data(), 1024);
	

	for (size_t i = 0; i < nHeight; i++)
	{
		// 行缓存
		for (size_t j = 0; j < nWidth; j++)
			rowBuff[j] = static_cast<BYTE>(mappingPtr(imageBuff[i * nWidth + j]));
		ofs.write((LPCSTR)rowBuff.data(), nRowSize);
	}
    ofs.close();
}

void thatboy::ColorCube::loadImage(const cv::Mat src_image)
{
	srcImage = src_image.clone();
	// 清零
	for (auto& val : colorHist)
		for (auto& val : val)
			for (auto& val : val)
				val = 0;
	colorCubeSet.clear();
	colorTable.clear();

	// 统计
	for (auto iter = srcImage.begin<ColorType>(); iter != srcImage.end<ColorType>(); iter++)
		++colorHist[(*iter)[0]][(*iter)[1]][(*iter)[2]];

	colorCubeSet.push_back(ColorCube(0, 0, 0, 255, 255, 255));
	colorCubeSet.front().reshapeCube();
}