#include <iostream>
#include <cstdlib>
#include <time.h>

char userHand();
char computerHand();
int compareHands(char, char);
void announceResults(int);

int main()
{
    std::cout << "Welcome to Rock Paper Scissors!" << std::endl;

    while (1)
    {
        char player = userHand();
        char computer = computerHand();
        int victory = compareHands(player, computer);
        announceResults(victory);

        std::cout << "Do you wish to play one more round? (y/n): ";
        char input{' '};
        std::cin >> input;
        if (input == 'n')
            break;
    }
    return 0;
}

char userHand()
{
    std::cout << "Please make your choice(R, P, S): ";
    char input{' '};
    std::cin >> input;

    if (input == 'r')
        input = 'R';
    else if (input == 'p')
        input = 'P';
    else if (input == 's')
        input = 'S';

    return input;
}

char computerHand()
{
    srand(time(0));
    int rnd = rand() % (3);
    char hand{' '};

    switch (rnd)
    {
    case 0:
        hand = 'R';
        break;
    case 1:
        hand = 'P';
        break;
    case 2:
        hand = 'S';
        break;
    default:
        break;
    }

    return hand;
}

int compareHands(char user, char comp)
{
    int victory{0};
    std::cout << "Player hand is " << user << ", comp hand is " << comp << std::endl;

    if (user == comp)
        return 2;
    else
    {
        if (user == 'R' && comp == 'P')
            victory = 0;
        else if (user == 'R' && comp == 'S')
            victory = 1;
        else if (user == 'P' && comp == 'R')
            victory = 1;
        else if (user == 'P' && comp == 'S')
            victory = 0;
        else if (user == 'S' && comp == 'R')
            victory = 0;
        else if (user == 'S' && comp == 'P')
            victory = 1;
    }

    return victory;
}

void announceResults(int victory)
{
    if (victory == 1)
        std::cout << "You won!" << std::endl;
    else if (!victory)
        std::cout << "You lost!" << std::endl;
    else
        std::cout << "Draw!" << std::endl;
}
