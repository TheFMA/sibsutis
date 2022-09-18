#include <iostream>
#include <math.h>

#define e 0.0000001

using namespace std;

double func(double x, double y, double y_der)
{
    double res = (exp(x) + y + y_der) / 3;
    return res;
}

int main()
{
    double x = 0;
}