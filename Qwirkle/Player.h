#ifndef PLAYER
#define PLAYER
#include "LinkedList.h"

#define MAXHAND 6
class Player
{
public:
    // constructors and destructors
    Player(std::string name);
    Player(std::string name, int score);
    ~Player();

    // get player score
    int getScore();

    // set player score
    void setScore(int score);

    // get player name
    std::string getName();

    // get playr's hand
    std::shared_ptr<LinkedList> getHand();

private:
    std::shared_ptr<LinkedList> hand;

    int score;

    std::string name;
};

#endif
