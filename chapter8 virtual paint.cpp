#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<vector<int>> myPoints;
Mat frame;
vector<vector<int>> myColors { {90,85,186,130,120,255}, // pink
								{85,154,26,136,239,172} }; // green

vector<Scalar> myColorValues{ {255,0,255}, // purple
									{0,255,0} }; // green

Point getContours(Mat imgSrc, Mat imgDst) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundBoxs(contours.size());

	Point mypoint;

	for (int i = 0; i < contours.size(); i++) {
		float area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundBoxs[i] = boundingRect(conPoly[i]);

			mypoint.x = boundBoxs[i].x + boundBoxs[i].width / 2;
			mypoint.y = boundBoxs[i].y;
			drawContours(imgDst, conPoly, i, Scalar(0, 0, 0), 2);
			rectangle(imgDst, boundBoxs[i].tl(), boundBoxs[i].br(), Scalar(0, 255, 0), 2);
		}
	}
	return mypoint;
}

vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;

	// convert to hsv space
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	for (int i=0; i < myColors.size(); i++) {
		Scalar lowerLimit(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upperLimit(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(img, lowerLimit, upperLimit, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask, img);
		if (myPoint.x != 0 and myPoint.y != 0) {
			myPoints.push_back({ myPoint.x, myPoint.y, i });
		}
		
	}
	return myPoints;
}

void drawOnCanvas(vector<vector<int>> myPoints, vector<Scalar> myColorValues) {
	for (int i = 0; i < myPoints.size(); i++) {
		circle(frame,Point(myPoints[i][0], myPoints[i][1]), 10, myColorValues[myPoints[i][2]], FILLED);
	}
}

void main() {
	VideoCapture cap(0);

	while (true) {
		cap.read(frame);
		myPoints = findColor(frame);
		drawOnCanvas(myPoints, myColorValues);

		imshow("Video from WebCam", frame);
		waitKey(1);
	}

}