
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


                                ////////// Video /////////
void main() {

    VideoCapture cap(0); // for webcam use numbers
    // define images that will be used
    Mat backGround, frame, imgHSV, mask, mask2, maskInv, newBackGround, newFrame;

    for (int i = 0; i <= 45; i++) {
        cap >> backGround;
    }

    while (true) {
        cap.read(frame);
        // convert to hsv space
        cvtColor(frame, imgHSV, COLOR_BGR2HSV);

        // define color ranges for red color
        // first range
        Scalar lowerLimit(0, 120, 70);
        Scalar upperLimit(10, 255, 255);
        // detecting the color and save the result to mask
        inRange(imgHSV, lowerLimit, upperLimit, mask);

        // second range
        Scalar lowerLimit2(170, 120, 70);
        Scalar upperLimit2(180, 255, 255);
        // detecting the color and save the result to mask
        inRange(imgHSV, lowerLimit2, upperLimit2, mask2);
        mask += mask2;
        
        // getting the inverse of the mask
        threshold(mask, maskInv, 20, 255, THRESH_BINARY_INV);

        // removing the detected color with a black region
        // using bitwise and operation
        cvtColor(maskInv, maskInv, COLOR_GRAY2BGR);
        bitwise_and(frame, maskInv, frame);

        // getting the removed region from the background image
        // using the bitwise and operation
        cvtColor(mask, mask, COLOR_GRAY2BGR);
        bitwise_and(backGround, mask, newBackGround);

        // replace the detected area with the area from the back ground
        newFrame = frame + newBackGround;
        //bitwise_or(frame, newBackGround, newFrame);

        //imshow("frame", frame);
        imshow("newFrame", newFrame);
        char pressedKey = waitKey(1);
        if (pressedKey == 'q') break;
    }
    cap.release();
}