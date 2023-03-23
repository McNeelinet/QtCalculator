#include <math.h>
#include <stdexcept>

const double E = 0.000001;


double opMultiplication(double operrand1, double operrand2)
{
    return operrand1 * operrand2;
}

double opDivision(double operrand1, double operrand2)
{
    if (operrand2 == 0)
        throw std::logic_error("Результат деления на ноль неопределен.\n"
                               "Введите другое число.");
    return operrand1 / operrand2;
}

double opAddition(double operrand1, double operrand2)
{
    return operrand1 + operrand2;
}

double opSubstraction(double operrand1, double operrand2)
{
    return operrand1 - operrand2;
}

double opSin(double operrand)
{
    return sin(operrand);
}

double opCos(double operrand)
{
    return cos(operrand);
}

double opTan(double operrand)
{
    if (abs((fmod(operrand, M_PI)) - (M_PI / 2)) <= E)
        throw std::logic_error("Тангенс от этого числа неопределен.\n"
                               "Введите другое число.");
    return tan(operrand);
}

double opCot(double operrand)
{
    if (abs(fmod(operrand, M_PI)) <= E)
        throw std::logic_error("Котангенс от этого числа неопределен.\n"
                               "Введите другое число.");
    return tan((M_PI / 2) - operrand);
}

double opInversion(double operrand)
{
    if (operrand == 0)
        throw std::logic_error("Результат деления на ноль неопределен.\n"
                               "Введите другое число.");
    return 1 / operrand;
}

double opSquareRoot(double operrand)
{
    if (operrand < 0)
        throw std::logic_error("Вы попытались извлечь корень из отрицательного числа.\n"
                               "Введите другое число.");
    return sqrt(operrand);
}

double calculate(double operrand1, double operrand2, std::string operation)
{
    if (operation == "*")
        return opMultiplication(operrand1, operrand2);
    else if (operation == "/")
        return opDivision(operrand1, operrand2);
    else if (operation == "+")
        return opAddition(operrand1, operrand2);
    else if (operation == "-")
        return opSubstraction(operrand1, operrand2);
    else
        throw std::logic_error("Неизвестная операция.");
}

double calculate(double operrand, std::string operation)
{
    if (operation == "sin")
        return opSin(operrand);
    else if (operation == "cos")
        return opCos(operrand);
    else if (operation == "tan")
        return opTan(operrand);
    else if (operation == "cot")
        return opCot(operrand);
    else if (operation == "1/x")
        return opInversion(operrand);
    else if (operation == "√")
        return opSquareRoot(operrand);
    else
        throw std::logic_error("Неизвестная операция.");
}
