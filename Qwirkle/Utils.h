#ifndef ASSIGN2_UTILS_H
#define ASSIGN2_UTILS_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define COMMAND "command"
#define COMMAND_PLACE "place"
#define COMMAND_LOAD "load"
#define COMMAND_REPLACE "replace"
#define COMMAND_MENU "menu"
#define COMMAND_SAVE "save"
#define COMMAND_PLAYER_NAME "playername"
#define COMMAND_MUTI_PLACE "placeM"

#define INVALID_INPUT "Invalid Input"

#define QUIT "quit"
#define STRING_AT "at"

// delimiters for spilt
#define TILE_DELIMITER ","
#define BOARD_DELIMITER ", "
#define COMMAND_DELIMITER " "

#define NEW_GAME "1"
#define LOAD_GAME "2"
#define CREDITS "3"
#define MENU_QUIT "4"
#define FILE_EXTENSION ".txt"

#define COMMAND_PLACE_LENGTH 4
#define SHORT_CMD_LENGTH 2

#define DIRECTIONS 4
#define TILE_LENGTH 2
#define POSITION_LENGTH 3
#define OUT_OF_BOARD -1

// values for the tile bag
#define REPEAT_TILES 3
#define NUM_COLOURS 6
#define NUM_SHAPES 6
#define MAX_TILE_BAG_SIZE NUM_COLOURS *NUM_SHAPES *REPEAT_TILES

#define GOOD_BYE "Goodbye"

#define NOT_FOUND -1

std::string getValidInput(std::string type);

void validatePlayerName(std::string &input, bool &valid);

void split(std::vector<std::string> &commands, std::string command, std::string delimeter, int space = 1);

std::string getCommand(std::vector<std::string> &commands, std::string input);

void validatePlacement(std::vector<std::string> commands,
                       std::vector<std::shared_ptr<Tile>> &tiles);

bool validateReplace(std::vector<std::string> commands, Colour &c, Shape &s);

bool validateColour(char c);

bool validateShape(Shape s);

bool mutiCheck(std::vector<std::shared_ptr<Tile>> tiles);

bool checkPositions(std::vector<Tile> tiles);

bool validateTile(Tile t);

bool validatePosition(int row, int col);

bool validNeighbour(Tile first, Tile second);

bool validatePosition(Point p);

void validateFile(std::string &name, bool &valid);

void validateMenu(std::string &input, bool &valid);

int findWord(std::string str, std::vector<std::string> commands);

int intCharToInt(char c);

void validateCommand(std::vector<std::string> commands, std::string input, bool &valid);

void ruleCheck();

bool uniqueTile(std::vector<std::shared_ptr<Tile>> tiles, std::shared_ptr<Tile> tile);

#endif
