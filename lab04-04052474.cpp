#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("D:\\lab04_image\\lena.jpg", IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	cvtColor(src, src, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(src, dst);

	imshow("Source image", src);
	imshow("Equalized Image", dst);


	vector<Mat> gray_planes;
	split(src, gray_planes);
	float minVal = 0, maxVal = 0;

	minMaxLoc(&gray_planes[0], &minVal, &maxVal, NULL, NULL);
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	Mat gray_hist;
	int histSize = 256;
	calcHist(&gray_planes[0], 1, 0, Mat(), gray_hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
	for (int i = 1; i < histSize; i++)
	{

		rectangle(histImage, Point(bin_w*(i - 1), hist_h),
			Point(bin_w*(i-1), hist_h - cvRound(gray_hist.at<float>(i))), Scalar(255,0,0), CV_FILLED);
		
	}
	imshow("calcHist Demo", histImage);
	
	waitKey();
	return 0;
}
