#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	CascadeClassifier licenseClassifier;
	licenseClassifier.load("resources/haarcascade_russian_plate_number.xml");
	//check if the model has been loaded successfully
	if (licenseClassifier.empty()) { cout << "classifier not loaded" << endl; }

	Mat img = imread("resources/plate.jpg");
	vector<Rect> plates;
	licenseClassifier.detectMultiScale(img, plates, 1.1, 10);

	for (int i = 0; i < plates.size(); i++) {
		imshow(to_string(i), img(plates[i]));
		imwrite("resources/plate" + to_string(i) + ".jpg", img(plates[i]));
		rectangle(img, plates[i].tl(), plates[i].br(), Scalar(0, 255, 0), 2);
	}

	imshow("plate", img);
	waitKey(0);
	/*
	VideoCapture cap("resources/cars.mp4");
	Mat frame;
	vector<Rect> plates;

	while (true) {
		cap.read(frame);

		// detect faces and draw boxes around theim
		resize(frame, frame, Size(640, 480));
		licenseClassifier.detectMultiScale(frame, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++) {
			rectangle(frame, plates[i].tl(), plates[i].br(), Scalar(0, 255, 0), 2);
		}

		imshow("Image", frame);
		waitKey(1);
	}
	*/
}