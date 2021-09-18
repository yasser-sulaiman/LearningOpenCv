
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


////////// Basic Functions /////////

void main() {

    string image_path = "resources/elon.jpg";

    Mat image = imread(image_path, IMREAD_COLOR);
    Mat imgResized, imgCroped, imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    // resize the image
    //image.size()
    //resize(image, imgResized, { 400, 600 }, 0, 0); // scaled to specific values of width and height
    resize(image, imgResized, Size(),0.5,0.5 ); // scaled to 0.5 of the original image

    // crop the image
    Rect roi(100, 100, 200, 200);
    imgCroped = image(roi);

    // convert to gray scale
    cvtColor(image, imgGray, COLOR_BGR2GRAY);

    // blur the image
    GaussianBlur(image, imgBlur, Size(5, 5), 5, 0);

    //edge detection (canny)
    Canny(imgBlur, imgCanny, 25, 125);

    // dialte image (increase thikness)
    Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDilate, kernal);

    // Erode image
    Mat kernalErode = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(imgDilate, imgErode, kernalErode);

    // show the images (decrease thikness)
    imshow("Image", image);
    imshow("Resized", imgResized);
    imshow("Croped", imgCroped);
    imshow("Gray", imgGray);
    imshow("Blur", imgBlur);
    imshow("Canny", imgCanny);
    imshow("Dilate", imgDilate);
    imshow("Erode", imgErode);

    waitKey(0);

}

