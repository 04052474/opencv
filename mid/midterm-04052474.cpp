#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>   // std::cout
#include <string> 
using namespace std;
using namespace cv;
int main()
{
	Mat lena = imread("D:\\mid_image\\lena.jpg");

	if (!lena.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	std::string text = "(" + std::to_string(lena.at<Vec3b>(266, 266)[0]) + "," + std::to_string(lena.at<Vec3b>(266, 266)[1]) + "," + std::to_string(lena.at<Vec3b>(266, 266)[2]) + ")";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 2;
	int baseline = 0;
	Point textOrg(100, 50);
	putText(lena, text, textOrg, fontFace, fontScale, Scalar(lena.at<Vec3b>(266, 266)[0], lena.at<Vec3b>(266, 266)[1], lena.at<Vec3b>(266, 266)[2]), thickness, 8, 0);

	Point center((lena.cols) / 2, (lena.rows) / 2);
	circle(lena, center, 50, Scalar(255, 0, 0), 2);
	namedWindow("Problem1", CV_WINDOW_NORMAL);
	imshow("Problem1", lena);
	/*....................¤À¹j........................*/
	Mat pic1 = imread("D:\\mid_image\\pic1.jpg", IMREAD_COLOR);
	Mat pic2 = imread("D:\\mid_image\\shape.png", IMREAD_UNCHANGED);
	for (int i = 0; i < pic1.rows; i++)
		for (int j = 0; j < pic1.cols; j++)
		{
			if ((pic2.at<Vec3b>(i, j)[0] == 255 && pic2.at<Vec3b>(i, j)[1] == 0 && pic2.at<Vec3b>(i, j)[2] == 0)
				|| (pic2.at<Vec3b>(i, j)[0] == 0 && pic2.at<Vec3b>(i, j)[1] == 255 && pic2.at<Vec3b>(i, j)[2] == 0)
				|| (pic2.at<Vec3b>(i, j)[0] == 0 && pic2.at<Vec3b>(i, j)[1] == 0 && pic2.at<Vec3b>(i, j)[2] == 255))
			{
				pic2.at<Vec3b>(i, j)[0] = pic1.at<Vec3b>(i, j)[0];
				pic2.at<Vec3b>(i, j)[1] = pic1.at<Vec3b>(i, j)[1];
				pic2.at<Vec3b>(i, j)[2] = pic1.at<Vec3b>(i, j)[2];
			}
		}

	namedWindow("Problem2", CV_WINDOW_NORMAL);
	imshow("Problem2", pic2);
	/*....................¤À¹j........................*/
	Mat shape_image = imread("D:\\mid_image\\shape.png", IMREAD_UNCHANGED);

	int minx_blue = 1000;
	int miny_blue = 1000;
	int maxx_blue = 0;
	int maxy_blue = 0;
	int minx_green = 1000;
	int miny_green = 1000;
	int maxx_green = 0;
	int maxy_green = 0;
	int minx_red = 1000;
	int miny_red = 1000;
	int maxx_red = 0;
	int maxy_red = 0;
	for (int i = 0; i < shape_image.rows; i++)
		for (int j = 0; j < shape_image.cols; j++)
		{
			if (shape_image.at<Vec3b>(i, j)[0] == 255 && shape_image.at<Vec3b>(i, j)[1] == 0 && shape_image.at<Vec3b>(i, j)[2] == 0)
			{
				if (minx_blue > j)
				{
					minx_blue = j;
				}
				if (miny_blue > i)
				{
					miny_blue = i;
				}

				if (maxx_blue < j)
				{
					maxx_blue = j;
				}
				if (maxy_blue < i)
				{
					maxy_blue = i;
				}
			}
			if (shape_image.at<Vec3b>(i, j)[0] == 0 && shape_image.at<Vec3b>(i, j)[1] == 255 && shape_image.at<Vec3b>(i, j)[2] == 0)
			{
				if (minx_green > j)
				{
					minx_green = j;
				}
				if (miny_green > i)
				{
					miny_green = i;
				}

				if (maxx_green < j)
				{
					maxx_green = j;
				}
				if (maxy_green < i)
				{
					maxy_green = i;
				}
			}
			if (shape_image.at<Vec3b>(i, j)[0] == 0 && shape_image.at<Vec3b>(i, j)[1] == 0 && shape_image.at<Vec3b>(i, j)[2] == 255)
			{
				if (minx_red > j)
				{
					minx_red = j;
				}
				if (miny_red > i)
				{
					miny_red = i;
				}

				if (maxx_red < j)
				{
					maxx_red = j;
				}
				if (maxy_red < i)
				{
					maxy_red = i;
				}
			}

		}
	rectangle(shape_image, Point(minx_blue, miny_blue), Point(maxx_blue, maxy_blue), Scalar(0, 0, 0), 2);
	rectangle(shape_image, Point(minx_green, miny_green), Point(maxx_green, maxy_green), Scalar(0, 0, 0), 2);
	rectangle(shape_image, Point(minx_red, miny_red), Point(maxx_red, maxy_red), Scalar(0, 0, 0), 2);
	namedWindow("Problem3", CV_WINDOW_NORMAL);
	imshow("Problem3", shape_image);
	/*....................¤À¹j........................*/
	Mat lena2 = imread("D:\\mid_image\\lena.jpg");
	Mat lena2_hsvImg;
	cvtColor(lena2, lena2_hsvImg, CV_BGR2HSV);

	vector<Mat> channels(3);
	split(lena2_hsvImg, channels);
	// get the S channel
	//Mat S = channels[1];
	Mat dst;
	equalizeHist(channels[1], dst);
	Mat equalize_HSV;
	std::vector<cv::Mat> HSVchannels;
	HSVchannels.push_back(channels[0]);
	HSVchannels.push_back(dst);
	HSVchannels.push_back(channels[2]);
	merge(HSVchannels, equalize_HSV);
	cvtColor(equalize_HSV, equalize_HSV, CV_HSV2BGR);
	namedWindow("Problem4", CV_WINDOW_NORMAL);
	imshow("Problem4", equalize_HSV);
	waitKey(0);

	return 0;
}
