#include <stdio.h>
#include <stdlib.h> // atoi関数，atof関数を使用するのに必要
#include <string.h>
#include <math.h>
#define N 3            // 変数の数
#define EPSIRON 0.0005 // 丸め誤差対策

#define BUF_SIZE 1024

double atof_extension(char *txtdata, int K);

int main(void)
{

    int i, j, k;
    int count;

    FILE *fp; // FILE型構造体
    char fname[20];
    printf("ファイル名を入力してください:");
    scanf("%s", fname);

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

    char buf[BUF_SIZE];
    int param_num = 0;

    while (fgets(buf, BUF_SIZE, fp) != NULL)
    {
        param_num++;
    }

    printf("%d\n", param_num);

    rewind(fp);

    double buf_num[param_num][param_num + 1];

    //添字に使うため、下のwhile文をカウント

    int count_col = 0;

    //一つの式の係数部分の文字列の長さを十分にとる
    char str[BUF_SIZE];
    char *tp;

    while (fgets(str, BUF_SIZE, fp) != NULL)
    {

        tp = strtok(str, " ");
        //a[count_col][0]に分割したトークンを代入
        buf_num[count_col][0] = atof_extension(tp, 9);

        // strcpy(buf_num[count_col][0], tp);

        //添字に使うため、下のwhile文をカウント

        int count_row = 1;
        while (tp != NULL)
        {
            tp = strtok(NULL, " ");
            if (tp != NULL)
            {
                //a[i][count]に分割したトークンを代入

                buf_num[count_col][count_row] = atof_extension(tp, 9);

                // strcpy(buf_num[count_col][count_row], tp);

                count_row++;
            };
        }

        count_col++;
    }

    fclose(fp); // ファイルを閉じる

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            if (j == 3)
            {
                printf("b[%d] = %lf\n", i, buf_num[i][j]);
            }
            else
            {
                printf("a[%d][%d] = %lf, ", i, j, buf_num[i][j]);
            }
        }
    }

    //文字→数字の変換、Kの検出、代入
}

double atof_extension(char *txtdata, int input_num)
{
    char *k = "K";

    if (strcmp(txtdata, k) == 0)
    {
        return input_num;
    }
    else
    {
        return atof(txtdata);
    }
}
