#ifndef POINT
#define POINT
#define STARTPOINT 'A'
#define ENDPOINT 'Z'
#define D_ROW "row"
#define D_COL "col"
#include <iostream>
class Point
{
public:
    // constructors and destructors
    Point(char c, int column);
    Point();
    ~Point();

    int getRow();

    int getColumn();

    bool validPoint(Point p, std::string direction = "", int n = 0);

    void diff(Point other, std::string &direction, int &n);

    // output point
    friend std::ostream &operator<<(std::ostream &out, Point p);

private:
    int row;
    int column;
    char rowAlphabet;
};

#endif
