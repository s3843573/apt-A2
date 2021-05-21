#include "Point.h"
Point::Point(char c, int colmun)
{
    this->row = c % STARTPOINT;
    this->column = colmun;
    this->rowAlphabet = c;
}

Point::Point()
{
}

Point::~Point()
{
}

int Point::getRow()
{
    return row;
}

int Point::getColumn()
{
    return column;
}

std::ostream &operator<<(std::ostream &out, Point p)
{
    out << p.rowAlphabet << p.column;
    return out;
}
