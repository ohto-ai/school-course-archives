#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
void BrightenColor(const unsigned char src_data[],unsigned char dst_data[],int dataSize,int bias)
{
	int i;
	unsigned char table[256];
	for (i = 0; i < 256; ++i)
	{
		table[i] = MAX(0,MIN(255, i + bias) );
	}
	for(i = 0; i < dataSize; ++i)
	{
		dst_data[i] = table[src_data[i]];
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* brightened_window = "Brightened Image";
	/// Load image
	src = imread( argv[1], 1 );
	if( !src.data )
	{ 
		cout<<"can not find source image"<<endl;
		return -1;
	}
	
	/// Apply BrightenColor
	if(src.isContinuous())
	{
		src.copyTo(dst);
		BrightenColor(src.data,dst.data,src.cols*src.rows*3,50);
		/// Display results
		namedWindow( source_window, CV_WINDOW_AUTOSIZE );
		namedWindow( brightened_window, CV_WINDOW_AUTOSIZE );
		imshow( source_window, src );
		imshow( brightened_window, dst );
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