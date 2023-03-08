#include <math.h>
#include <stdexcept>

const double E = 0.000001;


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
