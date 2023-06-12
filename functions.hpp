#pragma once
#include <iostream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Array2D.hpp"
#include "player.hpp"
#include "macros.h"
using namespace std;
#define functions_hpp

template <typename T>
void playerStartingPos(int, int, Player<T> &, Array2D<Player<T>> &);
char getPlayerDirection();
template <typename T>
void movePlayer(char, Player<T> &, Array2D<Player<T>> &);
template <typename T>
bool validMove(char, Player<T> &, Array2D<Player<T>> &);
template <typename T>
void zombieStartingPos(Player<T> &, Player<T> &, Array2D<Player<T>> &);
template <typename T>
char checkCollisions(Array2D<Player<T>> &, int, int);
void zombieDeath();
template <typename T>
void zombieMove(Array2D<Player<T>> &, Player<T> &);
void welcomeScreen();
char difficultyDecision();

void easyDifficultyGame();

int height = 5;
int width = 5;
char tile = ' '; // primary background tile character
bool keepPlaying;

void easyDifficultyGame()
{
    Array2D<Player<char>> board2(height, width);
    board2.fill(tile);

    Player<char> player;
    player.setType('l');

    Player<char> zombie;
    zombie.setType('z');

    playerStartingPos(3, 3, player, board2);
    zombieStartingPos(player, zombie, board2);

    keepPlaying = true;
    while (keepPlaying == true)
    {

        // Your turn
        board2.print();
        cout << setw(3) << BOLDBLUE << "Your turn, move a direction" << RESET << endl;
        movePlayer(getPlayerDirection(), player, board2);
        board2.print();

        // Zombie turn
        cout << setw(3) << BOLDGREEN << "Zombies turn" << RESET << endl;
        Sleep(750);
        zombieMove(board2, zombie);
        // zombieStartingPos(player, zombie, board2);
    }
}

char difficultyDecision()
{
    char ch = getch();

    while ((ch != '1') && (ch != '2') && (ch != '3'))
    {
        ch = getch();
    }
    return ch;
}

void welcomeScreen()
{
    cout << setw(4) << BOLDRED << "WELCOME TO ";
    Sleep(450);
    cout << setw(5) << BOLDGREEN << "TILE SURVIVOR" << RESET << endl;
    Sleep(1000);
    for (int i = 0; i < 50; i++)
    {
        cout << BOLDWHITE << "*";
        Sleep(20);
    }
    cout << RESET << endl;
    cout << RESET << endl;
    cout << setw(2) << BOLDWHITE << "CHOOSE DIFFICULTY!! " << RESET << endl;
    Sleep(800);
    cout << setw(2) << BOLDGREEN << "Press 1 for easy" << RESET << endl;
    Sleep(800);
    cout << setw(2) << BOLDBLUE << "Press 2 for normal" << RESET << endl;
    Sleep(800);
    cout << setw(2) << BOLDRED << "Press 3 for hard" << RESET << endl;
}

template <typename T>
void zombieMove(Array2D<Player<T>> &gameBoard, Player<T> &zombie)
{
    gameBoard.setValue(zombie.getPlayerY(), zombie.getPlayerX(), tile);
    // todo: create a random direction in 1 of 5 ways with the 5th being no direction
    int randDirection = (rand() % 5);
    char direction;
    // update the zombies position on the board
    // 1 = up, 2 = left, 3 = right, 4 = down, 5 = no move.

    switch (randDirection)
    {
    case 1:
        direction = 'u';
        if (validMove(direction, zombie, gameBoard))
        {
            if (checkCollisions(gameBoard, zombie.getPlayerY() - 1, zombie.getPlayerX()) == 'l') // zombie hits player
            {
                zombieDeath();
            }
            else
            {
                zombie.setPlayerY(zombie.getPlayerY() - 1); // up
            }
        }
        break;
    case 2:
        direction = 'l';
        if (validMove(direction, zombie, gameBoard))
        {
            if (checkCollisions(gameBoard, zombie.getPlayerY(), zombie.getPlayerX() - 1) == 'l') // zombie hits player
            {
                zombieDeath();
            }
            else
            {
                zombie.setPlayerX(zombie.getPlayerX() - 1); // left
            }
        }
        break;
    case 3:
        direction = 'r';
        if (validMove(direction, zombie, gameBoard))
        {
            if (checkCollisions(gameBoard, zombie.getPlayerY(), zombie.getPlayerX() - 1) == 'l') // zombie hits player
            {
                zombieDeath();
            }
            else
            {
                zombie.setPlayerX(zombie.getPlayerX() + 1); // right
            }
        }
        break;
    case 4:
        direction = 'd';
        if (validMove(direction, zombie, gameBoard))
        {
            if (checkCollisions(gameBoard, zombie.getPlayerY() + 1, zombie.getPlayerX()) == 'l') // zombie hits player
            {
                zombieDeath();
            }
            else
            {
                zombie.setPlayerY(zombie.getPlayerY() + 1); // down
            }
        }
        break;
    case 5:
        break; // no move
    default:
        break;
    }
    gameBoard.setValue(zombie.getPlayerY(), zombie.getPlayerX(), zombie.getType());
}

template <typename T>
char checkCollisions(Array2D<Player<T>> &gameBoard, int row, int col)
{
    if (gameBoard.getValue(row, col) == 'z')
    {
        return 'z';
    }
    if (gameBoard.getValue(row, col) == 'l')
    {
        return 'l';
    }

    return 'n';
}

template <typename T>
void zombieStartingPos(Player<T> &player, Player<T> &zombie, Array2D<Player<T>> &gameBoard)
{
    int randY = (rand() % gameBoard.getRow());
    int randX = (rand() % gameBoard.getCol());

    if ((randX > player.getPlayerX() + 1) || (randX < player.getPlayerX() - 1) || (randY > player.getPlayerY() + 1) || (randY < player.getPlayerY() - 1) || (randX != player.getPlayerX()) || (randY != player.getPlayerY()))
    {
        gameBoard.setValue(randY, randX, zombie.getType());
        zombie.setPlayerX(randX);
        zombie.setPlayerY(randY);
    }
    else
    {
        int randY = (rand() % gameBoard.getRow());
        int randX = (rand() % gameBoard.getCol());

        if ((randX > player.getPlayerX() + 1) || (randX < player.getPlayerX() - 1) || (randY > player.getPlayerY() + 1) || (randY < player.getPlayerY() - 1) || (randX != player.getPlayerX()) || (randY != player.getPlayerY()))
        {
            gameBoard.setValue(randY, randX, zombie.getType());
            zombie.setPlayerX(randX);
            zombie.setPlayerY(randY);
        }
    }
}

template <typename T>
void pBoard(Array2D<T> board)
{
    for (int i = 0; i < board.getRow(); i++)
    {
        for (int j = 0; j < board.getCol(); j++)
        {
            cout << board.getValue(i, j) << endl;
        }
        cout << endl;
    }
}

template <typename T>
void playerStartingPos(int X, int Y, Player<T> &player, Array2D<Player<T>> &board)
{
    // Where the player starts on the board
    board.setValue(Y, X, player.getType());
    player.setPlayerX(X);
    player.setPlayerY(Y);
}

char getPlayerDirection()
{
    // get the direction taken from the user's arrow keys
    int ch = getch();
    if (ch == 224)
    {
        ch = getch();
        switch (ch)
        {
        case 72:
            return 'u';
            break;
        case 80:
            return 'd';
            break;
        case 77:
            return 'r';
            break;
        case 75:
            return 'l';
            break;
        default:
            return 'n';
        }
    }
    return ch;
}

template <typename T>
void movePlayer(char direction, Player<T> &player, Array2D<Player<T>> &gameBoard)
{
    // update the previous tile that the player moved from
    gameBoard.setValue(player.getPlayerY(), player.getPlayerX(), tile);

    // update the players new position given from the keyboard
    switch (direction)
    {
    case 'u':
        if (validMove(direction, player, gameBoard))
        {
            if (checkCollisions(gameBoard, player.getPlayerY() - 1, player.getPlayerX()) == 'z') // player hits zombie
            {
                zombieDeath();
            }
            else
            {
                player.setPlayerY(player.getPlayerY() - 1); // move up
            }
        }
        else
            cout << "invalid move: " << endl;
        break;
    case 'l':
        if (validMove(direction, player, gameBoard))
        {
            if (checkCollisions(gameBoard, player.getPlayerY(), player.getPlayerX() - 1) == 'z') // player hits zombie
            {
                zombieDeath();
            }
            else
            {
                player.setPlayerX(player.getPlayerX() - 1); // left
            }
        }
        else
            cout << "invalid move: " << endl;

        break;
    case 'r':
        if (validMove(direction, player, gameBoard))
        {
            if (checkCollisions(gameBoard, player.getPlayerY(), player.getPlayerX() + 1) == 'z') // player hits zombie
            {
                zombieDeath();
            }
            else
            {
                player.setPlayerX(player.getPlayerX() + 1); // right
            }
        }
        else
            cout << "invalid move: " << endl;
        break;
    case 'd':
        if (validMove(direction, player, gameBoard))
        {
            if (checkCollisions(gameBoard, player.getPlayerY() + 1, player.getPlayerX()) == 'z') // player hits zombie
            {
                zombieDeath();
            }
            else
            {
                player.setPlayerY(player.getPlayerY() + 1); // down
            }
        }
        else
            cout << "invalid move: " << endl;
        break;
    case 'q':
        keepPlaying = false;
    default:
        break;
    }

    // update the players current position on the gameboard
    gameBoard.setValue(player.getPlayerY(), player.getPlayerX(), player.getType());
}

void zombieDeath()
{
    keepPlaying = false;
    cout << BOLDGREEN << "You died to a zombie" << RESET << endl;
}

template <typename T>
bool validMove(char direction, Player<T> &player, Array2D<Player<T>> &gameBoard)
{
    switch (direction)
    {
    case 'u':
        if (player.getPlayerY() - 1 >= 0) // up
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 'l':
        if (player.getPlayerX() - 1 >= 0) // left
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 'r':
        if (player.getPlayerX() + 1 <= gameBoard.getCol() - 1) // right
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 'd':
        if (player.getPlayerY() + 1 <= gameBoard.getRow() - 1) // down
        {
            return true;
        }
        else
        {
            cout << "invalid move: " << endl;
            return false;
        }
        break;
    default:
        break;
    }
    cout << "nothring haooend: " << endl;

    return false;
}
