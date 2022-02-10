#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <opencv2/opencv.hpp>

/**
 * <br/> Defines a marker
 */
class Marker
{
private:
    /**
     * <br/> The code of the marker
     */
	int _id;
	/**
	 * <br/> The orientation of the marker
	 */
	int _orientation;
	/**
	 * <br/> The corners of the marker
	 */
	std::vector<cv::Point2f> _corners;

public:
	Marker() = default;
	Marker(int id, int orientation, std::vector<cv::Point2f> corner) :_id(id), _orientation(orientation), _corners(std::move(corner))
	{	}

	int getID() const
	{
		return _id;
	}

	int getOrientation() const
	{
		return _orientation;
	}

	std::vector<cv::Point2f>& getCorners()
	{
        return _corners;
    }

	/**
	 * <br/> Calculates the middle of the marker
	 * <br/> Returns x,y
	 */
	std::tuple<double, double> getMiddle() const
	{
		using namespace cv;
		Point2f start = _corners[0];
		Point2f otherSide = _corners[2];
		return std::make_tuple(start.x + ((otherSide.x - start.x) / 2), start.y + ((otherSide.y - start.y) / 2));
	}

	/**
	 * <br/> Display method for debugging
	 * @param os ostream
	 * @param m marker
	 * @return ostream
	 */
	friend std::ostream& operator<<(std::ostream& os, const Marker& m);
};


inline std::ostream& operator<<(std::ostream& os, const Marker& m)
{
	const auto& [x, y] = m.getMiddle();
	os << "Marker id: " << m._id << " Position: x=" << x << " y=" << y << " Orientation: " << m._orientation << "\n";
	return os;
}
