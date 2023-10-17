#include <bits/stdc++.h>

class Calculator
{
private:
    std::stack<double> values;
    std::stack<char> operators;

public:
    double evaluate();
    int precedence(char);
    int modulo(int, int);
    double calculate(double, double, char);
    Calculator();
};
