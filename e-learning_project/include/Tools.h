#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include "../include/markerdetection/PoseEstimation.h"
#include "../include/markerdetection/Marker.h"

using namespace cv;
using namespace std;

#define EX5 1
#define EX5_RAW 0
#define DRAW_CONTOUR 0
#define DRAW_RECTANGLE 0

#define THICKNESS_VALUE 4
// Struct for pose estimation variables
struct PoseVariables {
    int videoWidth;
    int videoHeight;
    float markerSize;
};

// Struct holding all infos about each strip, e.g. length
struct MyStrip {
    int stripeLength;
    int nStop;
    int nStart;
    Point2f stripeVecX;
    Point2f stripeVecY;
};
// List of points
typedef vector<Point> contour_t;
typedef vector<Point2f> contour_f;
// List of contours
typedef vector<contour_t> contour_vector_t;
typedef vector<contour_f> contour_vector_f;

/*
* Search for contours in an image. Only contours with 4 corners are extracted.
*
* @return vector all found contours
* @param image the image that is analyzed for contours
* @param drawImage optional parameter to which image found contours are drawn
*/
contour_vector_t filterContours(Mat &image, Mat drawImage=Mat());

/*
* Improves the edges and therefore corners of contours using
* helper points and the Sobel operator.
*
* @return vector of improved contours
* @param image grayscal image used to improve the contours
* @param contours original contours that should be improved
*
*/
contour_vector_f improveContourEdges(Mat &image, Mat& grayScale, contour_vector_t contours);

/*
* Analyze contours if they are a valid marker and use the contours to extract the marker
* from the original image.
*
* @return vector of marker images
* @param image the image from which to extract the markers, should be a grayscale image
* @param contours vector containing corner points that mark the position of potential markers
* @param slider_value parameter containing the threshold applied in the extraction process
*/
vector<tuple<Mat,contour_f>> extractValidMarkers(Mat& grayScale, contour_vector_f contours, int slider_value);

/*
* Takes a vector of valid markers and reads out the code encoded inside the marker.
*
* @return vector of codes
* @param markers vector of images containing (valid) markers
*/
vector<Marker> extractMarkers(vector<tuple<Mat, contour_f>> markers);

// used from sample Solution

Mat calculate_Stripe(double dx, double dy, MyStrip& st);

int subpixSampleSafe(const Mat& pSrc, const Point2f& p);