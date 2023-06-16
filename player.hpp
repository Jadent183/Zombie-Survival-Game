#include <iostream>
#define Player_HPP
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
    Player(const T &x, const T &y, const T &PlayerType) : posX(x), posY(y), type(PlayerType) {}

    Player();
    Player(T);
    ~Player();

    void setType(T);
    T getType() const;
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int);
    void setPlayerY(int);

    friend class Array2D<Player<T>>;

    friend std::ostream &operator<<(std::ostream &os, const Player<T> &Player)
    {
        os << Player.type;
        return os;
    }
    friend bool operator==(const Player<T> &lhs, const Player<T> &rhs)
    {
        return (lhs.posX == rhs.posX) && (lhs.posY == rhs.posY) && (lhs.type == rhs.type);
    }
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
void Player<T>::setPlayerX(int PlayerX)
{
    this->posX = PlayerX;
}

template <typename T>
void Player<T>::setPlayerY(int PlayerY)
{
    this->posY = PlayerY;
}
