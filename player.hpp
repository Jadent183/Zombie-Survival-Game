#include <iostream>
#define player_HPP
#pragma once
using namespace std;

template <typename T>
class Player
{
private:
    int posX;
    int posY;
    T type;

public:
    Player();
    Player(T);
    ~Player();

    void setType(T);
    T getType() const;
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int);
    void setPlayerY(int);
};

template <typename T>
Player<T>::Player()
{
    type = 'x';
}

template <typename T>
Player<T>::Player(T type)
{
    this->type = type;
    posY = 0;
    posX = 0;
}

template <typename T>
Player<T>::~Player() {}

template <typename T>
void Player<T>::setType(T type)
{
    this->type = type;
}

template <typename T>
T Player<T>::getType() const
{
    return type;
}

template <typename T>
int Player<T>::getPlayerX()
{
    return posX;
}

template <typename T>
int Player<T>::getPlayerY()
{
    return posY;
}

template <typename T>
void Player<T>::setPlayerX(int playerX)
{
    this->posX = playerX;
}

template <typename T>
void Player<T>::setPlayerY(int playerY)
{
    this->posY = playerY;
}
