#include "Utils.h"

void validateMenu(std::string &input, bool &valid)
{
    // checking if the input is a valid menu option
    if (!(input == NEW_GAME || input == LOAD_GAME ||
          input == CREDITS || input == MENU_QUIT))
    {
        throw std::logic_error(INVALID_INPUT);
    }
    valid = true;
}

// spilt command into a vector
void split(std::vector<std::string> &commands,
           std::string command, std::string delimeter, int space)
{
    int start = 0;
    int endStr = command.find(delimeter);
    // spilt the command base on the delimiter
    while (endStr != (int)command.npos)
    {
        std::string str = command.substr(start, endStr - start);
        start = endStr + space;
        endStr = command.find(delimeter, start);
        commands.push_back(str);
    }

    // add last command to the vector
    commands.push_back(command.substr(start));
}

int intCharToInt(char c)
{
    // convert char to an int
    int n = (int)(c - '0');

    if (n < OUT_OF_BOARD)
    {
        throw std::logic_error("Cannot convert inputed Character to Integer");
    }

    return n;
}

void validatePlayerName(std::string &input, bool &valid)
{
    if (input.size() == 0)
    {
        throw std::logic_error(INVALID_INPUT);
    }

    for (int i = 0; i < (int)input.length(); i++)
    {
        // each character should be upper case alphabet only
        if (islower(input.at(i)) || !isalpha(input.at(i)))
        {
            std::string msg = "Invalid player name (upper case alphabet character only)";
            throw std::logic_error(msg);
        }
    }
    valid = true;
}

bool validateShape(Shape s)
{
    return (s >= CIRCLE && s <= CLOVER);
}

bool validateColour(Colour c)
{
    if (c < STARTPOINT && c > ENDPOINT)
    {
        throw std::logic_error("Invalid colour");
    }

    return true;
}
bool validatePosition(int row, int col)
{
    bool xBound = (row < OUT_OF_BOARD || row >= DIMENSIONS);
    bool yBound = (col < OUT_OF_BOARD || col >= DIMENSIONS);
    if (xBound || yBound)
    {
        throw std::logic_error("Invalid Position");
    }
    std::cout << "position" << std::endl;
    return true;
}

bool validatePosition(Point p)
{
    return validatePosition(p.getRow(), p.getColumn());
}

int findWord(std::string str, std::vector<std::string> commands)
{
    int index = NOT_FOUND;
    for (int i = 0; i < (int)commands.size(); i++)
    {
        if (commands[i] == str)
        {
            index = i;
        }
    }
    return index;
}

bool mutiCheck(std::vector<std::shared_ptr<Tile>> tiles)
{
    for (unsigned i = 0; i < tiles.size() - 1; i++)
    {
        Point firstP = tiles.at(i)->p;
        Point secondP = tiles.at(i + 1)->p;

        bool rowRule = ((firstP.getRow() - secondP.getRow() == 1) ||
                        (firstP.getRow() - secondP.getRow() == -1)) &&
                       (firstP.getColumn() == secondP.getColumn());

        bool colRule = ((firstP.getColumn() - secondP.getColumn() == 1) ||
                        (firstP.getColumn() - secondP.getColumn() == -1)) &&
                       (firstP.getRow() == secondP.getRow());

        if (!(rowRule || colRule))
        {
            throw std::logic_error("Invalid Positions");
        }
    }

    for (unsigned i = 0; i < tiles.size() - 1; i++)
    {
        std::shared_ptr<Tile> first = tiles.at(i);
        Point firstP = first->p;
        for (unsigned j = i + 1; j < tiles.size(); j++)
        {
            std::shared_ptr<Tile> second = tiles.at(j);
            Point secondP = second->p;
            bool colourRule = (first->colour == second->colour && first->shape != second->shape);
            bool shapeRule = (first->shape == second->shape && first->colour != second->colour);

            if (!(colourRule || shapeRule))
            {
                throw std::logic_error("Invalid Tiless");
            }
        }
    }
    return true;
}

void validateFile(std::string &name, bool &valid)
{
    if (name.find(FILE_EXTENSION) == name.npos)
    {
        name += FILE_EXTENSION;
        std::ifstream file(name);

        // checking the existence of an file
        if (file.good())
        {
            valid = true;
        }
    }
}

bool validateReplace(std::vector<std::string> commands, Colour &c, Shape &s)
{
    bool valid = false;
    if (commands.size() == SHORT_CMD_LENGTH)
    {
        int replace = findWord(COMMAND_REPLACE, commands);
        if (replace != NOT_FOUND)
        {
            std::string tileInfo = commands[1];
            c = tileInfo.at(0);
            s = intCharToInt(tileInfo.at(1));
            valid = validateColour(c) && validateShape(s);
        }
    }
    return valid;
}

std::string getCommand(std::vector<std::string> &commands, std::string input)
{
    std::string delimeter = " ";
    split(commands, input, delimeter);

    if (commands.size() == 0)
    {
        throw std::logic_error("Invalid command input");
    }
    return commands[0];
}

void validatePlacement(std::vector<std::string> commands, std::vector<std::shared_ptr<Tile>> &tiles)
{
    // adding inputed positions for tiles

    // adding inputed tiles

    bool valid = false;
    if (commands.size() >= COMMAND_PLACE_LENGTH)
    {
        int place = findWord(COMMAND_PLACE, commands);
        int at = findWord(STRING_AT, commands);

        if (place != NOT_FOUND && at != NOT_FOUND)
        {
            for (int i = 1; i < at; i++)
            {
                std::string tileInfo = commands.at(i);
                Colour c = tileInfo.at(0);
                Shape s = intCharToInt(tileInfo.at(1));
                validateColour(c);
                validateShape(s);
                std::shared_ptr<Tile> tile = std::make_shared<Tile>(c, s);
                tiles.push_back(tile);
            }
        }

        std::vector<Point> points;
        for (int i = at + 1; i < (int)commands.size(); i++)
        {
            std::string point = commands.at(i);
            int column = intCharToInt(point.at(1));
            char row = point.at(0);
            // coordinate above 9
            if ((int)point.size() <= POSITION_LENGTH)
            {
                // coordinate above 9
                if (point.size() > 2)
                {
                    column = column * 10 + intCharToInt(point.at(2));
                }
            }
            else
            {
                column = OUT_OF_BOARD;
            }
            Point p(row, column);
            validatePosition(p);
            points.push_back(p);
        }

        if (points.size() > tiles.size())
        {
            throw std::logic_error("You have more coordinates than tiles");
        }
        else if (tiles.size() > points.size())
        {
            throw std::logic_error("You have more tiles than coordinates");
        }
        else
        {
            for (unsigned i = 0; i < tiles.size(); i++)
            {
                tiles.at(i)->p = points.at(i);
            }
        }
        valid = true;
    }
    if (!valid)
    {
        throw std::logic_error("Invalid placement of Tile");
    }
}

void validateCommand(std::vector<std::string> commands, std::string input, bool &valid)
{
    // checking if input matches any command
    if (!(commands.size() < SHORT_CMD_LENGTH))
    {
        if (commands.at(0) == COMMAND_PLACE && commands.size() >= COMMAND_PLACE_LENGTH)
        {
            int index = findWord(STRING_AT, commands);
            valid = (index != NOT_FOUND) ? true : false;
        }
        else if (commands.at(0) == COMMAND_REPLACE &&
                 (int)commands.size() == SHORT_CMD_LENGTH)
        {
            valid = true;
        }
        else if (commands.at(0) == COMMAND_SAVE &&
                 (int)commands.size() == SHORT_CMD_LENGTH)
        {
            valid = true;
        }
        else if (commands.at(0) == COMMAND_MUTI_PLACE)
        {
            valid = true;
        }
    }
}

std::string getValidInput(std::string type)
{
    bool valid = false;
    std::string input;

    while (!valid)
    {
        //Prompt
        std::cout << "> ";
        std::getline(std::cin, input);

        // keep loop until a valid input
        try
        {
            if (!std::cin.eof())
            {
                // validate base on the type
                if (type == COMMAND_MENU && input.length() == 1)
                {
                    validateMenu(input, valid);
                }
                else if (type == COMMAND_PLAYER_NAME)
                {
                    validatePlayerName(input, valid);
                }
                else if (type == COMMAND_LOAD)
                {
                    validateFile(input, valid);
                }
                else if (type == COMMAND)
                {
                    std::vector<std::string> commands;
                    split(commands, input, COMMAND_DELIMITER);
                    validateCommand(commands, input, valid);
                }

                // not a valid command
                if (!valid)
                {
                    throw std::logic_error(INVALID_INPUT);
                }
            }
            else
            {
                std::cout << std::endl;

                // exit program after eof
                throw std::exception();
            }
            std::cout << std::endl;
        }

        // catching errors
        catch (std::logic_error &e)
        {
            // error message
            std::cout << std::endl;
            std::cout << e.what() << std::endl;
        }
    }

    return input;
}

bool validMutiplePlacement(std::vector<std::string> commands, Tile tiles[])
{
    // if (commands.size() > COMMAND_PLACE_LENGTH)
    // {
    //     bool place = findWord(COMMAND_PLACE, commands);
    //     bool at = findWord(STRING_AT, commands);

    //     split(commands, )
    // }
    return false;
}

bool uniqueTile(std::vector<std::shared_ptr<Tile>> tiles, std::shared_ptr<Tile> tile)
{
    bool unique = false;
    for (unsigned i = 0; i < tiles.size(); i++)
    {
        unique = tile == tiles.at(i);
    }
    return unique;
}