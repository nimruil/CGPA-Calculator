#include <iostream>

#include "calculator.h"

void outro();

int main()
{
    Calculator calc;
    outro();
    return 0;
}

void outro()
{
    char input;
    std::cout << "Type any character to terminate.. ";
    std::cin >> input;
}
