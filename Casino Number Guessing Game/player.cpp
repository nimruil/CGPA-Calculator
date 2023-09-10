
#include "player.h"

Player::Player(std::string nameVal, float balanceVal) : name{nameVal}, balance{balanceVal}
{
    std::cout << "Welcome to the table, " << name << "! Your starting balance is " << balance << "." << std::endl;
}

std::string Player::getName() { return name; }
float Player::getBalance() { return balance; }
void Player::earnMoney(float amount) { balance += amount; }
void Player::loseMoney(float amount) { balance -= amount; }
