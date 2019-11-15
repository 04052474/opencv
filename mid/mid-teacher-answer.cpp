#include <opencv2/opencv.hpp>  
#include <iostream>

using namespace cv;
using namespace std;

void Problem1(const String& filename) 
{
	Mat src = imread(filename);
	int B = src.at< Vec3b>(266, 266)[0];
	int G = src.at< Vec3b>(266, 266)[1];
	int R = src.at< Vec3b>(266, 266)[2];

	String text = "(" + to_string(B) + "," + to_string(G) + "," + to_string(R) + ")";
	putText(src, text, Point(100, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(B, G, R), 2, 8, 0);
	circle(src, Point(src.cols / 2, src.rows / 2), 50, Scalar(255, 0, 0), 2);
	imshow("Problem1", src);
}

void Problem2(const String& filename1, const String& filename2)
{
	Mat src1 = imread(filename1);
	Mat src2 = imread(filename2);

	for (int i = 0; i < src2.rows; i++)
		for (int j = 0; j < src2.cols; j++)
		{
			int B = src2.at<Vec3b>(i, j)[0];
			int G = src2.at<Vec3b>(i, j)[1];
			int R = src2.at<Vec3b>(i, j)[2];
			if ((B == 255 && G == 0 && R == 0) || (B == 0 && G == 255 && R == 0) || (B == 0 && G == 0 && R == 255))
			{
				src2.at<Vec3b>(i, j)[0] = src1.at<Vec3b>(i, j)[0];
				src2.at<Vec3b>(i, j)[1] = src1.at<Vec3b>(i, j)[1];
				src2.at<Vec3b>(i, j)[2] = src1.at<Vec3b>(i, j)[2];
			}
		}
	imshow("Problem2", src2);
}

void findROI(Mat &src, Rect &boundRect, Scalar color)
{
	int xMin = src.cols, xMax = -1, yMin = src.rows, yMax = -1;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar *p_src = src.ptr<uchar>(i, j);
			if ((p_src[0] == color[0]) && (p_src[1] == color[1]) && (p_src[2] == color[2]))
			{
				if (i <= yMin)
					yMin = i;
				if (i >= yMax)
					yMax = i;
				if (j <= xMin)
					xMin = j;
				if (j >= xMax)
					xMax = j;
			}
		}
	}
	if ((yMin <= yMax) && (xMin <= xMax)) {
		boundRect.x = xMin;
		boundRect.y = yMin;
		boundRect.width = xMax - xMin + 1;
		boundRect.height = yMax - yMin + 1;
	}
	else {
		boundRect = Rect(0, 0, 0, 0);
	}
}

void Problem3(const String& filename)
{
	Mat src = imread(filename);
	Rect boundRect;
	findROI(src, boundRect, Scalar(255, 0, 0));
	if (boundRect.width != 0 && boundRect.height != 0)
	{
		rectangle(src, boundRect.tl(), boundRect.br(), Scalar(0, 0, 0), 2, 8, 0);
	}
	findROI(src, boundRect, Scalar(0, 255, 0));
	if (boundRect.width != 0 && boundRect.height != 0)
	{
		rectangle(src, boundRect.tl(), boundRect.br(), Scalar(0, 0, 0), 2, 8, 0);
	}
	findROI(src, boundRect, Scalar(0, 0, 255));
	if (boundRect.width != 0 && boundRect.height != 0)
	{
		rectangle(src, boundRect.tl(), boundRect.br(), Scalar(0, 0, 0), 2, 8, 0);
	}
	imshow("Problem3", src);
}

void Problem4(const String& filename)
{
	Mat src = imread(filename);
	Mat hsv;
	cvtColor(src, hsv, CV_BGR2HSV);
	Mat sChannel(hsv.rows, hsv.cols, CV_8UC1);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			sChannel.at<uchar>(i, j) = hsv.ptr<uchar>(i, j)[1];
		}
	}

	Mat dst;
	Mat srcHist, dstHist;
	int histSize = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };
	equalizeHist(sChannel, dst);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			hsv.ptr<uchar>(i, j)[1] = dst.at<uchar>(i, j);
		}
	}
	cvtColor(hsv, dst, CV_HSV2BGR);
	imshow("Problem4", dst);
}

int main()
{
	Problem1("images\\lena.jpg");
	Problem2("images\\pic1.jpg", "images\\shape.png");
	Problem3("images\\shape.png");
	Problem4("images\\lena.jpg");
	waitKey(0);
	return 0;
}

