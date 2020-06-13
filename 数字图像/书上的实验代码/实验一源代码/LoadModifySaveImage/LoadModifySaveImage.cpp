#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

int main( int argc, char** argv )
{
	char* imageName = argv[1];

	Mat image;
	image = imread( imageName, CV_LOAD_IMAGE_COLOR );

	if( argc != 2 || !image.data )
	{
	printf( " No image data \n " );
	return -1;
	}

	Mat gray_image;
	cvtColor( image, gray_image, CV_RGB2GRAY,1);

	imwrite( "../../images/Gray_Image.jpg", gray_image );

	namedWindow( imageName, CV_WINDOW_AUTOSIZE );
	namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

	imshow( imageName, image );
	imshow( "Gray image", gray_image );

	waitKey(0);

	return 0;
}