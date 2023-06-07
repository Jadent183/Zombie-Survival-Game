#include <iostream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Array2D.hpp"
#include "player.hpp"
#include "macros.h"
using namespace std;

template <typename T>
T **makeBoard(int, int, T);
template <typename T>
void printBoard(int, int, T **);
template <typename T>
void deleteBoard(int, int, T **);
template <typename T>
void addRandom(int, int, int, T, T **);
template <typename T>
void playerStartingPos(int, int, Player<T> &, Array2D<Player<T>> &);
char getPlayerDirection();
template <typename T>
void movePlayer(char, Player<T> &, Array2D<Player<T>> &);
template <typename T>
int getPlayerPosX(int, int, T, T **);
template <typename T>
int getPlayerPosY(int, int, T, T **);
template <typename T>
bool validMove(char, Player<T> &, Array2D<Player<T>> &);

template <typename T>
void pBoard(Array2D<T>);

int height = 5;
int width = 5;

int main(int argc, char **argv)
{

    Array2D<Player<char>> board2(height, width);
    board2.fill('o');

    Player<char> player;
    player.setType('x');

    playerStartingPos(2, 2, player, board2);

    board2.print();

    while (1)
    {
        cout << "move a direction" << endl;
        movePlayer(getPlayerDirection(), player, board2);

        board2.print();
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
T **makeBoard(int height, int width, T value)
{
    // allocate memory for game board
    T **gameBoard = new T *[height];

    // allocate memory for gameBoard[height][width]
    for (int i = 0; i < height; i++)
    {
        gameBoard[i] = new T[width];
    }

    // fill the gameBoard
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gameBoard[i][j] = value;
        }
    }

    return gameBoard;
}

template <typename T>
void printBoard(int height, int width, T **gameBoard)
{
    // print top row lines
    cout << setw(1) << " ";
    for (int k = 0; k < width * 2; k++)
    {
        cout << setw(2) << BOLDWHITE << "--";
    }
    cout << "-";
    cout << endl;

    // print the gameBoard
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << setw(2) << "|" << RESET;                          // right side line
            cout << BOLDGREEN << setw(2) << gameBoard[i][j] << RESET; // gameboard values
        }
        cout << BOLDWHITE << setw(2) << "|"; // far right side line
        cout << endl;
        cout << setw(1) << " "; // whitespace
        for (int k = 0; k < width * 2; k++)
        {
            cout << setw(2) << "--"; // in between row lines
        }
        cout << "-" << RESET; // bottom row lines
        cout << endl;
    }
}

template <typename T>
void deleteBoard(int height, int width, T **gameBoard)
{
    // delete the gameBaord
    for (int i = 0; i < height; i++)
    {
        delete[] gameBoard[i];
    }
    delete[] gameBoard;
}

template <typename T>
void addRandom(int height, int width, int chance, T value, T **gameBoard)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((rand() % chance == 1) && (gameBoard[i][j] == 0))
            {
                gameBoard[i][j] = value;
            }
        }
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
    return 'n';
}

template <typename T>
void movePlayer(char direction, Player<T> &player, Array2D<Player<T>> &gameBoard)
{

    switch (direction)
    {
    case 'u':
        if (validMove(direction, player, gameBoard))
        {
            player.setPlayerY(player.getPlayerY() - 1); // up
        }
        break;
    case 'l':
        if (validMove(direction, player, gameBoard))
        {
            player.setPlayerX(player.getPlayerX() - 1); // left
        }
        break;
    case 'r':
        if (validMove(direction, player, gameBoard))
        {
            player.setPlayerX(player.getPlayerX() + 1); // right
        }
        break;
    case 'd':
        if (validMove(direction, player, gameBoard))
        {
            player.setPlayerY(player.getPlayerY() + 1); // down
        }
        break;
    default:
        break;
    }
    gameBoard.setValue(player.getPlayerY(), player.getPlayerX(), player.getType());
}

template <typename T>
bool validMove(char direction, Player<T> &player, Array2D<Player<T>> &gameBoard)
{
    switch (direction)
    {
    case 'u':
        if (player.getPlayerY() - 1 >= 0)
        {
            return true;
        }
        else
        {
            cout << "invalid move: " << endl;
            return false;
        }
        break;
    case 'l':
        if (player.getPlayerX() - 1 >= 0)
        {
            return true;
        }
        else
        {
            cout << "invalid move: " << endl;
            return false;
        }
        break;
    case 'r':
        if (player.getPlayerX() + 1 <= gameBoard.getCol() - 1)
        {
            return true;
        }
        else
        {
            cout << "invalid move: " << endl;
            return false;
        }
        break;
    case 'd':
        if (player.getPlayerY() + 1 <= gameBoard.getRow() - 1)
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

template <typename T>
int getPlayerPosX(int height, int width, T playerType, T **gameBoard)
{
    // width
    int playerPosX;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (gameBoard[i][j] == playerType)
            {
                int playerPosX = j;
                return playerPosX;
            }
        }
    }
    return playerPosX;
}
template <typename T>
int getPlayerPosY(int height, int width, T playerType, T **gameBoard)
{
    // height
    int playerPosY;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (gameBoard[i][j] == playerType)
            {
                int playerPosY = i;
                return playerPosY;
            }
        }
    }
    return playerPosY;
}
