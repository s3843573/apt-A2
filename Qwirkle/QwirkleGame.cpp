#include "QwirkleGame.h"

QwirkleGame::QwirkleGame()
{
    currentPlayerIndex = 0;
    // playerSize = c;
}

QwirkleGame::~QwirkleGame()
{
}

void QwirkleGame::shuffle(Tile t[])
{
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, MAX_TILE_BAG_SIZE - 1);
    for (int i = 0; i < MAX_TILE_BAG_SIZE; i++)
    {
        // swap position for two random tiles inside the array
        int firstRandom = uniform_dist(randomSeed);
        int secondRandom = uniform_dist(randomSeed);

        Tile temp = t[firstRandom];
        t[firstRandom] = t[secondRandom];
        t[secondRandom] = temp;
    }
}

void QwirkleGame::setTileBag()
{
    Tile tiles[MAX_TILE_BAG_SIZE];
    Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    int index = 0;
    int size = sizeof(colours) / sizeof(colours[0]);

    // loop twice
    for (int l = 0; l < REPEAT_TILES; l++)
    {
        // create 36 tiles
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                Tile t(colours[j], shapes[k]);
                tiles[index] = t;
                ++index;
            }
        }
    }
    // comment the shuffle function when testing the game.
    // shuffle(tiles);

    for (int j = 0; j < MAX_TILE_BAG_SIZE; j++)
    {
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(tiles[j]);
        tileBag.addBack(tile);
    }
}

void QwirkleGame::startGame()
{
    // set up the bag at the start
    setTileBag();
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;

    // read in players names
    for (int i = 0; i < PLAYERSIZE; i++)
    {
        std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)" << std::endl;
        std::string name = getValidInput(COMMAND_PLAYER_NAME);
        addPlayer(name, i);
    }

    // starting with first player in the array
    switchPlayer(0);
}

void QwirkleGame::playGame()
{
    std::string message = "Starting a New Game";
    playGame(message);
}

void QwirkleGame::playGame(std::string message)
{
    std::cout << message << std::endl;
    bool end = false;

    while (!end)
    {
        // TESTING ONLY printing all tiles
        std::cout << tileBag << std::endl;

        std::cout << std::endl;

        for (unsigned int i = 0; i < addedTiles.size(); i++)
        {
            std::cout << addedTiles.at(i)->colour << ":" << addedTiles.at(i)->shape << ", ";
        }
        std::cout << std::endl;

        // print out basic player data
        std::cout << std::endl;
        std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
        for (int j = 0; j < PLAYERSIZE; j++)
        {
            std::shared_ptr<Player> p = players[j];
            std::cout << "Score for " << p->getName() << ": " << p->getScore() << std::endl;
        }

        board.printBoard();

        std::cout << "Your hand is " << std::endl;
        std::cout << *currentPlayer->getHand() << std::endl;
        std::cout << std::endl;

        std::string command = getValidInput(COMMAND);
        bool changePlayer = false;

        // catching any errors that command throw
        try
        {
            executeCommand(command, changePlayer);
        }
        catch (std::logic_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        // checking ending condition, if not switch player
        end = endGame();
        switchPlayer(currentPlayerIndex, changePlayer);
    }
}

void QwirkleGame::executeCommand(std::string input, bool &changePlayer)
{
    // Point point
    Colour c;
    Shape s;
    std::vector<std::string> commands;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::string command = getCommand(commands, input);

    // checking which command to perform
    if (commands[0] == COMMAND_PLACE)
    {
        // check if the colour, shape and point are valid
        validatePlacement(commands, tiles);

        for (unsigned i = 0; i < tiles.size(); i++)
        {
            std::shared_ptr<Tile> tile = tiles.at(i);
            int position = currentPlayer->getHand()->get(tile);

            // place tile
            board.placeTile(tile, currentPlayer);
            addedTiles.push_back(tile);
            changePlayer = true;
            currentPlayer->getHand()->deleteAt(position);
            drawTile(currentPlayer);
        }
    }
    else if (commands[0] == COMMAND_REPLACE)
    {
        // replace tile
        validateReplace(commands, c, s);
        replaceTile(tiles.at(0), changePlayer);
    }
    else if (commands[0] == COMMAND_SAVE)
    {
        // save game
        std::string name = commands[1];
        saveGame(name + FILE_EXTENSION);
    }
    else if (commands[0] == COMMAND_MUTI_PLACE)
    {
    }
}

void QwirkleGame::switchPlayer(int i, bool changedPlayer)
{
    // switch player
    if (changedPlayer)
    {
        i = (i == PLAYERSIZE - 1) ? 0 : i + 1;
        currentPlayer = players[i];
    }
    else
    {
        currentPlayer = players[i];
    }
    currentPlayerIndex = i;
}

void QwirkleGame::addPlayer(std::string name, int index)
{
    // add player to the array
    std::shared_ptr<Player> p = std::make_shared<Player>(name);
    for (int i = 0; i < MAXHAND; i++)
    {
        drawTile(p);
    }
    players[index] = p;
}

bool QwirkleGame::replaceTile(std::shared_ptr<Tile> tile, bool &changePlayer)
{
    bool replaced = false;
    int position = currentPlayer->getHand()->get(tile);

    // replace tile from player
    if (tile != nullptr)
    {
        replaced = true;
        tileBag.addBack(currentPlayer->getHand()->get(position));
        currentPlayer->getHand()->deleteAt(position);
        drawTile(currentPlayer);
        changePlayer = true;
    }
    return replaced;
}

bool QwirkleGame::endGame()
{
    bool end = false;

    // end game when tile bag is 0 and current player has no more tiles
    if (tileBag.size() == 0 && currentPlayer->getHand()->size() == 0)
    {
        end = true;
    }

    // printing end game messages
    if (end)
    {
        std::cout << std::endl;
        std::cout << "Game Over" << std::endl;
        std::shared_ptr<Player> winner = players[0];

        for (int i = 0; i < PLAYERSIZE; i++)
        {
            std::shared_ptr<Player> p = players[i];
            std::cout << "Score for " << p->getName() << ": " << p->getScore() << std::endl;
            if (p->getScore() > winner->getScore())
            {
                winner = p;
            }
        }
        std::cout << "Player " << winner->getName() << " won!" << std::endl;

        // exit
        throw std::exception();
    }
    return end;
}

void QwirkleGame::loadPlayer(std::ifstream &file, int index)
{
    // read in name and score
    std::string name;
    file >> name;
    int score;
    file >> score;

    // creating a new player
    std::shared_ptr<Player> p = std::make_shared<Player>(name, score);

    std::string line;
    std::getline(file, line);

    std::string hand;
    std::getline(file, hand);

    std::vector<std::string> tiles;
    split(tiles, hand, TILE_DELIMITER);

    // load player's hand
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        std::string tile = tiles.at(i);
        Colour c = tile.at(0);
        Shape s = intCharToInt(tile.at(1));
        std::shared_ptr<Tile> t = std::make_shared<Tile>(c, s);
        p->getHand()->addBack(t);
    }

    // save player to the array
    players[index] = p;
}

void QwirkleGame::loadBoard(std::ifstream &file)
{
    std::vector<std::string> info;
    std::string tiles;
    std::getline(file, tiles);
    // add tiles if the the line is not none
    if (tiles.length() > 0)
    {
        split(info, tiles, BOARD_DELIMITER, 2);
        for (int i = 0; i < (int)info.size(); i++)
        {
            std::string tileInfo = info[i];

            // get tile data
            Colour c = tileInfo.at(0);
            Shape s = (int)(tileInfo.at(1) - '0');

            std::shared_ptr<Tile> tile = std::make_shared<Tile>(c, s);
            char row = tileInfo.at(3);
            int column = intCharToInt(tileInfo.at(4));
            // point that is larger than 9
            if (tileInfo.size() > 5)
            {
                column = column * 10 + intCharToInt(tileInfo.at(5));
            }

            // place tiles onto the board
            Point p(row, column);
            tile->p = p;
            board.placeTile(tile);
        }
    }
}

void QwirkleGame::loadGame(std::string fileName)
{
    std::ifstream file(fileName);

    // load players
    for (int i = 0; i < PLAYERSIZE; i++)
    {
        loadPlayer(file, i);
    }

    std::string boardSize;
    std::getline(file, boardSize);

    // load board and tile tag
    loadBoard(file);
    loadTiles(file);
    std::string name;
    std::getline(file, name);

    // get current player
    int index = 0;
    for (int i = 0; i < PLAYERSIZE; i++)
    {
        if (players[i]->getName() == name)
        {
            index = i;
        }
    }
    switchPlayer(index);

    // success message
    std::string message = "Qwirkle game successfully loaded";
    playGame(message);
    file.close();
}

void QwirkleGame::loadTiles(std::ifstream &file)
{
    // save all tiles
    std::vector<std::string> allTiles;
    std::string tiles;
    std::getline(file, tiles);

    if (tiles.size() > 0)
    {
        split(allTiles, tiles, TILE_DELIMITER);
        for (int i = 0; i < (int)allTiles.size(); i++)
        {
            std::string tile = allTiles.at(i);
            Colour c = tile.at(0);
            Shape s = intCharToInt(tile.at(1));
            std::shared_ptr<Tile> t = std::make_shared<Tile>(c, s);
            tileBag.addBack(t);
        }
    }
}

void QwirkleGame::saveGame(std::string fileName)
{
    if (fileName == FILE_EXTENSION)
    {
        throw std::logic_error(INVALID_INPUT);
    }

    std::ofstream saveGame(fileName);

    // save players
    for (int i = 0; i < PLAYERSIZE; i++)
    {
        saveGame << players[i]->getName() << std::endl;
        saveGame << players[i]->getScore() << std::endl;
        saveGame << *players[i]->getHand() << std::endl;
    }

    // save board and tile tag
    saveGame << DIMENSIONS << "," << DIMENSIONS << std::endl;
    saveGame << board << std::endl;
    saveGame << tileBag << std::endl;
    saveGame << currentPlayer->getName();

    // save success message
    std::cout << "Game successfully saved" << std::endl;
    saveGame.close();
}

void QwirkleGame::drawTile(std::shared_ptr<Player> player)
{
    if (tileBag.size() > 0)
    {
        player->getHand()->addBack(tileBag.get(0));
        tileBag.deleteFront();
    }
}
