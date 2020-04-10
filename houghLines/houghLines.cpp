#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat cannyMat;
	cv::Mat binMat = cv::imread("D:\\Files\\metal-part-distorted-03.png", 0);
	cv::Mat srcMat = cv::imread("D:\\Files\\metal-part-distorted-03.png");//读取图像
	//检测图像读取是否成功
	if (srcMat.empty())
	{
		return -1;
	}
	//用Canny算子进行边缘检测
	cv::Canny(binMat, cannyMat, 100, 250, 3);
	cv::imshow("canny", cannyMat);
	//进行霍夫变换
	cv::Mat lineMat;
	cv::HoughLines(cannyMat, lineMat, 1, CV_PI / 180, 42);
	//绘制直线
	for (int i = 0; i < lineMat.rows; i++)
	{
		float rho = lineMat.at<Vec2f>(i, 0)[0], theta = lineMat.at<Vec2f>(i, 0)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (-b));
		cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
		//显示结果
		cv::imshow("dst", srcMat);
		cv::imshow("canny", cannyMat);
	}
	waitKey(0);
}