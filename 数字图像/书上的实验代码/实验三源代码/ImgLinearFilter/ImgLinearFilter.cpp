#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

//7*9 box filter
void BoxFilter(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows)
{
	int i,j,m,n,sum;
	for(i = 3; i < rows - 3; ++i)
	{
		for(j = 4; j < cols - 4; ++j)
		{
			sum = 0;
			for(m=-3; m <= 3;++m)
			{
				for(n=-4; n <= 4;++n)
				{
					sum+=src_data[(i+m)*cols+j+n];
				}
			}
			dst_data[i*cols+j] = cvRound(sum / 63.0);
		}
	}
}
//7*9 box filter by splitted way
void BoxFilter_Split(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows)
{
	int i,j,m,n,sum;
	unsigned char *dst_data_tmp = new unsigned char[cols*rows];
	memcpy(dst_data_tmp,src_data,cols*rows);
	for(i = 3; i < rows - 3; ++i)
	{
		for(j = 0; j < cols; ++j)
		{
			sum = 0;
			for(m=-3; m <= 3;++m)
			{
				sum+=src_data[(i+m)*cols+j];
			}
			dst_data_tmp[i*cols+j] = cvRound(sum / 7.0);
		}
	}
	for(i = 0; i < rows; ++i)
	{
		for(j = 4; j < cols - 4; ++j)
		{
			sum = 0;
			for(n=-4; n <= 4;++n)
			{
				sum+=dst_data_tmp[i*cols+j+n];
			}
			dst_data[i*cols+j] = cvRound(sum / 9.0);
		}
	}
	delete dst_data_tmp;
}
//5*5 weighted avg filter
void WeightedAvgFilter(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows)
{
	int i,j,m,n,sum;
	int weight[5][5] = {1, 2, 3, 2, 1,
						2, 5, 6, 5, 2, 
						3, 6, 8, 6, 3,
						2, 5, 6, 5, 2, 
						1, 2, 3, 2, 1};
	float alpha = 0;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			alpha += weight[i][j];
	}
	for(i = 2; i < rows - 2; ++i)
	{
		for(j = 2; j < cols - 2; ++j)
		{
			sum = 0;
			for(m=-2; m <= 2;++m)
			{
				for(n=-2; n <= 2;++n)
				{
					sum+=src_data[(i+m)*cols+j+n]*weight[m+2][n+2];
				}
			}
			dst_data[i*cols+j] = cvRound(sum/alpha);
		}
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* avg_window1 = "avg Image1";
	char* avg_window2 = "avg Image2";
	char* avg_window_weighted = "weighted avg Image";

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
		/// Apply 7*9 box filter
		double t = (double)getTickCount();
		BoxFilter(src.data,dst.data,src.cols,src.rows);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( avg_window1 , CV_WINDOW_AUTOSIZE );
		imshow(avg_window1 , dst );

		/// Apply 7*9 box filter by splitted way
		src.copyTo(dst);
		t = (double)getTickCount();
		BoxFilter_Split(src.data,dst.data,src.cols,src.rows);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( avg_window2 , CV_WINDOW_AUTOSIZE );
		imshow(avg_window2 , dst );

		/// Apply 5*5 weighted avg filter
		src.copyTo(dst);
		WeightedAvgFilter(src.data,dst.data,src.cols,src.rows);
		/// Display results
		namedWindow( avg_window_weighted , CV_WINDOW_AUTOSIZE );
		imshow(avg_window_weighted , dst );
	}

	/// Wait until user exits the program
	waitKey(0);
	return 0;
}