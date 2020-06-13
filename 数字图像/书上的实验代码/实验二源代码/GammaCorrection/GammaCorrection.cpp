#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
void GammaCorrection(const unsigned char src_data[],unsigned char dst_data[],int dataSize,double gamma)
{
	unsigned char table[256];
	for (int i = 0; i < 256; ++i)
	{
		table[i] = cvRound ( pow( (float)(i / 255.0) , (float)gamma) * 255 );
	}
	for(int i = 0; i < dataSize; ++i)
	{
		dst_data[i] = table[src_data[i]];
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	int dstCn = 1;
	char* source_window = "Source image";
	char* gamma_window = "GammaCorrected Image";
	/// Load image
	src = imread( argv[1], CV_LOAD_IMAGE_COLOR );
	if( !src.data )
	{ 
		cout<<"can not find source image"<<endl;
		return -1;
	}
	if(src.depth() != CV_8U) // enum { CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6 }
		return -1;
	/// Convert to grayscale and channel is 1
	cvtColor( src, src, CV_BGR2GRAY,dstCn );
	/// Apply GammaCorrection
	if(src.isContinuous())
	{
		dst.create(src.rows,src.cols,CV_8UC1);
		GammaCorrection(src.data,dst.data,src.cols*src.rows,1/1.7);
		/// Display results
		namedWindow( source_window, CV_WINDOW_AUTOSIZE );
		namedWindow( gamma_window, CV_WINDOW_AUTOSIZE );
		imshow( source_window, src );
		imshow( gamma_window, dst );
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