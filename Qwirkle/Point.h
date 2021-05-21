#ifndef POINT
#define POINT
#define STARTPOINT 'A'
#define ENDPOINT 'Z'
#include <iostream>
class Point
{
public:
    // constructors and destructors
    Point(char c, int column);
    Point();
    ~Point();

    // get row
    int getRow();

    // get column
    int getColumn();

    // output point
    friend std::ostream &operator<<(std::ostream &out, Point p);

private:
    int row;
    int column;
    char rowAlphabet;
};

#endif
