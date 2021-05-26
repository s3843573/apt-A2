#ifndef BOARD
#define BOARD

#include "Player.h"
#include "Point.h"
#include "Tile.h"
#include "Utils.h"

#define DIMENSIONS 26
#define MAX_TILES 6

#include <vector>

class Board
{
public:
    Board();
    ~Board();

    // place tile on the board
    void placeTile(std::shared_ptr<Tile> tile, std::shared_ptr<Player> player = nullptr);

    void removeTile(std::shared_ptr<Tile> tile);

    // print entire board
    void printBoard();

    // get the with given point
    std::shared_ptr<Tile> getTile(Point p);

    // calculating the score for the placement
    bool calculateScore(std::shared_ptr<Player> player,
                        std::shared_ptr<Tile> tile);

    // using this method for saving board state
    friend std::ostream &
    operator<<(std::ostream &os, Board &board);

private:
    // vector of vectors of tiles
    std::vector<std::vector<std::shared_ptr<Tile>>> board;

    // set up the new board
    void setBoard();

    // number of tiles
    int tiles();
};
#endif
