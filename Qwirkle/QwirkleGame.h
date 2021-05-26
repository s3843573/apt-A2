#ifndef GAME
#define GAME

#include "Utils.h"

#include <random>
#include <time.h>
#define PLAYERSIZE 1

class QwirkleGame
{
public:
    QwirkleGame();
    ~QwirkleGame();

    // start the game
    void startGame();

    // play game
    void playGame();

    void addPlayer(std::string name, int index);

    bool replaceTile(std::shared_ptr<Tile> tile, bool &changePlayer);

    bool endGame();

    // command for save and load for the game
    void saveGame(std::string fileName);
    void loadGame(std::string fileName);

    // create a tile bag then shuffle it
    void setTileBag();

    // switch current player
    void switchPlayer(int i, bool changePlayer = false);

    // load functions
    void loadBoard(std::ifstream &file);
    void loadTiles(std::ifstream &file);
    void loadPlayer(std::ifstream &file, int index);

    // run methods base on the command
    void executeCommand(std::string command, bool &changePlayer);

private:
    LinkedList tileBag;
    Board board;

    std::shared_ptr<Player> players[PLAYERSIZE];

    int currentPlayerIndex;

    void drawTile(std::shared_ptr<Player> player);

    // all valid tiles
    std::vector<std::shared_ptr<Tile>> addedTiles;

    std::shared_ptr<Player> currentPlayer;

    void shuffle(Tile t[]);

    void playGame(std::string message);
    // const int playerSize;
};
#endif