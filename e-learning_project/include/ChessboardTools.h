#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "./Tools.h"
#include "./ConsoleManipulation.h"
#include "./markerdetection/markerdetection.h"
#include "Chessboard.h"

namespace ChessboardTools
{
    ChessBoard createEmptyBoard();
    ChessBoard createStartingBoard();
    void addFigures(bool white, int startingRow, ChessBoard &chessboard);
    std::string chessboardToString(std::vector<std::vector<Field> > board);
    ChessBoard stringToChessboard(const std::string&);
    Field& selectField(ChessBoard &board);
    ChessBoard stringToChessboard(const std::string& boardString);
    Point2f getIntersection(Point2f a, Point2f b, Point2f c, Point2f d);
    void setCornerPointsOfFields(contour_f vec, ChessBoard &chessboard);
}