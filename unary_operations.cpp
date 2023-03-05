#include <math.h>


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
    return tan(operrand);
}

double opCot(double operrand)
{
    return tan((M_PI / 2) - operrand);
}

double opInversion(double operrand)
{
    return 1 / operrand;
}

double opSquareRoot(double operrand)
{
    return sqrt(operrand);
}

double opChangeSign(double operrand)
{
    return operrand * -1;
}
