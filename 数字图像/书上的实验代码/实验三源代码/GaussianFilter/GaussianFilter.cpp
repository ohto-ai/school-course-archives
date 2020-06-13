#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

void GaussianFilter(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows,double sigma)
{
	int i,j,m,n;
	float sum=0;
	int center = (int)(3 * sigma);
	int length = 2*center+1;
	float* kernel = new float[length];
	double sigma2 = sigma*sigma;
	for(i = 0;i<length;i++)
	{
		double r = center - i;
		kernel[i] = (float)(exp(-0.5*r*r/sigma2));
		sum+=kernel[i];
	}
	for(i = 0;i<length;i++)
	{
		kernel[i] /= sum;
	}
	unsigned char *tmp = new unsigned char[rows*cols];
	memcpy(tmp,src_data,rows*cols);
	for(i = 0; i < rows; ++i)
	{
		for(j = center; j < cols - center; ++j)
		{
			sum = 0;
			for(n=-center; n <= center;++n)
			{
				sum += src_data[i*cols+j+n]*kernel[n+center];
			}
			tmp[i*cols+j] = cvRound(sum);
		}
	}
	for(i = center; i < rows - center; ++i)
	{
		for(j = 0; j < cols; ++j)
		{
			sum = 0;
			for(m=-center; m <= center;++m)
			{
				sum+=tmp[(i+m)*cols+j]*kernel[m+center];
			}
			dst_data[i*cols+j] = cvRound(sum);
		}
	}
	delete tmp;
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* gaussian_window1 = "gaussian Image1";
	char* gaussian_window2 = "gaussian Image2";

	/// Load image
	src = imread( "../../images/lena.png", CV_LOAD_IMAGE_GRAYSCALE );
	if( !src.data )
	{ 
		cout<<"not find source image"<<endl;
		return -1;
	}
	namedWindow( source_window, CV_WINDOW_AUTOSIZE );
	imshow(source_window, src );
	if(src.isContinuous())
	{
		src.copyTo(dst);
		/// Apply guassian filter sigma = 2
		double t = (double)getTickCount();
		GaussianFilter(src.data,dst.data,src.cols,src.rows,2);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( gaussian_window1 , CV_WINDOW_AUTOSIZE );
		imshow(gaussian_window1 , dst );

		src.copyTo(dst);
		/// Apply guassian filter sigma = 5
		t = (double)getTickCount();
		GaussianFilter(src.data,dst.data,src.cols,src.rows,5);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( gaussian_window2 , CV_WINDOW_AUTOSIZE );
		imshow(gaussian_window2 , dst );
	}

	/// Wait until user exits the program
	waitKey(0);
	return 0;
}