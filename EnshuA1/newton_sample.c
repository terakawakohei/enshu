#include <stdio.h>
#include <stdlib.h>
#include <math.h>        /* ターミナルでコンパイルする際は gcc -lm newton.c -o newtonというように"-lm"オプションを付けてください．*/
#define EPSIRON1 0.00001 /* 収束・発散判定に用いる値は適宜決めてください */
#define EPSIRON2 0.00001
#define K_MAX 100 /* 反復回数は適宜決めてください */

double nonlinear_func(double x) /* 非線形関数の計算用関数 */
{

    return 0.45 * pow(x, 3) - 6 * x * cos(0.5 * x) + 4;
}

double nonlinear_func_diff(double x) /* 微分した関数の計算用関数 */
{

    return 1.35 * pow(x, 2) - 6 * cos(0.5 * x) + 3 * x * sin(0.5 * x);
}

int main(void)
{
    double init_x, x[K_MAX + 1];
    int k;          /* カウント用 */
    int flag_step1; /* フラグ用の変数(必要ならば使ってください) */

    printf("Inital value = ");
    scanf("%lf", &init_x);
    x[0] = init_x;
    k = 0;
    while (k < K_MAX)
    {
        if (flag_step1 == 0)
        {
            /* 初期解の再設定 */

            printf("初期解を再設定します\n");
            printf("Inital value = ");
            scanf("%lf", &init_x);

            k = 0;
            x[0] = init_x;
        }
        else
        {
            /* ステップ2 */
            x[k + 1] = x[k] - nonlinear_func(x[k]) / nonlinear_func_diff(x[k]);

            if (!(fabs(nonlinear_func_diff(x[k])) > EPSIRON1))
            {
                //接戦がx軸と交わらないとし、初期値の再設定
                flag_step1 = 0;
            }

            /* ステップ3 */
            if (fabs(nonlinear_func(x[k + 1])) <= EPSIRON2)
            { //収束判定を見たいているので、終了
                break;
            }
            if (fabs(x[k + 1] - x[k]) > fabs(x[k] - x[k - 1]) && k >= 1)
            {
                //発散しているとして、初期値の再設定
                flag_step1 = 0;
            }
            /* ステップ4*/
            if (k > K_MAX)
            {
                //適切な反復回数で収束しなかったとして、初期値の再設定
                flag_step1 = 0;
            }
            /* 収束までの過程を表示 */
            printf("Iteration 1: x_%d = %lf\n", k + 1, x[k + 1]);
            k++;
        }
    }

    /* 解の出力部分を書いてください */
    printf("Result: x = %lf, Iteration number = %d\n", x[k + 1], k + 1);

    return 0;
}