#include <conio.h>
#include <math.h>
#include <stdio.h>
#define N 3
#define EPS 0.0000001
double matrix[N][N + 1] = {{10, -3, 1, -1}, {2, -10, 3, -4}, {4, 1, 10, 21}};
void matrixix_show();
double MPI(double out[]);
int main()
{
    double out[N];
    for (int i = 0; i < N; i++) {
        out[i] = 0;
    }
    printf(" matrixix \n\n");
    matrixix_show();
    MPI(out);
    getch();
}

/* Выводит на экран матрицу */
void matrixix_show()
{
    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j <= N; ++j)
            printf("%8.3f  ", matrix[i][j]);
        printf("\n");
    }
}

/* Решение матрицы методом простых итераций */
double MPI(double out[])
{
    int i, j, k, step;
    float b[N], c[N][N], cx[N] = {0}, norm_b = 0, norm_c, tmp;
    /* Приводим матрицу к виду удобному для итераций */
    for (i = 0; i < N; ++i) {
        tmp = matrix[i][i];
        for (j = 0; j <= N; ++j)
            matrix[i][j] /= tmp;
    }
    /* Получаем матрицу С и вектор В */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j)
            c[i][j] = matrix[i][j];
        c[i][i] = 0;
        b[i] = matrix[i][N];
    }
    /* Выводим матрицу С на экран */
    printf("\n Vector C \n\n");
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j)
            printf("%6.3f  ", c[i][j]);
        printf("\n");
    }
    /* Выводим на экран вектор В */
    printf("\n Vector B \n\n");
    for (i = 0; i < N; ++i)
        printf("%6.3f\n", b[i]);
    /* Определяем норму матрицы С */
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j) {
            out[i] += fabs(c[j][i]);
            norm_c = out[0];
            if (out[i] > norm_c)
                norm_c = out[i];
        }
    /* Определяем норму вектора В */
    for (i = 0; i < N; ++i)
        norm_b += fabs(b[i]);
    /* Выводим нормы */
    printf("\n Norm C = %5.3f\n Norm B = %5.3f", norm_c, norm_b);
    /* Подсчёт кол-ва шагов */
    step = (log((1 - norm_c) * EPS / norm_b) / log(norm_c)) + 1;
    printf("\n N = %d", step);
    printf("\n");
    /* Нахождение решений исходной матрицы */

    double mass1[N];
    for (int i = 0; i < N; i++) {
        mass1[i] = 0;
    }
    for (i = 0; i < step; ++i) {
        for (j = 0; j < N; ++j)
            cx[j] = 0;
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                cx[j] += c[j][k] * mass1[k];
                mass1[j] = b[j] - cx[j];
            }
        }
        for (j = 0; j < N; j++) {
            printf("x%d=%1.15f  ", j + 1, mass1[j]);
        }
        printf("\n");
    }
    // printf("\n\n - Otveti - \n\n");
    // for (i = 0; i < N; i++)
    //     printf("x%d=%5.3f  ", i + 1, mass1[i]);
    return 0;
}