#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    score = 0;
    hand = std::make_shared<LinkedList>();
}

Player::Player(std::string name, int score) : Player(name)
{
    this->score = score;
}

Player::~Player()
{
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
}

std::string Player::getName()
{
    return name;
}

std::shared_ptr<LinkedList> Player::getHand()
{
    return hand;
}