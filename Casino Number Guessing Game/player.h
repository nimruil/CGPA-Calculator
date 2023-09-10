#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <string>

class Player
{
private:
    std::string name;
    float balance;

public:
    Player(std::string, float);
    std::string getName();
    float getBalance();
    void earnMoney(float);
    void loseMoney(float);
};

#endif //_PLAYER_H_
