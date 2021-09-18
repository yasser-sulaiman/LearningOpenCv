#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
  ////////////////////// Draw Shapes /////////////////////
void main() {
	// Blank image
	//Scalar function takes B, G, R values as argument
	Mat blank(512, 512, CV_8UC3, Scalar(255,255,255));

	//draw a circle
	circle(blank, Point(256, 256), 100, Scalar(0, 255, 255), FILLED);

	// draw a rectangle
	rectangle(blank, Point(50, 50), Point(150, 150), Scalar(255, 0, 0), 10);

	// draw a line
	line(blank, Point(50, 280), Point(250, 280), Scalar(0, 255, 0), 5);

	//Put Text on an image
	putText(blank, "Hello World", Point(50, 380), FONT_HERSHEY_COMPLEX, 5, Scalar(0, 0, 255), 2);


	imshow("Blank", blank);
	waitKey(0);
}