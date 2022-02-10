//
//  FIeld.cpp
//  LauraLovesLogicLocal
//
//  Created by Felix Moser on 18.06.21.
//

#include "../../include/Field.h"

Field::Field() : letter{ 'Z' }, number{ -1 }, empty{ true } {
    // defines a default field
}

Field::Field(char l, int n) : letter{ l }, number{ n } {
    empty = true;
}

Field::cornerPoints Field::getCorners() const
{
    return corners;
}

char Field::getLetter() const
{
    return letter;
}

int Field::getNumber() const
{
    return number;
}

bool Field::getEmpty() const
{
    return empty;
}

Figure Field::getFigure() const
{
    return figure;
}

void Field::setCorners(Field::cornerPoints c)
{
    corners = c;
}

void Field::setFigure(Figure fig)
{
    figure = std::move(fig);
    empty = false;
}

void Field::setEmpty(bool e)
{
    empty = e;
}

bool Field::operator==(const Field& rhs) const {
    return rhs.letter == getLetter()
        && rhs.number == getNumber()
        && rhs.empty == getEmpty()
        && rhs.figure == getFigure();
}
