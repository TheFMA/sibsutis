#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#define EPS pow(10, -6)
#define E 2.7182818284

using namespace std;
double function(double x, double y, double yy)
{
    return (pow(E, x) + y + yy) / 3;
}
void Runge_Kytta_by_time(double x[1], double y[2])
{
    double h = 0.1;
    int counter = 0;
    int k;
    double Yh[2], Yh2[2], Ykor[2], yh, Y_a[2];
    double step = h, X, Xh2;

    while (counter < 1 / (2 * step)) {
        counter = 0;

        for (int i = 0; i < 2; i++) {
            Yh[i] = y[i];
            Yh2[i] = y[i];
        }
        printf("X        ");
        printf("       Y    ");
        printf("       Y'    ");
        printf("\n");
        printf("%.7f    ", x[0]);
        printf("%.7f    ", Yh[0]);
        printf("%.7f    ", Yh[1]);
        printf("\n");

        for (X = x[0]; X < 1 - step + EPS; X += step) {
            for (int i = 0; i < 2; i++) {
                if (i == 0)
                    Y_a[i] = Yh[i] + step / 2 * Yh[i + 1];
                else
                    Y_a[i] = Yh[i] + step / 2 * function(X, Yh[0], Yh[1]);
            }
            for (int i = 0; i < 2; i++) {
                if (i == 0)
                    Yh[i] += step * Y_a[i + 1];
                else
                    Yh[i] += step * function(X + step / 2, Y_a[0], Y_a[1]);
            }

            for (Xh2 = X, k = 0; k < 2; k++, Xh2 += step / 2) {
                for (int i = 1; i < 2; i++) {
                    if (i == 0)
                        Y_a[i] = Yh2[i] + step / 4 * Yh2[i + 1];
                    else
                        Y_a[i] = Yh2[i]
                                + step / 4 * function(Xh2, Yh2[0], Yh2[1]);
                }

                for (int i = 0; i < 2; i++) {
                    if (i == 0)
                        Yh2[i] += step / 2 * Y_a[i + 1];
                    else
                        Yh2[i] += step / 2
                                * function(Xh2 + step / 4, Y_a[0], Y_a[1]);
                }
            }
            if (fabs(Yh[0] - Yh2[0]) < 3 * EPS) {
                counter++;
            }

            Ykor[0] = Yh2[0] + 1 / 3 * (Yh2[0] + Yh[0]);
            Ykor[1] = Yh2[1] + 1 / 3 * (Yh2[1] + Yh[1]);

            printf("%.7f    ", X + step);
            printf("%.7f    ", Ykor[0]);
            printf("%.7f    ", Ykor[1]);
            printf("\n");
        }
        printf("h = %f    ", step);
        printf("\n");
        step /= 2;
    }
}

int main()
{
    double x[1] = {0};
    double y[2] = {1, 1};
    Runge_Kytta_by_time(x, y);
    system("pause");
    return 0;
}