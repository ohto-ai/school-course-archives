#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* hsv_h_window = "hsv_h";
	char* hsv_s_window = "hsv_s";
	char* hsv_v_window = "hsv_v";
	char* hls_h_window = "hls_h";
	char* hls_l_window = "hls_l";
	char* hls_s_window = "hls_s";
	char* lab_l_window = "lab_l";
	char* lab_a_window = "lab_a";
	char* lab_b_window = "lab_b";
	char* luv_l_window = "luv_l";
	char* luv_u_window = "luv_u";
	char* luv_v_window = "luv_v";
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
		vector<Mat> planes;
		//BGR2HSV
		cvtColor(src, dst, CV_BGR2HSV);
		split( dst, planes );
		namedWindow( hsv_h_window , CV_WINDOW_AUTOSIZE );
		imshow( hsv_h_window , planes[0] );
		namedWindow( hsv_s_window , CV_WINDOW_AUTOSIZE );
		imshow( hsv_s_window , planes[1] );
		namedWindow( hsv_v_window , CV_WINDOW_AUTOSIZE );
		imshow( hsv_v_window , planes[2] );
		//BGR2HLS
		cvtColor(src, dst, CV_BGR2HLS);
		split( dst, planes );
		namedWindow( hls_h_window , CV_WINDOW_AUTOSIZE );
		imshow( hls_h_window , planes[0] );
		namedWindow( hls_l_window , CV_WINDOW_AUTOSIZE );
		imshow( hls_l_window , planes[1] );
		namedWindow( hls_s_window , CV_WINDOW_AUTOSIZE );
		imshow( hls_s_window , planes[2] );
		//BGR2Lab
		cvtColor(src, dst, CV_BGR2Lab);
		split( dst, planes );
		namedWindow( lab_l_window , CV_WINDOW_AUTOSIZE );
		imshow( lab_l_window , planes[0] );
		namedWindow( lab_a_window , CV_WINDOW_AUTOSIZE );
		imshow( lab_a_window , planes[1] );
		namedWindow( lab_b_window , CV_WINDOW_AUTOSIZE );
		imshow( lab_b_window , planes[2] );
		//BGR2Luv
		cvtColor(src, dst, CV_BGR2Luv);
		split( dst, planes );
		namedWindow( luv_l_window , CV_WINDOW_AUTOSIZE );
		imshow( luv_l_window , planes[0] );
		namedWindow( luv_u_window , CV_WINDOW_AUTOSIZE );
		imshow( luv_u_window , planes[1] );
		namedWindow( luv_v_window , CV_WINDOW_AUTOSIZE );
		imshow( luv_v_window , planes[2] );
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