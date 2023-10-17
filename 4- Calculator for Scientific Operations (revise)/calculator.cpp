#include "calculator.h"

int Calculator::modulo(int value1, int value2) { return value1 % value2; }
double Calculator::evaluate()
{
    std::cout << "Enter the inline expression:";
    std::string str;
    std::cin >> str;

    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
            int tmp{0};

            while (i < str.length() && isdigit(str[i]))
            {
                tmp = (tmp * 10) + (str[i] - '0');
                i++;
            }

            values.push(tmp);
            i--;
        }
        else if (str[i] == '(')
            operators.push(str[i]);
        else if (str[i] == ' ')
            continue;
        else if (str[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                double value2 = values.top();
                values.pop();
                double value1 = values.top();
                values.pop();
                char oper = operators.top();
                operators.pop();
                values.push(calculate(value1, value2, oper));
            }

            if (!operators.empty())
                operators.pop();
        }
        else
        {
            while (!operators.empty() && precedence(operators.top()) >= precedence(str[i]))
            {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                double result{calculate(val1, val2, op)};
                values.push(result);
            }
            operators.push(str[i]);
        }
    }

    while (!operators.empty())
    {
        double value2 = values.top();
        values.pop();

        double value1 = values.top();
        values.pop();

        char oper = operators.top();
        operators.pop();

        double result{calculate(value1, value2, oper)};
        values.push(result);
    }

    return values.top();
}

int Calculator::precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/' || c == '%')
        return 2;
    else
        return 0;
}

double Calculator::calculate(double value1, double value2, char oper)
{
    switch (oper)
    {
    case '+':
        return value1 + value2;
    case '-':
        return value1 - value2;
    case '*':
        return value1 * value2;
    case '/':
        return value1 / value2;
    case '%':
        return modulo(value1, value2);
    default:
        return 0.0;
    }
}

Calculator::Calculator()
{
    double result = evaluate();
    std::cout << "Result is " << result << std::endl;
}
