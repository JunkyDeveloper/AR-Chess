#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "./Tools.h"
#include "./ConsoleManipulation.h"
#include "./markerdetection/markerdetection.h"
#include "./drawing/DrawTools.h"
#include "./ChessboardTools.h"
#include "./drawing/DrawFigures.h"
#include "./Puzzles.h"
#include <atomic>

#define camera_angle 30

using namespace std;
using namespace cv;
void initVideoStream(cv::VideoCapture& cap);