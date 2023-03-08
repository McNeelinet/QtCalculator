#include <stdexcept>


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
