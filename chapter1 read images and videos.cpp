
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


////////// Images /////////
/*
void main() {

    string image_path = "resources/elon.jpg";

    Mat image = imread(image_path, IMREAD_COLOR);

    //resize(image, image, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    imshow("Image", image);
    waitKey(0);

}*/

////////// Video /////////

void main() {

    string path = "resources/video.mp4";
    VideoCapture cap(path); // for webcam use numbers
    Mat frame;
    while (true) {
        cap.read(frame);
        imshow("frame", frame);
        waitKey(20);
    }


}