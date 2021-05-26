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

void Point::diff(Point other, std::string &direction, int &n)
{
    bool rowD = ((row - other.row == 1) || (row - other.row == -1)) && (column == other.column);
    bool colD = ((column - other.column == 1) || (column - other.column == -1)) && (row == other.row);
    if (!(rowD || colD))
    {
        throw std::logic_error("Invalid Tiles");
    }
    else if (rowD)
    {
        direction = D_ROW;
        n = row - other.row;
    }
    else if (colD)
    {
        direction = D_COL;
        n = column - other.column;
    }
}

bool Point::validPoint(Point p, std::string direction, int n)
{
    std::string message = "";

    bool valid = false;
    if (direction.empty())
    {
        bool validRow = ((this->row - 1 == p.row) || (this->row + 1 == p.column));
        bool validCol = ((this->column - 1 == p.row) || (this->column + 1 == p.column));
        valid = validRow || validCol;
    }
    else
    {
        std::cout << direction << std::endl;
        std::cout << n << std::endl;
        if (direction == D_ROW)
        {
            valid = (row - n == p.row);
        }
        else if (direction == D_COL)
        {
            valid = (column - n == p.column);
        }
    }
    if (!valid)
    {
        throw std::logic_error("TEST error ");
    }
    return valid;
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
