#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
void bubblesort(int r[],int index[],int n)
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
		if(r[j]>r[j-1])  
		{
			flag=1;
			temp=r[j];
			r[j]=r[j-1];
			r[j-1]=temp;
			temp = index[j];
			index[j] = index[j-1];
			index[j-1] = temp;
		}
		i++;
	}
}
void GetNearestColor(unsigned char &B,unsigned char &G,unsigned char &R,int color[],int n)
{
	unsigned char b,g,r;
	B=B>>3;
	G=G>>3;
	R=R>>3;
	unsigned char result[3];
	float min = 32*3;
	float error=0;
	for(int i=0;i<n;i++)
	{
		b = color[i]/1024;
		g = (color[i]-color[i]/1024*1024)/32;
		r = (color[i]-color[i]/32*32);
	//	error = sqrt((float)(B-b)*(B-b)+(float)(G-g)*(G-g)+(float)(R-r)*(R-r));
		error = abs(B-b)+abs(G-g)+abs(R-r);
		if( min > error )
		{
			min = error;
			result[0] = b;
			result[1] = g;
			result[2] = r;
		}
	}
	B = result[0]*8;
	G = result[1]*8;
	R = result[2]*8;
}
void ColorQuantization_Popular(const unsigned char src_data[],unsigned char dst_data[],int dataSize)
{
	int i;
	int hist[32*32*32];
	int color[32*32*32];
	memset(hist,0,sizeof(int)*32*32*32);
	for (i = 0; i < 32*32*32; i++)
	{
		color[i] = i;
	}
	for (i = 0; i < dataSize; i+=3)
	{
		hist[(src_data[i]/8)*1024+(src_data[i+1]/8)*32+src_data[i+2]/8] ++;
	}
	bubblesort(hist,color,32*32*32);

	memcpy(dst_data,src_data,dataSize);
	for(i = 0; i < dataSize; i+=3)
	{
		GetNearestColor(dst_data[i],dst_data[i+1],dst_data[i+2],color,1000);
	}
}
int main( int argc, char** argv )
{
	Mat src, dst;
	char* source_window = "Source image";
	char* quantized_window= "quantized image";
	/// Load image
	src = imread( argv[1], -1 );
	if( !src.data )
	{ 
		cout<<"can not find source image"<<endl;
		return -1;
	}
	
	/// Apply ColorQuantization_Popular
	if(src.isContinuous())
	{
		src.copyTo(dst);
		ColorQuantization_Popular(src.data,dst.data,src.cols*src.rows*3);
		/// Display results
		namedWindow( source_window, CV_WINDOW_AUTOSIZE );
		namedWindow( quantized_window, CV_WINDOW_AUTOSIZE );
		imshow( source_window, src );
		imshow( quantized_window, dst );
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