#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void drawBox(Mat& img, Point2f points[4], Scalar color, int thikness=2) {
	for (int i = 0; i < 4; i++) {
		circle(img, points[i], 5, color, FILLED);
	}
	line(img, points[0], points[1], color, thikness);
	line(img, points[0], points[2], color, thikness);
	line(img, points[1], points[3], color, thikness);
	line(img, points[2], points[3], color, thikness);
}

////////////////////// Warp Perspectives /////////////////////
void main() {
	String path = "resources/cards.png";
	Mat img = imread(path);
	//resize(img, img, Size(680, 480));
	// cordinates of the card's corners
	// upper left -> upper right -> lower left -> lower right
	//source
	Point2f src[4] = { {414,107}, {481,66}, {525,171}, {594,132} };
	//destination
	float w = 150, h = 200;
	Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

	Mat matrix, imgWarp;
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	// marking the points of intrest
	/*Scalar Color(0, 255, 0);
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 5, Color, FILLED);
	}*/
	Scalar Color(0, 255, 255);
	drawBox(img, src, Color,2);
	imshow("Image", img);
	imshow("Warp", imgWarp);
	waitKey(0);
}