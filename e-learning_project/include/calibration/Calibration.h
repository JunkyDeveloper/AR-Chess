#pragma once
#include "../main.h"
#include "../Chessboard.h"
#include <thread>

namespace calib
{
	/**
	* Save pose matrices for every chessboard field
	* 
	* @param chessboard: The Chessboard
	* @param markersize: The size of a chessboard field in meters
	* @param frameWidth: width of the camera image in pixel
	* @param frameHeigth: height of the camera image in pixel
	*/
	void calibrationFromEdges(ChessBoard& chessboard, float markersize, int frameWidth, int frameHeight);

	/**
	* May return a field at the location of a marker that is not a chessboard edge marker
	* @param chessboard: the chessboard
	* @param frame: image frame containing a marker
	* @return Chessboard field the first found marker is placed on
	*/
	std::optional<Field> calibrateMarkerToFigure(ChessBoard& chessboard, Mat& frame);

	/**
	* Calibrate the chessboard. Searches for the corner markers, sets the corner points in the 
	* chessboard and calculates the pose matrices for the chessboard fields.
	* 
	* @param cap: Video Capture
	* @param chessBoard: Chessboard
	* @param fieldSize: Size of a board field in meters
	* @param videoWidth: width of the image frame in pixel
	* @param videoHeight: height of the image frame in pixel
	*/
	void calibrate(cv::VideoCapture& cap, ChessBoard& chessBoard, 
		float fieldSize, int videoWidth, int videoHeight, bool thread);

	/**
	* Starts the calibration thread.
	* 
	* @param cap: video capture used for image retrieval
	* @param chess: chessboard to save calibration to
	* @param fieldSize: size of the chessboad fields in meters
	* @param videoWidth: width of the image frame in pixel
	* @param videoHeight: height of the image frame in pixel
	*/
	std::thread& startCalibration(cv::VideoCapture& cap, 
		ChessBoard& chess, float fieldSize, int videoWidth, int videoHeight);

	/**
	* Ends the calibration thread.
	*/
	void endCalibration(std::thread& t);
}