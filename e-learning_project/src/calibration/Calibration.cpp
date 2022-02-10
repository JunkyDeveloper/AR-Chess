#include "../../include/calibration/Calibration.h"
#include "../../include/markerdetection/PoseEstimation.h"
#include <memory>
#include <thread>
#include <atomic>

void calib::calibrationFromEdges(ChessBoard& chessboard, float markersize, int frameWidth, int frameHeight)
{
	auto board = chessboard.getBoard();
	for (auto& row : board)
	{
		for (auto& field : row)
		{
			// order corners for pose estimation
			cv::Point2f corners[4] = {
				field.getCorners().corner0,
				field.getCorners().corner1,
				field.getCorners().corner3,
				field.getCorners().corner2
			};
			// transform frame coordinates to camera coordinates
			for (int i = 0; i < 4; ++i) {
				// constant shift -> origin needs to be in the center of image
				corners[i].x -= frameWidth >> 1;
				// -(corners.y) -> is needed because y is inverted
				corners[i].y = -corners[i].y + (frameHeight >> 1);
			}
			std::array<float, 16> trans;
			estimateSquarePose(trans.data(), corners, markersize);
			// save transformation matrix for the current field
			field.transformationMatrix = trans;
		}
	}
	chessboard.replaceTransformation(board);
}

std::optional<Field> calib::calibrateMarkerToFigure(ChessBoard& chessboard, Mat& frame)
{
	for (auto& marker : md::findMarkerInFrame(frame))
	{
		int id = marker.getID();
		if (id != 0x0272 && id != 0x005A && id != 0x0690 && id != 0x0B44)
		{
			// return the field the marker was placed on
			return chessboard.locateField(marker.getMiddle());
		}
	}
	return std::nullopt;
}
extern std::atomic<bool> running;
extern std::atomic<bool> newVideoStream;
void calib::calibrate(cv::VideoCapture& cap, ChessBoard& chessBoard, float fieldSize, int videoWidth, int videoHeight, bool thread)
{
	cv::Mat img_bgr;
	contour_f output;
	do
	{
		// Find the chessboard corners
		do
		{
			if (!running)
			{
				break;
			}
			if (newVideoStream)
			{
				continue;
			}
			try
			{
				if (thread)
				{
					cap.retrieve(img_bgr);
				}
				else
					cap >> img_bgr;
			}
			catch (std::exception&es)
			{
				cout << es.what();
			}
			if (img_bgr.empty() && thread)
			{
				continue;
			}
			// find the chessboard corners
			output = md::findChessboard(md::findMarkerInFrame(img_bgr));
		} while (output.size() < 4);
		if (!running)
		{
			break;
		}
		// Set corner points of the board
		ChessboardTools::setCornerPointsOfFields(output, chessBoard);
		// Save pose matrices for every field to the chessboard
		calib::calibrationFromEdges(chessBoard, fieldSize, videoWidth, videoHeight);
	} while (thread && running);
}

std::thread& calib::startCalibration(cv::VideoCapture& cap, ChessBoard& chess, float fieldSize, int videoWidth, int videoHeight)
{
	static std::thread calib(calibrate, std::ref(cap), std::ref(chess), fieldSize, videoWidth, videoHeight, true);
	return calib;
}

void calib::endCalibration(std::thread& t)
{
	t.join();
}