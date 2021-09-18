#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////////// Shape Detection /////////////////////

void getContours(Mat imgSrc, Mat imgDst) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//draw all contours
	//drawContours(imgDst, contours, -1, Scalar(0, 0, 0), 5);
	
	// filtering according to contour's area
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundBoxs(contours.size());
	String objecType;

	for (int i = 0; i < contours.size() ; i++) {

		float area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//draw contours
			//drawContours(imgDst, contours, i, Scalar(0, 0, 0), 5);
			//drawContours(imgDst, conPoly, i, Scalar(0, 0, 0), 5);
			//cout << conPoly[i].size() << endl;
			
			// finding and drawing bounding boxes
			boundBoxs[i] = boundingRect(conPoly[i]);
			rectangle(imgDst, boundBoxs[i].tl(), boundBoxs[i].br(), Scalar(0, 255, 0), 2);
			
			if (conPoly[i].size() == 3) { objecType = "Triangle"; }
			if (conPoly[i].size() == 4) { 
				float aspectRatio = (float) boundBoxs[i].width / (float) boundBoxs[i].height;
				cout <<"aspect ratio: "<< aspectRatio << endl;
				if (aspectRatio > 0.95 && aspectRatio < 1.05){ objecType = "Square"; }
				else { objecType = "rectangle"; }
			}
			if (conPoly[i].size() == 5) { objecType = "pentagon"; }
			if (conPoly[i].size() > 5) { objecType = "Circle or some polygon"; }
			
			putText(imgDst, objecType, { boundBoxs[i].x, boundBoxs[i].y -5},FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1);

		}
	}
}

void main() {
	String path = "resources/colored.jpg";
	Mat img = imread(path);

	// preprocessing the image
	Mat imgGray, imgBlur, imgCanny, imgDilate;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDilate, kernal);

	//get and draw contours
	getContours(imgDilate, img);


	imshow("Image", img);
	imshow("Dilate", imgDilate);
	waitKey(0);
	
}