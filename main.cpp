#include <iostream>
#include "functions.hpp"
using namespace std;

int main(int argc, char **argv)
{

    srand(time(NULL));
    welcomeScreen();
    char difficulty = difficultyDecision();

    if (difficulty == '1')
    {
        easyDifficultyGame();
    }
    else if (difficulty == '2')
    {
    }
    else if (difficulty == '3')
    {
    }
}
