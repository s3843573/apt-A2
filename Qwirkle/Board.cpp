#include "Board.h"

Board::Board()
{
    setBoard();
}

Board::~Board()
{
    board.clear();
}

void Board::setBoard()
{
    for (int i = 0; i < DIMENSIONS; i++)
    {
        std::vector<std::shared_ptr<Tile>> tiles(DIMENSIONS);
        board.push_back(tiles);
    }
}

void Board::printBoard()
{
    std::cout << "  ";
    for (int i = 0; i < DIMENSIONS; i++)
    {
        if (i < 10)
        {
            std::cout << "  " << i;
        }
        else
        {
            std::cout << " " << i;
        }
    }
    std::cout << std::endl;

    std::cout << "  ";
    for (int i = 0; i < DIMENSIONS; i++)
    {
        std::cout << "---";
    }
    std::cout << std::endl;
    std::cout << "";

    // print all tiles inside with |  |
    for (int i = 0; i < DIMENSIONS; i++)
    {
        std::cout << (char)(STARTPOINT + i) << " ";
        for (int j = 0; j < DIMENSIONS; j++)
        {
            std::shared_ptr<Tile> tile = board[i][j];
            if (tile != nullptr)
            {
                std::cout << "|" << tile->colour << tile->shape;
                if (j == DIMENSIONS - 1)
                {
                    std::cout << "|";
                }
            }
            else if (j < DIMENSIONS - 1)
            {
                std::cout << "|  ";
            }
            else
            {
                std::cout << "|  |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::placeTile(std::shared_ptr<Tile> tile, std::shared_ptr<Player> player)
{
    Point p = tile->p;
    // if the point is out of the board, throw out of range exception
    if (!validatePosition(p.getRow(), p.getColumn()))
    {
        throw std::out_of_range("Input Position out of the board");
    }
    if (player != nullptr)
    {
        calculateScore(player, tile);
    }
    board[p.getRow()][p.getColumn()] = tile;
}

bool Board::calculateScore(std::shared_ptr<Player> player,
                           std::shared_ptr<Tile> tile)
{
    // get coordinate information
    int row = tile->p.getRow();
    int col = tile->p.getColumn();

    // neightbour coordinate
    int rowNeighbours[] = {1, 0, -1, 0};
    int colNeighbours[] = {0, -1, 0, 1};

    std::shared_ptr<Tile> t = board[row][col];

    int playerScore = player->getScore();
    bool stop = false;

    stop = (t != nullptr) ? true : false;

    // total score for all directions
    int score = 0;
    int i = 0;
    int newRowCol = 0;

    bool placed = false;

    // checking for the first placement for tile
    int firstTile = tiles();
    if (firstTile == 0)
    {
        stop = true;
        score = 2;
        placed = true;
    }

    while (!stop)
    {
        // checking all neightbours
        stop = (i == DIRECTIONS - 1);

        int newRow = row + rowNeighbours[i];
        int newCol = col + colNeighbours[i];

        std::shared_ptr<Tile> current = nullptr;
        bool bounded = validatePosition(newRow, newCol);

        // checking coordinate out of bound
        if (bounded)
        {
            current = board[newRow][newCol];
        }

        // each direction have seperated score to increment
        int tilesScore = 0;
        bool getPoints = false;

        while (current != nullptr && tilesScore < MAX_TILES - 1)
        {
            // rules for a valid placement
            bool colourRule = current->colour == tile->colour && current->shape != tile->shape;
            bool shapeRule = current->shape == tile->shape && current->colour != tile->colour;
            bool rule = colourRule || shapeRule;
            bool same = !(current == tile);

            if (rule && same)
            {
                // adding tile score
                ++tilesScore;
                getPoints = true;

                // qwirkle condition
                if (tilesScore == MAX_TILES - 1)
                {
                    std::cout << "Qwirkle!!!" << std::endl;
                    score += 6;
                }

                placed = true;

                // increment the value in the same direction
                newRow += rowNeighbours[i];
                newCol += colNeighbours[i];

                // bound check
                current = (validatePosition(newRow, newCol)) ? board[newRow][newCol] : nullptr;
            }
            else
            {
                current = nullptr;
                stop = true;
                placed = false;
            }
        }

        // add one point to itself, for each new row or column created
        newRowCol = (getPoints) ? newRowCol + 1 : newRowCol;

        ++i;
        score += tilesScore;
        tilesScore = 0;
    }

    // updat player score, for a valid placement
    if (placed)
    {
        int totalScore = playerScore + score + newRowCol;
        player->setScore(totalScore);
    }
    else
    {
        throw std::logic_error("Invalid placement, check your tile and position");
    }
    std::cout << "HERE" << std::endl;
    return placed;
}

std::shared_ptr<Tile> Board::getTile(Point p)
{
    if (!validatePosition(p.getRow(), p.getColumn()))
    {
        throw std::out_of_range("Input position out of the board");
    }

    return board[p.getRow()][p.getColumn()];
}

std::ostream &operator<<(std::ostream &os, Board &board)
{
    int allTiles = board.tiles();
    int count = 0;
    for (int i = 0; i < DIMENSIONS; i++)
    {
        char row = i + STARTPOINT;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            Point p(row, j);
            std::shared_ptr<Tile> tile = board.getTile(p);
            if (tile != nullptr)
            {
                // follwing the save format
                if (count == allTiles - 1)
                {
                    os << tile->colour << tile->shape << "@" << p;
                }
                else
                {
                    os << tile->colour << tile->shape << "@" << p << ", ";
                }
                ++count;
            }
        }
    }
    return os;
}

int Board::tiles()
{
    // all placed tiles
    int count = 0;
    for (int i = 0; i < DIMENSIONS; i++)
    {
        for (int j = 0; j < DIMENSIONS; j++)
        {
            if (board[i][j] != nullptr)
            {
                ++count;
            }
        }
    }
    return count;
}

void Board::removeTile(std::shared_ptr<Tile> tile)
{
    Point p = tile->p;
    board[p.getRow()][p.getColumn()] = nullptr;
}
