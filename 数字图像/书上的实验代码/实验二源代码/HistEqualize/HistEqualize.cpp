#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

void HistEqualize(const unsigned char src_data[],unsigned char dst_data[],int dataSize)
{
	int i;
	float hist[256];
	memset(hist,0,256*sizeof(float));
	for(i=0;i<dataSize;i++)
	{
		hist[src_data[i]] ++ ;
	}
	unsigned char table[256];
	float sum=0;
	for (i = 0; i < 256; ++i)
	{
		sum += hist[i];
		table[i] = cvFloor(sum * 255 / dataSize);
	}
	for(i = 0; i < dataSize; ++i)
	{
		dst_data[i] = table[src_data[i]];
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	int dstCn = 1;
	char* source_window = "Source image";
	char* equalized_window = "Equalized Image Method1";
	/// Load image
	src = imread( argv[1], CV_LOAD_IMAGE_COLOR );
	if( !src.data )
	{ 
		cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
		return -1;
	}
	if(src.depth() != CV_8U) // enum { CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6 }
		return -1;
	/// Convert to grayscale and channel is 1
	cvtColor( src, src, CV_BGR2GRAY,dstCn );
	/// Apply Histogram Equalization
	equalizeHist( src, dst );
	/// Display results
	namedWindow( source_window, CV_WINDOW_AUTOSIZE );
	namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );
	imshow( source_window, src );
	imshow( equalized_window, dst );

	////////////////////////////////////////////////////////////
	if(src.isContinuous())
	{
		src.copyTo(dst);
		HistEqualize(src.data,dst.data,src.cols*src.rows);
		/// Display results
		namedWindow( "Equalized Image Method2", CV_WINDOW_AUTOSIZE );
		imshow("Equalized Image Method2", dst );
	}

	/// Wait until user exits the program
	waitKey(0);
	return 0;
}