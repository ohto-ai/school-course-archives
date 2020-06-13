#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
/// Global Variables
const int slider_h_max = 360;
const int slider_h_center = 180;
int slider_h;
const int slider_s_max = 510;
const int slider_s_center = 255;
int slider_s;
const int slider_v_max = 510;
const int slider_v_center = 255;
int slider_v;
/// Matrices to store images
Mat src;
Mat hsv;
Mat hsv_current;
Mat dst;

void on_trackbar_h( int, void* )
{
	unsigned char *p,*q;
	if(hsv_current.isContinuous()&&hsv.isContinuous())
	{
		for(p=hsv_current.data,q=hsv.data;p<hsv_current.dataend;p+=3,q+=3)
		{
			*p = MAX(0,MIN(255,(*q)+(slider_h-slider_h_center)/2));
		}
	}
	cvtColor(hsv_current, dst, CV_HSV2BGR);
	imshow( "H_adjust", dst );
	imshow( "S_adjust", dst );
	imshow( "V_adjust", dst );
}
void on_trackbar_s( int, void* )
{
	unsigned char *p,*q;
	if(hsv_current.isContinuous()&&hsv.isContinuous())
	{
		for(p=hsv_current.data,q=hsv.data;p<hsv_current.dataend;p+=3,q+=3)
		{
			*(p+1) = MAX(0,MIN(255,(*(q+1))+slider_s-slider_s_center));
		}
	}
	cvtColor(hsv_current, dst, CV_HSV2BGR);
	imshow( "H_adjust", dst );
	imshow( "S_adjust", dst );
	imshow( "V_adjust", dst );
}
void on_trackbar_v( int, void* )
{
	unsigned char *p,*q;
	if(hsv_current.isContinuous()&&hsv.isContinuous())
	{
		for(p=hsv_current.data,q=hsv.data;p<hsv_current.dataend;p+=3,q+=3)
		{
			*(p+2) = MAX(0,MIN(255,(*(q+2))+slider_v-slider_v_center));
		}
	}
	cvtColor(hsv_current, dst, CV_HSV2BGR);
	imshow( "H_adjust", dst );
	imshow( "S_adjust", dst );
	imshow( "V_adjust", dst );
}
int main( int argc, char** argv )
{
	/// Read image ( same size, same type )
	src = imread("../../images/baboon.jpg",1);
	if( !src.data ) { printf("Error loading src \n"); return -1; }
	/// Initialize values
	cvtColor(src, hsv, CV_BGR2HSV);
	hsv.copyTo(hsv_current);
	slider_h = slider_h_center;
	slider_s = slider_s_center;
	slider_v = slider_v_center;
	/// Create Windows
	namedWindow("H_adjust", 1);
	namedWindow("S_adjust", 1);
	namedWindow("V_adjust", 1);
	/// Create Trackbars
	char TrackbarName[50];
	sprintf( TrackbarName, "h  %d", slider_h_max );
	createTrackbar( TrackbarName, "H_adjust", &slider_h, slider_h_max, on_trackbar_h );
	/// Show some stuff
	on_trackbar_h( slider_h, 0 );

	/// Create Trackbars
	sprintf( TrackbarName, "s  %d", slider_s_max );
	createTrackbar( TrackbarName, "S_adjust", &slider_s, slider_s_max, on_trackbar_s );
	/// Show some stuff
	on_trackbar_s( slider_s, 0 );

	/// Create Trackbars
	sprintf( TrackbarName, "v  %d", slider_v_max );
	createTrackbar( TrackbarName, "V_adjust", &slider_v, slider_v_max, on_trackbar_v );
	/// Show some stuff
	on_trackbar_v( slider_v, 0 );

	/// Wait until user press some key
	waitKey(0);
	return 0;
}