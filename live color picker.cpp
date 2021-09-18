#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////////// Color Detection /////////////////////
void main() {
	VideoCapture cap(0);
	Mat img;
	Mat imgHSV, mask;

	//lower limits
	int hmin = 90;
	int smin = 85;
	int vmin = 186;
	//upper limits
	int hmax = 130;
	int smax = 120;
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

		cap.read(img);
		// convert to hsv space
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		inRange(img, lowerLimit, upperLimit, mask);

		imshow("Image", img);
		//imshow("HSV", imgHSV);
		imshow("Mask", mask);
		waitKey(1);
	}
}