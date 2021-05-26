
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "Point.h"
#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
   Tile(Colour colour, Shape shape);
   Tile();

   Tile(const Tile &other);

   ~Tile();
   Colour colour;
   Shape shape;
   Point p;

   bool operator==(Tile &other);
};

#endif // ASSIGN2_TILE_H
