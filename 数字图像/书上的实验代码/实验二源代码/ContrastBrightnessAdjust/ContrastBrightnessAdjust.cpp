#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
void ContrastBrightnessAdjust(const Mat * src,Mat & dst,float factor, float bias)
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
					{
						float tmp = (p[j]-128)*factor+128+bias;
						if(tmp > 255)
							tmp = 255;
						else if(tmp < 0)
							tmp = 0;
						else{}
						q[j] = cvRound(tmp);
					}
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
					{
						float tmp = (p[j]-128)*factor+128+bias;
						if(tmp > 255)
							tmp = 255;
						else if(tmp < 0)
							tmp = 0;
						else{}
						q[j] = cvRound(tmp);
					}
				}
			}
	}
	
}
void ContrastBrightnessAdjust(const unsigned char src_data[],unsigned char dst_data[],int dataSize,float factor, float bias)
{
	int i;
	const unsigned char *p=src_data;
	unsigned char *q=dst_data;
	for(i=0;i<dataSize;i++)
	{
		*q++ = cvRound(MAX(0,MIN((*p-128)*factor+128+bias,255)));
		p++;
	}
}
void AutoConstrastBrightnessAdjust_GrayImg(const unsigned char src_data[],unsigned char dst_data[],int dataSize)
{
	int i;
	const unsigned char *p=src_data;
	unsigned char *q=dst_data;
	unsigned char min=255,max=0;
	for(i=0;i<dataSize;i++)
	{
		if(src_data[i]<min)
			min = src_data[i];
		if(src_data[i]>max)
			max = src_data[i];
	}
	for(i=0;i<dataSize;i++)
	{
		*q++ = cvRound(MAX(0,MIN((*p-min)*(255.0/(max-min)),255)));
		p++;
	}
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
    namedWindow( "src1 img", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "src1 img", src );                   // Show our image inside it.

	ContrastBrightnessAdjust(&src,dst,2.0, 0);
	namedWindow( "method1(2.0,0)", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "method1(2.0,0)", dst );                   // Show our image inside it.

	ContrastBrightnessAdjust(&src,dst,2.0, -100);
	namedWindow( "method1(2.0,-100)", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "method1(2.0,-100)", dst );                   // Show our image inside it.

	if(src.isContinuous())
	{
		src.copyTo(dst);
		ContrastBrightnessAdjust(src.data,dst.data,src.cols*src.rows*3,2.0,0);
		namedWindow( "method2(2.0,0)", CV_WINDOW_AUTOSIZE );// Create a window for display.
		imshow( "method2(2.0,0)", dst );                   // Show our image inside it.
		ContrastBrightnessAdjust(src.data,dst.data,src.cols*src.rows*3,2.0,-100);
		namedWindow( "method2(2.0,-100)", CV_WINDOW_AUTOSIZE );// Create a window for display.
		imshow( "method2(2.0,-100)", dst );                   // Show our image inside it.
	}
	src = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
	namedWindow( "src2 img", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "src2 img", src );                   // Show our image inside it.
	if(src.isContinuous())
	{
		src.copyTo(dst);
		AutoConstrastBrightnessAdjust_GrayImg(src.data,dst.data,src.cols*src.rows);
		namedWindow( "AutoMethod", CV_WINDOW_AUTOSIZE );// Create a window for display.
		imshow( "AutoMethod", dst );                   // Show our image inside it.
	}

	waitKey(0);

	return 0;
}
