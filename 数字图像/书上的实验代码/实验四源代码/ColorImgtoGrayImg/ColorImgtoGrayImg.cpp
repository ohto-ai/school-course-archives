#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
void Color2Gray1(const unsigned char src_data[],unsigned char dst_data[],int dstDataSize)
{
	int i;
	for(i = 0; i < dstDataSize; ++i)
	{
		dst_data[i] = cvRound((src_data[i*3]+src_data[i*3+1]+src_data[i*3+2])/3);
	}
}
void Color2Gray2(const unsigned char src_data[],unsigned char dst_data[],int dstDataSize)
{
	int i;
	for(i = 0; i < dstDataSize; ++i)
	{
		dst_data[i] = cvRound(src_data[i*3]*0.114+src_data[i*3+1]*0.587+src_data[i*3+2]*0.299);
	}
}
void Color2Gray3(const unsigned char src_data[],unsigned char dst_data[],int dstDataSize)
{
	int i;
	for(i = 0; i < dstDataSize; ++i)
	{
		dst_data[i] = cvRound(src_data[i*3]*0.072+src_data[i*3+1]*0.7154+src_data[i*3+2]*0.2125);
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* gray_window1 = "gray image1";
	char* gray_window2 = "gray image2";
	char* gray_window3 = "gray_image3";
	/// Load image
	src = imread( argv[1], 1 );
	if( !src.data )
	{ 
		cout<<"can not find source image"<<endl;
		return -1;
	}
	namedWindow( source_window, CV_WINDOW_AUTOSIZE );
	imshow( source_window, src );
	/// Apply BrightenColor
	if(src.isContinuous())
	{
		dst = Mat::zeros( src.rows, src.cols, CV_8UC1);
		Color2Gray1(src.data,dst.data,src.cols*src.rows);
		namedWindow( gray_window1, CV_WINDOW_AUTOSIZE );
		imshow( gray_window1, dst );
		
		Color2Gray2(src.data,dst.data,src.cols*src.rows);
		namedWindow( gray_window2, CV_WINDOW_AUTOSIZE );
		imshow( gray_window2, dst );

		Color2Gray3(src.data,dst.data,src.cols*src.rows);
		namedWindow( gray_window3, CV_WINDOW_AUTOSIZE );
		imshow( gray_window3, dst );
	}
	else
	{ 
		cout<<"data is not continuous"<<endl;
		return -1;
	}

	/// Wait until user exits the program
	waitKey(0);
	return 0;
}