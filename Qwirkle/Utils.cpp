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
        throw std::logic_error(INVALID_INPUT);
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
            throw std::logic_error(INVALID_INPUT);
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
    return (c >= STARTPOINT && c <= ENDPOINT);
}

bool validatePosition(int row, int col)
{
    // checking if the row and col is out of bound
    bool xBound = (col > OUT_OF_BOARD && col < DIMENSIONS);
    bool yBound = (row > OUT_OF_BOARD && row < DIMENSIONS);
    return xBound && yBound;
}

bool findWord(std::string str, std::vector<std::string> commands)
{
    bool match = false;
    for (int i = 0; i < (int)commands.size(); i++)
    {
        if (commands[i] == str)
        {
            match = true;
        }
    }
    return match;
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
        bool replace = findWord(COMMAND_REPLACE, commands);
        if (replace)
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
        throw std::logic_error(INVALID_INPUT);
    }
    return commands[0];
}

bool validatePlacement(std::vector<std::string> commands, Colour &c, Shape &s, Point &p)
{

    bool valid = false;
    if (commands.size() == COMMAND_PLACE_LENGTH)
    {
        bool place = findWord(COMMAND_PLACE, commands);
        bool at = findWord(STRING_AT, commands);

        if (place && at)
        {
            // get tile
            std::string tileInfo = commands[1];
            c = tileInfo.at(0);
            s = intCharToInt(tileInfo.at(1));

            // get position
            std::string position = commands[3];
            char row = position.at(0);

            //NOTE SHAPE MAY BE 2 DIGIT
            int column = intCharToInt(position.at(1));
            if ((int)position.size() <= POSITION_LENGTH)
            {
                // coordinate above 9
                if (position.size() > 2)
                {
                    column = column * 10 + intCharToInt(position.at(2));
                }
            }
            else
            {
                column = OUT_OF_BOARD;
            }
            p = Point(row, column);
            valid = validateColour(c) && validateShape(s) && validatePosition(p.getRow(), column);
        }
    }
    if (!valid)
    {
        throw std::logic_error(INVALID_INPUT);
    }
    return valid;
}

void validateCommand(std::vector<std::string> commands, std::string input, bool &valid)
{
    // checking if input matches any command
    if (!(commands.size() < SHORT_CMD_LENGTH))
    {
        if (commands.at(0) == COMMAND_PLACE && (int)commands.size() == COMMAND_PLACE_LENGTH)
        {
            valid = (commands.at(2) == STRING_AT) ? true : false;
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