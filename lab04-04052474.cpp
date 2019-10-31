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

	//minMaxLoc(&gray_planes[0], &minVal, &maxVal, NULL, NULL);
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	Mat src_hist;
	Mat dst_hist;
	int histSize = 256;
	calcHist(&src, 1, 0, Mat(), src_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&dst, 1, 0, Mat(), dst_hist, 1, &histSize, &histRange, uniform, accumulate);

	Point minsrc, maxsrc;
	minMaxLoc(src_hist, 0, 0, &minsrc, &maxsrc);
	Point mindst, maxdst;
	minMaxLoc(dst_hist, 0, 0, &mindst, &maxdst);

	int hist_w = 256, hist_h = 300;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
	Mat equalization_histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	normalize(src_hist, src_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(dst_hist, dst_hist, 0, equalization_histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{

		line(histImage, Point(bin_w*(i), hist_h - cvRound(src_hist.at<float>(i))),
		Point(bin_w*(i), hist_h),
		Scalar(255, 0, 0), 1, 8, 0);//hist_h - cvRound(src_hist.at<float>(i)會這樣減可能是因為圖是從左上角0,0開始畫
		line(equalization_histImage, Point(bin_w*(i), hist_h - cvRound(dst_hist.at<float>(i))),
			Point(bin_w*(i), hist_h),
			Scalar(255, 0, 0), 1, 8, 0);
	}
	imshow("calcHist Demo", histImage);
	imshow("equalization_histImage Demo", equalization_histImage);
	waitKey();
	return 0;
}
