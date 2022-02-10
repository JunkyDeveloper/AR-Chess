//
//  Figure.cpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//

#include <vector>
#include "../../include/Figure.h"

std::string Figure::getName() const {
    return name;
}

bool Figure::getIsWhite() const {
    return white;
}

bool Figure::shouldDraw() const
{
    return draw;
}

bool Figure::operator==(const Figure &rhs) const {
    return rhs.name == getName() && rhs.white == getIsWhite();
}
