#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{

	cv::Mat frame = imread("E:\\PIC\\m.png");
	cv::Mat SobelMat1;
	cv::Mat SobelMat2;
	cv::Mat cannyMat;
	Sobel(frame, SobelMat1, CV_16SC1, 1, 0, 3);
	Sobel(frame, SobelMat2, CV_16SC1, 0, 1, 3);
	Canny(SobelMat1, SobelMat2, cannyMat, 90, 140);
	//Canny(frame, cannyMat, 50, 200, 3);
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(cannyMat, lines, 1, CV_PI / 180,100);
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for ( ;it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		line(frame, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}
	imshow("frame", frame);
	imshow("canny", cannyMat);
	waitKey();
}