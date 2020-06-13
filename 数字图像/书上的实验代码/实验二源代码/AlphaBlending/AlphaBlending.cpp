#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
/// Global Variables
const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;
/// Matrices to store images
Mat src1;
Mat src2;
Mat dst;
/**
* @function on_trackbar
* @brief Callback for trackbar
*/
void on_trackbar( int, void* )
{
	alpha = (double) alpha_slider/alpha_slider_max ;
	beta = ( 1.0 - alpha );
//	addWeighted( src1, alpha, src2, beta, 0.0, dst);
	dst.create(src1.rows,src1.cols,CV_8UC3);
	if(src1.isContinuous()&&src2.isContinuous()&&dst.isContinuous())
	{
		unsigned char *s1,*s2,*d;
		for(s1 = src1.data,s2 = src2.data,d=dst.data;d<dst.dataend;s1++,s2++,d++)
			*d = (*s1) * alpha + (*s2) * beta;
	}
	imshow( "Linear Blend", dst );
}
int main( int argc, char** argv )
{
	/// Read image ( same size, same type )
	src1 = imread("../../images/LinuxLogo.jpg",CV_LOAD_IMAGE_COLOR);
	src2 = imread("../../images/WindowsLogo.jpg",CV_LOAD_IMAGE_COLOR);
	if( !src1.data ) { printf("Error loading src1 \n"); return -1; }
	if( !src2.data ) { printf("Error loading src2 \n"); return -1; }
	if(src1.depth() != CV_8U || src2.depth() != CV_8U) // enum { CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6 }
		return -1;
	if(src1.rows != src2.rows || src1.cols != src2.cols)
		return -1;
	/// Initialize values
	alpha_slider = 0;
	/// Create Windows
	namedWindow("Linear Blend", 1);
	/// Create Trackbars
	char TrackbarName[50];
	sprintf( TrackbarName, "Alpha %d", alpha_slider_max );
	createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
	/// Show some stuff
	on_trackbar( alpha_slider, 0 );
	/// Wait until user press some key
	waitKey(0);
	return 0;
}