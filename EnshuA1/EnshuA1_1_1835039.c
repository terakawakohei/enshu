#include <stdio.h>
#include <stdlib.h> // atoi関数，atof関数を使用するのに必要
#include <string.h>
#include <math.h>

#define EPSIRON 0.0005 // 丸め誤差対策

#define BUF_SIZE 1024 //一つの方程式の係数を入れるのに十分な長さ

int g_ParamNum; //関数の引数に変数の数を渡すためグローバルに用意

void pivot(double a[][g_ParamNum], double b[g_ParamNum], int p);
double atof_extension(char *txtdata, int input_num); //係数にKが含まれている場合の対応

int main(void)
{
    int i, j, k;
    int count;

    FILE *fp; // FILE型構造体
    char fname[20];
    printf("ファイル名を入力してください:");
    scanf("%s", fname);

    //学番下一桁を入力

    double inputK;
    printf("学番の下一桁を入力してください:");
    scanf("%lf", &inputK);
    printf("K=%lf\n", inputK);

    fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fp == NULL)
    {
        printf("%s file not open!\n", fname);
        return -1;
    }
    else
    {
        printf("%s file opened!\n", fname);
    }

    //パラメータの数を計算
    char buf[BUF_SIZE];
    int param_num = 0;

    while (fgets(buf, BUF_SIZE, fp) != NULL)
    {
        param_num++;
    }

    printf("%d元連立方程式を読み込みました\n", param_num);

    g_ParamNum = param_num;

    rewind(fp);

    double buf_num[param_num][param_num + 1];

    //係数を格納する配列の添字に使うため、下のwhile文をカウント

    int count_col = 0;

    //一つの式の係数部分の文字列の長さを十分にとる
    char str[BUF_SIZE];
    char *tp;

    while (fgets(str, BUF_SIZE, fp) != NULL)
    {

        tp = strtok(str, " ");
        //buf_numに分割したトークンを代入
        buf_num[count_col][0] = atof_extension(tp, inputK);

        //添字に使うため、下のwhile文をカウント

        int count_row = 1;
        while (tp != NULL)
        {
            tp = strtok(NULL, " ");
            if (tp != NULL)
            {
                //buf_numに分割したトークンを代入

                buf_num[count_col][count_row] = atof_extension(tp, inputK);

                count_row++;
            };
        }

        count_col++;
    }

    fclose(fp); // ファイルを閉じる

    //読み込んだ係数の確認

    // printf("読み込んだ係数を確認します\n");
    // for (i = 0; i < param_num; i++)
    // {
    //     for (j = 0; j <= param_num; j++)
    //     {
    //         printf("%lf", buf_num[i][j]);
    //     }
    //     printf("\n");
    // }

    //buf_numからa,bに移し替え

    double a[param_num][param_num];
    double b[param_num];

    //aに代入
    for (i = 0; i < param_num; ++i)
    {
        for (j = 0; j < param_num; ++j)
        {

            a[i][j] = buf_num[i][j];
        }
    }
    //bに代入
    for (i = 0; i < param_num; ++i)
    {

        b[i] = buf_num[i][param_num];
    }

    // 前進消去
    count = param_num;
    for (i = 0; i < count; i++)
    {
        //まずピボット操作が必要かどうかを確認する
        if (fabs(a[i][i]) < EPSIRON)
        {
            // pivot操作

            pivot(a, b, i);
        }
    }

    for (int k = 0; k < count; k++)
    {
        for (i = 0; i < count; i++)
        {
            if (k != i)
            {
                //k+1の更新の際に保持しておく
                double temp = a[i][k];

                for (j = 0; j < count; j++)
                {

                    if (i > k)
                    {
                        a[i][j] = a[i][j] - a[k][j] * (temp / a[k][k]);
                    }
                }
                if (i > k)
                {
                    b[i] = b[i] - b[k] * (temp / a[k][k]);
                }

                // printf("k=%dの、代%d行の計算が終了、b=%f,次は下の行に--iは%d\n", k, i, b[i], i);
            }
        }
    }

    // 後退代入

    // パラメータxを宣言
    double x[param_num];
    // 今度は大きい値から引いていくことに注意

    x[param_num - 1] = b[param_num - 1] / a[param_num - 1][param_num - 1];

    for (i = param_num - 2; i >= 0; i--)
    {
        double calc_sigma = 0;
        for (int p = i + 1; p <= param_num; p++)
        {
            calc_sigma += a[i][p] * x[p];
        }
        x[i] = 1 / a[i][i] * (b[i] - calc_sigma);
    }

    // 結果の確認
    for (i = 0; i < count; i++)
    {
        for (j = 0; j <= count; j++)
        {
            if (j == count)
            {
                printf("b[%d] = %lf\n", i, b[i]);
            }
            else
            {
                printf("a[%d][%d] = %lf, ", i, j, a[i][j]);
            }
        }
    }
    for (i = 0; i < count; i++)
        printf("x_%d = %lf, ", i + 1, x[i]);
    printf("\n");

    return 0;
}

//交換が必要な対角成分の添字をpとして受け取る
void pivot(double a[][g_ParamNum], double b[g_ParamNum], int p)
{
    // pivot変換用関数
    int i, pivot;
    double max_value; // 最大の変数を格納
    double temp_value;
    double temp[g_ParamNum];

    max_value = a[0][p];

    // 同じ列の中で、どの係数が一番大きいかを確認
    //最も大きい行の数字がpivotに入る

    for (i = 1; i < g_ParamNum; i++)
    {

        if (fabs(a[i][p]) >= fabs(max_value))
        {
            max_value = a[i][p];
            pivot = i;
        }
    }

    // 一番大きい係数だった行の全体を入れ替える(pとpivotで行を交換)

    if (p != pivot)
    {

        for (i = 0; i < g_ParamNum; ++i)
        {
            temp[i] = a[p][i];
            a[p][i] = a[pivot][i];
            a[pivot][i] = temp[i];
        }

        temp_value = b[p];
        b[p] = b[pivot];
        b[pivot] = temp_value;
    }
}

//係数にKが含まれている場合の対応
double atof_extension(char *line, int input_num)
{

    if (strchr(line, (int)'K'))
    {
        return input_num;
    }
    else
    {
        return atof(line);
    }
}
