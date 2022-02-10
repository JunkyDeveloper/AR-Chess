//
//  Figure.hpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//
#pragma once
#include <string>
#include <vector>

class Figure {
public:
	Figure() = default;

	Figure(std::string n, bool w) : name{ n }, white{ w }, draw{ false } {}
	Figure(std::string n, bool w, bool d) : name{ n }, white{ w }, draw{ d }{}

	std::string getName() const;

	bool getIsWhite() const;

	bool shouldDraw() const;

	std::string name;
	bool white; // 1 -> white, 0 -> black
	bool draw;

	bool operator==(const Figure& rhs) const;
};

