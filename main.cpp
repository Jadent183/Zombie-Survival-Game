#include <iostream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <windows.h>
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
void playerStartingPos(int, int, T, T **);
char getPlayerDirection();
template <typename T>
void movePlayer(int, int, char, Player<T>, T **);
template <typename T>
int getPlayerPosX(int, int, T, T **);
template <typename T>
int getPlayerPosY(int, int, T, T **);
template <typename T>
T setPlayerType(T);
template <typename T>
T getPlayerType(T);

int height = 5;
int width = 5;

int main(int argc, char **argv)
{
    srand(time(NULL));
    Player<char> player1;
    player1.setType('x');

    auto **board1 = makeBoard(height, width, 'f');
    playerStartingPos(height, width, player1.getType(), board1);
    player1.setPlayerX(getPlayerPosX(height, width, player1.getType(), board1));
    player1.setPlayerY(getPlayerPosY(height, width, player1.getType(), board1));

    printBoard(height, width, board1);

    while (1)
    {
        cout << player1.getPlayerX() << endl;
        cout << player1.getPlayerY() << endl;

        cout << "move a direction" << endl;
        // char direction = getPlayerDirection();

        movePlayer(height, width, getPlayerDirection(), player1, board1);

        printBoard(height, width, board1);
    }

    /*
    auto **board1 = makeBoard(height, width, "t");

    auto player1 = setPlayerType("l");
    placePlayer(height, width, player1, board1);
    // addRandom(height, width, 2, 7, board1);

    while (1)
    {
        printBoard(height, width, board1);
        char direction = getPlayerDirection();
        movePlayer(height, width, direction, player1, board1);
        cout << "test: " << player1 << endl;
        // printBoard(height, width, board1);
    }

    deleteBoard(height, width, board1);
    */
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
void playerStartingPos(int height, int width, T playerType, T **gameBoard)
{
    // Where the player starts on the board
    gameBoard[height / 2][width / 2] = playerType;
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
void movePlayer(int height, int width, char direction, Player<T> player, T **gameBoard)
{
    // int playerPosX = getPlayerPosX(height, width, player, gameBoard);
    // int playerPosY = getPlayerPosY(height, width, player, gameBoard);

    // int playerPosX = player.getPlayerX();
    // int playerPosY = player.getPlayerY();

    switch (direction)
    {
    case 'u':
        player.setPlayerY(player.getPlayerY() - 1); // up
        cout << "up X: " << player.getPlayerX() << " Y: " << player.getPlayerY() << endl;
        break;
    case 'l':
        player.setPlayerX(player.getPlayerX() - 1); // left
        cout << "left X: " << player.getPlayerX() << " Y: " << player.getPlayerY() << endl;
        break;
    case 'r':
        player.setPlayerX(player.getPlayerX() + 1); // right
        cout << "right X: " << player.getPlayerX() << " Y: " << player.getPlayerY() << endl;
        break;
    case 'd':
        player.setPlayerY(player.getPlayerY() + 1); // down
        cout << "down X: " << player.getPlayerX() << " Y: " << player.getPlayerY() << endl;
        break;
    default:
        break;
    }

    gameBoard[player.getPlayerY()][player.getPlayerX()] = player.getType();

    /*

    switch (direction)
    {
    case 'u':
        player.setType('x');
        gameBoard[playerPosX][playerPosY - 1] = 'x'; // up
        break;
    case 'l':
        player.setType('x');
        gameBoard[playerPosX - 1][playerPosY] = 'x'; // left
        break;
    case 'd':
        player.setType('x');
        gameBoard[playerPosX + 1][playerPosY] = 'x'; // right
        break;
    case 'r':
        player.setType('x');
        gameBoard[playerPosX][playerPosY + 1] = 'x'; // down
        break;
    default:
        break;
    }
    // cout << player << endl;
    */
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

template <typename T>
T setPlayerType(T value)
{
    T player = value;
    return player;
}
template <typename T>
T getPlayerType(T player)
{
    return player;
}
