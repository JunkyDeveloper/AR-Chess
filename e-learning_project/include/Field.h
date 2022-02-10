//
//  FIeld.hpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//
#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include "Figure.h"
#include<opencv2/opencv.hpp>
#include <memory>
class Field
{
public:
    struct cornerPoints
    {
        cv::Point2f corner0;
        cv::Point2f corner1;
        cv::Point2f corner2;
        cv::Point2f corner3;
    };

    Field();
    Field(char l, int n);
    void setCorners(cornerPoints);
    void setFigure(Figure);
    void setEmpty(bool);
    cornerPoints getCorners() const;
    char getLetter() const;
    int getNumber() const;
    bool getEmpty() const;
    Figure getFigure() const;

    std::array<float, 16> transformationMatrix;

    bool operator==(const Field& rhs) const;


private:
	// safe corner points in (real) coordinates
	cornerPoints corners;
	char letter;
	int number;
	bool empty;
	Figure figure;
};

struct Move {
    Move() = default;
    Field from;
    Field to;
    Figure figure;
};
