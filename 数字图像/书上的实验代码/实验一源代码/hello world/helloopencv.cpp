#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

void DrawHist(const string& winname,Mat & b_hist,Mat & g_hist,Mat &r_hist,int histSize)
{
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			Scalar( 255, 0, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
	}
	/// Display
	namedWindow(winname, CV_WINDOW_AUTOSIZE );
	imshow(winname, histImage );
}

void main(int argc,char** argv)
{
	Mat src,dst;
	Mat hist,hist1,hist2;
	src = imread(argv[1],0);
	hist = Mat::zeros(1,256,CV_32F);
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			((float*)(hist.data))[src.at<uchar>(i,j)]++;
			//hist.at<float>(src.at<uchar>(i,j))++;
		}
	}
	cvNamedWindow("src");
	imshow("src",src);
	hist.copyTo(hist1);
	hist.copyTo(hist2);
	cvNamedWindow("12");
	DrawHist("12",hist,hist1,hist2,256);


	cvWaitKey(0);
}