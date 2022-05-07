#include <source.hpp>

int src::add(int a, int b)
{
    return a+b;
}

int src::subtract(int a, int b)
{
    return a-b;
}

int src::multiply(int a, int b)
{
    return a*b;
}

int src::divide(int a, int b)
{
    return b != 0 ? a/b : 0;
}