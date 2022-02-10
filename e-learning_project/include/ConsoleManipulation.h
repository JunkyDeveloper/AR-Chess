#pragma once
#include <opencv2/core/mat.hpp>

namespace cm
{
	/**
	 * Clear the lines from the zero position
	 */
	void cleanMat(int height, int width);

	/**
	 * Write the matrix at the position 0,0
	 */
	void overPrintMat(cv::Mat mat);
}