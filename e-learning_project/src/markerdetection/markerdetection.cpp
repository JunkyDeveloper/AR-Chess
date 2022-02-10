#include "../../include/markerdetection/markerdetection.h"
#include "../../include/Tools.h"
#include "../../include/markerdetection/PoseEstimation.h"
#include <tuple>
#include <optional>

using namespace cv;

std::vector<Marker> md::findMarkerInFrame(cv::Mat& frame)
{
	Mat imgFiltered;
	Mat grayScale;
	imgFiltered = frame;
	// Convert image to gray scale
	cvtColor(imgFiltered, grayScale, COLOR_BGR2GRAY);
	// Threshold to reduce the noise and convert to binary coloured image
	threshold(grayScale, grayScale, 130, 255, THRESH_BINARY);
	// find contours in the grayScale image and filter out the interesting ones
	contour_vector_t processedContours = filterContours(grayScale, imgFiltered);
	// improve the edges of relevant contours before marker analysis
	contour_vector_f improvedContours = improveContourEdges(imgFiltered, grayScale, processedContours);
	// Give only valid markers back
	auto valMar = extractValidMarkers(grayScale, improvedContours, 180);
	// Extract the code, corners and the orientation of the marker
	return extractMarkers(valMar);
}

std::vector<cv::Point2f> md::findChessboard(std::vector<Marker> markers)
{
	std::optional<Point2f> topRight, bottomLeft, bottomRight, topLeft;
	Marker markerTopRight, markerBottomLeft, markerBottomRight, markerTopLeft;
	std::vector<cv::Point2f> chessboard;
	for (auto& marker : markers) {
		// for each marker, take the corner touching the chessboard edge
		// if marker orientation=0, then the marker corners are ordered as follows:
		// top left, top right, bottom right, bottom left
		switch (marker.getID())		
		{
		case 0x0272: // top left
			markerTopLeft = marker;
			switch (marker.getOrientation())
			{
			case 0: topLeft = marker.getCorners().at(2);
				break;
			case 1: topLeft = marker.getCorners().at(1);
				break;
			case 2:	topLeft = marker.getCorners().at(0);
				break;
			case 3:	topLeft = marker.getCorners().at(3);
				break;
			default:
				break;
			}
			break;
		case 0x005A: // top right
			markerTopRight = marker;
			switch (marker.getOrientation())
			{
			case 0: topRight = marker.getCorners().at(3);
				break;
			case 1: topRight = marker.getCorners().at(2);
				break;
			case 2:	topRight = marker.getCorners().at(1);
				break;
			case 3:	topRight = marker.getCorners().at(0);
				break;
			default:
				break;
			}
			break;
		case 0x0690: // bottom left
			markerBottomLeft = marker;
			switch (marker.getOrientation())
			{
			case 0: bottomLeft = marker.getCorners().at(1);
				break;
			case 1: bottomLeft = marker.getCorners().at(0);
				break;
			case 2:	bottomLeft = marker.getCorners().at(3);
				break;
			case 3:	bottomLeft = marker.getCorners().at(2);
				break;
			default:
				break;
			}
			break;
		case 0x0B44: // bottom right
			markerBottomRight = marker;
			switch (marker.getOrientation())
			{
			case 0: bottomRight = marker.getCorners().at(0);
				break;
			case 1: bottomRight = marker.getCorners().at(3);
				break;
			case 2:	bottomRight = marker.getCorners().at(2);
				break;
			case 3:	bottomRight = marker.getCorners().at(1);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

	}
	// Sort the edge points in the correct order
	// 0 topRight
	// 1 bottomLeft
	// 2 bottomRight
	// 3 topLeft
	if (topRight.has_value()) {
		chessboard.emplace_back(topRight.value());
	}
	if (bottomLeft.has_value()) {
		chessboard.emplace_back(bottomLeft.value());
	}
	if (bottomRight.has_value()) {
		chessboard.emplace_back(bottomRight.value());
	}
	if (topLeft.has_value()) {
		chessboard.emplace_back(topLeft.value());
	}
	return chessboard;
}
