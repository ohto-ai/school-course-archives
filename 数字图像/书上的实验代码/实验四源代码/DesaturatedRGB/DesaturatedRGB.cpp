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
Mat src;
Mat dst;
/**
* @function on_trackbar
* @brief Callback for trackbar
*/
void on_trackbar( int, void* )
{
	alpha = (double) alpha_slider/alpha_slider_max ;
	beta = ( 1.0 - alpha );
	src.copyTo(dst);
	if(src.isContinuous()&&dst.isContinuous())
	{
		unsigned char *s,*d;
		for(s = src.data,d=dst.data;d<dst.dataend;s+=3,d+=3)
		{
			double y = (*s)*0.114+(*(s+1))*0.587+(*(s+2))*0.299;
			*d = cvRound(alpha*y+beta*(*s));
			*(d+1) = cvRound(alpha*y+beta*(*(s+1)));
			*(d+2) = cvRound(alpha*y+beta*(*(s+2)));
		}
	}
	imshow( "DesaturatedRGB", dst );
}
int main( int argc, char** argv )
{
	/// Read image ( same size, same type )
	src = imread("../../images/baboon.jpg",1);
	if( !src.data ) { printf("Error loading src \n"); return -1; }
	/// Initialize values
	alpha_slider = 0;
	/// Create Windows
	namedWindow("DesaturatedRGB", 1);
	/// Create Trackbars
	char TrackbarName[50];
	sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
	createTrackbar( TrackbarName, "DesaturatedRGB", &alpha_slider, alpha_slider_max, on_trackbar );
	/// Show some stuff
	on_trackbar( alpha_slider, 0 );
	/// Wait until user press some key
	waitKey(0);
	return 0;
}