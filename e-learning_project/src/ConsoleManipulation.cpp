#include "../include/ConsoleManipulation.h"
#include <iostream>
#include <opencv2/opencv.hpp>

void cm::cleanMat(int height, int width)
{
	std::string line;
	// building spaces;
	for (int i = 0; i < width + 6; ++i)
	{
		line += " ";
	}
	//clear the field
	for (int i = 0; i < height; i++)
	{
		std::cout << "\033[" << i << ";0H" << line;
	}
}

void cm::overPrintMat(cv::Mat mat)
{
	cleanMat(mat.rows, mat.cols);
	std::cout << "\033[0;0H" << mat;
}