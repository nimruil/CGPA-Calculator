#include <iostream>
#include <time.h>

#include "player.h"
#include "bet.h"

// depending on difficulty of the game, player tries to guess  the number comp has chosen and bets money
// on this number. If he guesses correct he earns money. This money is directly related to the difficulty.
// Game ends when user wants to cash in or is bankrupt.

void introduction();
int defineUpperLimit();
int determineNumber(int);
Player initializePlayer();
void play(bet &, int, int);
void evaluate(bet &, int, int, Player &);
bool enoughOrNot(Player &);
void outro();

const float rewardRate = 0.1f;

int main()
{
    introduction();
    Player player = initializePlayer();
    bet currentBet;
    bool keepGoing{1};

    while (keepGoing)
    {
        int upperlimit = defineUpperLimit();
        int chosenNumber = determineNumber(upperlimit);
        play(currentBet, player.getBalance(), upperlimit);
        evaluate(currentBet, chosenNumber, upperlimit, player);
        keepGoing = enoughOrNot(player);
    }
    outro();
    return 0;
}

void introduction()
{
    std::cout << "This is a game about guessing numbers.\n"
              << "You decide a number and the house chooses a random number between 0 and this number(0 and this number included)\n"
              << "The reward is " << rewardRate * 100 << "\% times upper limit.\n"
              << std::endl;
}

int defineUpperLimit()
{
    std::cout << "--------------------------------------------" << std::endl;
    while (1)
    {
        std::cout << "What would you like the upper limit to be?: ";
        int upperlimit{0};
        std::cin >> upperlimit;
        if (upperlimit <= 0)
            std::cout << "Upper limit should be greater than zero." << std::endl;
        else
            return upperlimit;
    }
}

int determineNumber(int num)
{
    int number{0};
    srand(time(NULL));
    number = rand() % num;
    return number;
}

Player initializePlayer()
{
    std::cout << "First, enter your name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Please enter your starting balance: ";
    float balance;
    std::cin >> balance;
    Player object{name, balance};
    return object;
}

void play(bet &currentBet, int playerBalance, int upperlimit)
{
    while (1)
    {
        std::cout << "Which number do you think the house guessed?: ";
        std::cin >> currentBet.number;
        if (currentBet.number >= 0 && currentBet.number <= upperlimit)
            break;
        else
            std::cout << "That number is smaller than zero or larger than upper limit." << std::endl;
    }
    while (1)
    {
        std::cout << "How much would you bet on it?: ";
        std::cin >> currentBet.betAmount;
        if (currentBet.betAmount <= playerBalance)
            break;
        else
            std::cout << "You don't have that much money!" << std::endl;
    }
}

void evaluate(bet &currentBet, int chosenNumber, int upperlimit, Player &player)
{
    if (currentBet.number == chosenNumber)
    {
        std::cout << "You guessed correct! The number was " << chosenNumber << "." << std::endl;
        float prize = currentBet.betAmount * upperlimit * rewardRate;
        std::cout << "You have won the prize of " << prize << ". ";
        player.earnMoney(prize);
    }
    else
    {
        std::cout << "You guessed wrong! The number was " << chosenNumber << "." << std::endl;
        std::cout << "You lost your bet of " << currentBet.betAmount << "." << std::endl;
        player.loseMoney(currentBet.betAmount);
    }
}

bool enoughOrNot(Player &player)
{
    std::cout << "Your balance is " << player.getBalance() << "." << std::endl;

    if (player.getBalance() > 0)
    {
        std::cout << "Do you wish to play another game? (y/n):";
        char input{' '};
        std::cin >> input;
        if (input == 'y')
            return 1;
        else
            return 0;
    }
    else
    {
        std::cout << "Your balance is zero. "
                  << "Press x to start saving money. ";
        char input;
        std::cin >> input;
        return 0;
    }
}

void outro()
{
    char input;
    std::cout << "Press x to terminate.. ";
    std::cin >> input;
}
