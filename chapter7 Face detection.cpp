#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////////// Face Detection image /////////////////////
/*
void main() {
	String path = "resources/faces.jpg";
	Mat img = imread(path);

	CascadeClassifier faceClassifier;
	faceClassifier.load("resources/haarcascade_frontalface_default.xml");
	//check if the model has been loaded successfully
	if (faceClassifier.empty()) { cout << "classifier not loaded" << endl; }

	// detect faces and draw boxes around theim
	vector<Rect> faces;
	resize(img, img, Size(640, 480));
	faceClassifier.detectMultiScale(img, faces, 1.1, 10);
	
	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 2);
	}

	imshow("Image", img);
	waitKey(0);

}
*/

////////////////////// Face Detection Video /////////////////////

void main() {
	CascadeClassifier faceClassifier;
	faceClassifier.load("resources/haarcascade_frontalface_default.xml");
	//check if the model has been loaded successfully
	if (faceClassifier.empty()) { cout << "classifier not loaded" << endl; }

	VideoCapture cap(0);
	Mat frame;
	while (true) {
		cap.read(frame);

		// detect faces and draw boxes around theim
		vector<Rect> faces;
		resize(frame, frame, Size(640, 480));
		faceClassifier.detectMultiScale(frame, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++) {
			rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 2);
		}

		imshow("Image", frame);
		waitKey(1);

	}

	

	

}