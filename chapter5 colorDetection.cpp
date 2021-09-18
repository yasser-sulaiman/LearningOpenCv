#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////////// Color Detection /////////////////////
void main() {
	String path = "resources/colored.jpg";
	Mat img = imread(path);
	Mat imgHSV, mask;
	// convert to hsv space
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	//lower limits
	int hmin = 0;
	int smin = 0;
	int vmin = 0;
	//upper limits
	int hmax = 179;
	int smax = 255;
	int vmax = 255;

	namedWindow("Track Bars", (500, 500));
	createTrackbar("HUE min", "Track Bars", &hmin, 179);
	createTrackbar("HUE max", "Track Bars", &hmax, 179);
	createTrackbar("Saturation min", "Track Bars", &smin, 255);
	createTrackbar("Saturation max", "Track Bars", &smax, 255);
	createTrackbar("Value min", "Track Bars", &vmin, 255);
	createTrackbar("Value max", "Track Bars", &vmax, 255);
	
	while (true) {
		Scalar lowerLimit(hmin, smin, vmin);
		Scalar upperLimit(hmax, smax, vmax);
		inRange(img, lowerLimit, upperLimit, mask);

		imshow("Image", img);
		imshow("HSV", imgHSV);
		imshow("Mask", mask);
		waitKey(1);
	}
}