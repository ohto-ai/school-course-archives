#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void ReverseColor(const Mat * src,Mat & dst)
{
	src->copyTo(dst);
	int nRows = src->rows;
	int nCols = src->cols;
	if (src->isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i,j;
	const uchar *p;
	uchar *q;
	const int channels = src->channels();
	switch(channels)
	{
		case 1:
			{
				for( i = 0; i < nRows; ++i)
				{
					p = (*src).ptr<uchar>(i);
					q = dst.ptr<uchar>(i);
					for ( j = 0; j < nCols; ++j)
						q[j] = ~p[j];
				}
				break;
			}
		case 3:
			{
				for( i = 0; i < nRows; ++i)
				{
					p = (*src).ptr<uchar>(i);
					q = dst.ptr<uchar>(i);
					for ( j = 0; j < nCols*3; ++j)
						q[j] = ~p[j];
				}
			}
	}
}
void ReverseColor(const unsigned char src_data[],unsigned char dst_data[],int dataSize)
{
	int i;
	const unsigned char *p=src_data;
	unsigned char *q=dst_data;
	for(i=0;i<dataSize;i++)
		*q++ = ~(*p++);
}

void ReverseColor_LUT_OpenCV(const Mat * src,Mat & dst,uchar table[])
{
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for( int i = 0; i < 256; ++i)
		p[i] = table[i];
	LUT(*src, lookUpTable, dst);
}
void ReverseColor_LUT(const Mat * src,Mat & dst,uchar table[])
{
	src->copyTo(dst);
	int nRows = src->rows;
	int nCols = src->cols;
	if (src->isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i,j;
	const uchar *p;
	uchar *q;
	const int channels = src->channels();
	switch(channels)
	{
		case 1:
			{
				for( i = 0; i < nRows; ++i)
				{
					p = (*src).ptr<uchar>(i);
					q = dst.ptr<uchar>(i);
					for ( j = 0; j < nCols; ++j)
						q[j] = table[p[j]];
				}
				break;
			}
		case 3:
			{
				for( i = 0; i < nRows; ++i)
				{
					p = (*src).ptr<uchar>(i);
					q = dst.ptr<uchar>(i);
					for ( j = 0; j < nCols*3; ++j)
						q[j] = table[p[j]];
				}
			}
	}
}
void ReverseColor_LUT(const unsigned char src_data[],unsigned char dst_data[],int dataSize,unsigned char table[])
{
	int i;
	const unsigned char *p=src_data;
	unsigned char *q=dst_data;
	for(i=0;i<dataSize;i++)
		*q++ = table[*p++];
}
/**
 * @function main
 */
int main( int argc, char** argv )
{
	Mat src, dst;

	src = imread( argv[1], CV_LOAD_IMAGE_COLOR );

	if( !src.data )
		return -1;
	if(src.depth() != CV_8U) // enum { CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6 }
		return -1;
    namedWindow( "src image", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "src image", src );                   // Show our image inside it.

	ReverseColor(&src,dst);
	namedWindow( "method1", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "method1", dst );                   // Show our image inside it.

	if(src.isContinuous())
	{
		src.copyTo(dst);
		ReverseColor(src.data,dst.data,src.cols*src.rows*3);
		namedWindow( "method2", CV_WINDOW_AUTOSIZE );// Create a window for display.
		imshow( "method2", dst );                   // Show our image inside it.
	}
	
	unsigned char table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = ~((unsigned char)i);

	ReverseColor_LUT_OpenCV(&src,dst,table);
	namedWindow( "LUT_method1", CV_WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "LUT_method1", dst );                   // Show our image inside it.

	ReverseColor_LUT(&src,dst,table);
	namedWindow( "LUT_method2", CV_WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "LUT_method2", dst );                   // Show our image inside it.

	if(src.isContinuous())
	{
		src.copyTo(dst);
		ReverseColor_LUT(src.data,dst.data,src.cols*src.rows*3,table);
		namedWindow( "LUT_method3", CV_WINDOW_AUTOSIZE );// Create a window for display.
		imshow( "LUT_method3", dst );                   // Show our image inside it.
	}

	waitKey(0);

	return 0;
}
