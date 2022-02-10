#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
#include "../markerdetection/Marker.h"
#include "../Chessboard.h"
#include <opencv2/opencv.hpp>
#include "../Chessboard.h"
#include <thread>
#include "../Puzzles.h"

/* PI */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

namespace dtools
{
	void drawSquare(float edgeLength);
	void drawSphere(double r, int lats, int longs);
	void drawCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
	void initGL();
	void display(GLFWwindow* window, const cv::Mat& img_bgr, int, int);
	void reshape(GLFWwindow* window, int width, int height);
	void colorField(std::array<float, 16>);
	void selectField(Field& field, ChessBoard& chessboard);
	void drawChessboard(ChessBoard&);
	void drawFigure(Figure, std::array<float, 16>);
	void drawMove(const Move& m, ChessBoard& board);
	void draw(cv::VideoCapture& cap, ChessBoard& chessboard, int videoWidth, int videoHeight);
	std::thread& startDrawing(cv::VideoCapture& cap, ChessBoard& chessboard, int videoWidth, int videoHeight);
	void stopDrawing(std::thread&);
	void drawFilledCircle(GLfloat radius);
}
