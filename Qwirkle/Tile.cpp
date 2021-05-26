#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile()
{
}

Tile::Tile(const Tile &other)
{
    this->colour = other.colour;
    this->shape = other.shape;
    // std::cout << "COPYIED" << std::endl;
}

bool Tile::operator==(Tile &other)
{
    // bool same = false;
    // if (this->colour == other.colour && this->shape == other.shape)
    // {
    //     same = true;
    // }
    // return same;
    return (this->colour == other.colour && this->shape == other.shape);
}

Tile::Tile()
{
}
// Empty... for now?
