#pragma once
#include <iostream>
#include <iomanip>
#include "macros.h"
using namespace std;
#define array2D_HPP

template <typename T>
class Array2D
{
private:
    T **data;
    int rows;
    int cols;

public:
    Array2D(int numRows, int numCols) : rows(numRows), cols(numCols)
    {
        // Allocate memory for the 2D array
        data = new T *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
        }
    }

    ~Array2D()
    {
        // Deallocate memory for the 2D array
        for (int i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    void setValue(int row, int col, T value)
    {
        data[row][col] = value;
    }

    T getValue(int row, int col)
    {
        return data[row][col];
    }

    int getRow()
    {
        return rows;
    }

    int getCol()
    {
        return cols;
    }

    void fill(T value)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = value;
            }
        }
    }

    void print()
    {
        // print top row lines
        cout << setw(1) << " ";
        for (int k = 0; k < cols * 2; k++)
        {
            cout << setw(2) << BOLDWHITE << "--";
        }
        cout << "-";
        cout << endl;

        // print the gameBoard
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << setw(2) << "|" << RESET; // right side line

                if (data[i][j] == 'z') // green for zombies
                {
                    cout << BOLDGREEN << setw(2) << data[i][j] << RESET; // gameboard values
                }
                else if (data[i][j] == 'l') // blue for Player
                {
                    cout << BOLDBLUE << setw(2) << data[i][j] << RESET; // gameboard values
                }
                else // white for everything else
                {
                    cout << BOLDWHITE << setw(2) << data[i][j] << RESET; // gameboard values
                }
            }
            cout << BOLDWHITE << setw(2) << "|"; // far right side line
            cout << endl;
            cout << setw(1) << " "; // whitespace
            for (int k = 0; k < cols * 2; k++)
            {
                cout << setw(2) << "--"; // in between row lines
            }
            cout << "-" << RESET; // bottom row lines
            cout << endl;
        }
    }
};