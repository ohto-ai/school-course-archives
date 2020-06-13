#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

void bubblesort(int r[],int n)
{ 
	/*elements are stored in r[0] to r[n-1]*/
	int i,j,flag;
	int temp;
	flag=1;
	i=0;
	while((i<n-1)&&(flag==1))
	{  
		flag=0;
		for(j=n-1;j>i;j--)
		if(r[j]<r[j-1])  
		{
			flag=1;
			temp=r[j];
			r[j]=r[j-1];
			r[j-1]=temp;
		}
		i++;
	}
}

//9*9 media filter
void mediaFilter(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows)
{
	int i,j,m,n;
	int tmp[81];
	for(i = 4; i < rows - 4; ++i)
	{
		for(j = 4; j < cols - 4; ++j)
		{
			for(m=-4; m <= 4;++m)
			{
				for(n=-4; n <= 4;++n)
				{
					tmp[(m+4)*9+n+4] = src_data[(i+m)*cols+j+n];
				}
			}
			bubblesort(tmp,81);
			dst_data[i*cols+j] = tmp[40];
		}
	}
}
//9*9 media filter by splitted way
void mediaFilter_Split(const unsigned char src_data[],unsigned char dst_data[],int cols,int rows)
{
	int i,j,m,n;
	unsigned char *dst_data_tmp = new unsigned char[cols*rows];
	memcpy(dst_data_tmp,src_data,cols*rows);
	int tmp[9];
	for(i = 4; i < rows - 4; ++i)
	{
		for(j = 0; j < cols; ++j)
		{
			for(m=-4; m <= 4;++m)
			{
				tmp[m+4] = src_data[(i+m)*cols+j];
			}
			bubblesort(tmp,9);
			dst_data_tmp[i*cols+j] = tmp[4];
		}
	}
	for(i = 0; i < rows; ++i)
	{
		for(j = 4; j < cols - 4; ++j)
		{
			for(n=-4; n <= 4;++n)
			{
				tmp[n+4] = dst_data_tmp[i*cols+j+n];
			}
			bubblesort(tmp,9);
			dst_data[i*cols+j] = tmp[4];
		}
	}
	delete dst_data_tmp;
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* media_window1 = "Media image1";
	char* media_window2 = "Media image2";

	/// Load image
	src = imread( "../../images/lena256gray.png", CV_LOAD_IMAGE_GRAYSCALE );
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
		/// Apply 9*9 media filter
		double t = (double)getTickCount();
		mediaFilter(src.data,dst.data,src.cols,src.rows);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( media_window1 , CV_WINDOW_AUTOSIZE );
		imshow(media_window1 , dst );

		/// Apply 9*9 media filter by splitted way
		src.copyTo(dst);
		t = (double)getTickCount();
		mediaFilter_Split(src.data,dst.data,src.cols,src.rows);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in seconds: " << t << endl;
		/// Display results
		namedWindow( media_window2 , CV_WINDOW_AUTOSIZE );
		imshow(media_window2, dst );
	}

	/// Wait until user exits the program
	waitKey(0);
	return 0;
}