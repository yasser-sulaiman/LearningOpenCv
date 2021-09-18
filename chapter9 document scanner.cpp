#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


////////// document scanner /////////
Mat imgGray, imgBlur, imgThresh, imgCanny, imgDilate, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

Mat preProcessing(Mat img) {
    // convert to gray scale
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    // blur the image
    GaussianBlur(img, imgBlur, Size(5, 5), 5, 0);
    //edge detection (canny)
    Canny(imgBlur, imgCanny, 25, 125);
    // dialte image (increase thikness)
    Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDilate, kernal);
    return imgDilate;
}


vector<Point> getContours(Mat imgSrc, Mat imgDst) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundBoxs(contours.size());

    vector<Point> biggest;
    float maxArea = 0;

    for (int i = 0; i < contours.size(); i++) {
        float area = contourArea(contours[i]);
        cout << area << endl;
        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            //drawContours(imgDst, conPoly, i, Scalar(0, 0, 0), 2);

            if (area > maxArea and conPoly[i].size() == 4) {
                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                maxArea = area;
            }
           
            //rectangle(imgDst, boundBoxs[i].tl(), boundBoxs[i].br(), Scalar(0, 255, 0), 2);
        }
    }
    return biggest;
}


void drawPoints(Mat imgDst, vector<Point> points, Scalar color) {
    for (int i = 0; i < points.size(); i++) {
        circle(imgDst, points[i], 20, color, FILLED);
        putText(imgDst, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 2);
    }
}


vector<Point> reOrder(vector<Point> points) {

    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;
    for (int i = 0; i < 4; i++) {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

    return newPoints;
}


Mat getWarp(Mat img, vector<Point> points, float w, float h) {
  
    Point2f src[4] = { points[0], points[1], points[2], points[3] };
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

    Mat matrix, warpedImage;
    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, warpedImage, matrix, Point(w, h));

    return warpedImage;
}


void main() {

    string image_path = "resources/pass.jpg";

    Mat image = imread(image_path, IMREAD_COLOR);
    //resize(image, image, Size(), 0.4,0.4);
    
    // preprocessing
    imgThresh = preProcessing(image);

    // get biggest contour
    initialPoints=getContours(imgThresh, image);
    //drawPoints(image, initialPoints, Scalar(255, 0, 0));
    docPoints = reOrder(initialPoints);
    //drawPoints(image, docPoints, Scalar(255, 0, 0));

    // wrap
    float w = 420, h = 596;
    imgWarp = getWarp(image, docPoints, w, h);

    // crop
    int cropValue = 5;
    Rect roi(cropValue, cropValue, w - 2 * cropValue, h - 2 * cropValue);
    imgCrop = imgWarp(roi);

    imshow("Image", image);
    imshow("pre processed image", imgThresh);
    imshow("Warped", imgWarp);
    imshow("Croped", imgCrop);
    waitKey(0);

}