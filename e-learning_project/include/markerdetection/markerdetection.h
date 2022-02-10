#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include "Marker.h"

namespace md
{
	/**
	* Finds all 4x4 marker in a video frame.
	* 
	* @param frame: a single video frame 
	* @return vector of Markers found in the frame
	*/
	std::vector<Marker> findMarkerInFrame(cv::Mat& frame);

	/**
	* Expects a vector of markers and sorts out the edge markers of the chessboard.
	* For each of these edge markers the correct corner is chosen which describes the edges
	* of the physical chessboard.
	* 
	* @param a vector of markers
	* @return a vector with two dimensional points representing the chessboard edges
	*/
	std::vector<cv::Point2f> findChessboard(std::vector<Marker>);
}