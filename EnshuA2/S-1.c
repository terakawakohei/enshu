#include <stdio.h>
#include <math.h>
#define N 1000
double a[N][N], x[N], y[N];
int main(void)
{
    int i, j;
    double error, ans;

    //Aの初期化
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            a[i][j] = i + j;
        }
    }

    //xの初期化

    for (i = 0; i < N; i++)
    {
        x[i] = i;
    }

    for (i = 0; i < N; i++)
    {
        y[i] = 0;
    }

    //計算

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            y[j] += a[i][j] * x[j];
        }
    }

    error = 0.0;
    for (i = 0; i < N; i++)
    {
        ans = i * 1 / 2 * i * (i + 1) + 1 / 6 * i * (i + 1) * (2 * i + 1);
        error = error + fabs(y[i] - ans);
        printf("ans = %10.5f/n", ans);
    }
    printf("error = %10.5f/n", error);

    return 0;
}