#include "QwirkleGame.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>

#define EXIT_SUCCESS 0

void printCredits();

int main(void)
{
   QwirkleGame game;

   // welcome message
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;

   bool keepPlaying = true;
   try
   {
      while (keepPlaying)
      {
         // main menu
         std::cout << "Menu" << std::endl;
         std::cout << "----" << std::endl;

         std::cout << "1. New Game" << std::endl;
         std::cout << "2. Load Game" << std::endl;
         std::cout << "3. Credits" << std::endl;
         std::cout << "4. Quit" << std::endl;

         std::cout << std::endl;
         std::string choice = getValidInput(COMMAND_MENU);

         if (choice == NEW_GAME)
         {
            // playing a new game
            game.startGame();
            game.playGame();
         }
         else if (choice == LOAD_GAME)
         {
            // load up game
            std::cout << "Enter the filename from which load a game" << std::endl;
            std::string fileName = getValidInput(COMMAND_LOAD);
            game.loadGame(fileName);
         }
         else if (choice == CREDITS)
         {
            printCredits();
         }
         else if (choice == MENU_QUIT)
         {
            keepPlaying = false;
            std::cout << GOOD_BYE << std::endl;
         }
      }
   }
   catch (std::exception &e)
   {
      std::cout << std::endl;
      std::cout << GOOD_BYE << std::endl;
   }

   return EXIT_SUCCESS;
}

void printCredits()
{
   std::cout << "------------------------------------" << std::endl;
   std::cout << "Name: "
             << "Dushyant Mallya" << std::endl;
   std::cout << "Student ID: "
             << "s3842605" << std::endl;
   std::cout << "Email: "
             << "s3842605@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   std::cout << "Name: "
             << "Charlotte Stockfeld" << std::endl;
   std::cout << "Student ID: "
             << "s3722139" << std::endl;
   std::cout << "Email: "
             << "s3722139@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   std::cout << "Name: "
             << "Minggang Dong" << std::endl;
   std::cout << "Student ID: "
             << "s3843573" << std::endl;
   std::cout << "Email: "
             << "s3843573@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   std::cout << "Name: "
             << "William Hu" << std::endl;
   std::cout << "Student ID: "
             << "s3856557" << std::endl;
   std::cout << "Email: "
             << "s3856557@student.rmit.edu.au" << std::endl;
   std::cout << "------------------------------------" << std::endl;
   std::cout << std::endl;
}
