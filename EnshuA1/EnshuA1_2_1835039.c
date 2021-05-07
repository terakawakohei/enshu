#include <stdio.h>
#include <stdlib.h> // atoi関数，atof関数を使用するのに必要
#include <string.h>
#include <math.h>
#define EPSIRON 0.0005 // 丸め誤差対策

#define BUF_SIZE 1024 //一つの方程式の係数を入れるのに十分な長さ

int g_ParamNum; //関数の引数に変数の数を渡すためグローバルに用意

void pivot(double a[][g_ParamNum], double c[g_ParamNum][g_ParamNum], int p);
double atof_extension(char *txtdata, int input_num); //係数にKが含まれている場合の対応
double checkInverseMatrix(double A[][g_ParamNum]);   //逆行列が存在するなら1を返す
double calcDet(double A[][g_ParamNum]);              //行列式を計算
int main(void)
{
    int i, j, k;
    int count;

    //学番下一桁を入力

    double inputK;
    printf("学番の下一桁を入力してください:");
    scanf("%lf", &inputK);
    printf("K=%lf\n", inputK);

    FILE *fpA; // FILE型構造体、Aの係数を読み込む
    char fnameA[20];
    printf("Ax=bのAにあたるファイル名を入力してください:");
    scanf("%s", fnameA);

    fpA = fopen(fnameA, "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fpA == NULL)
    {
        printf("%s file not open!\n", fnameA);
        return -1;
    }
    else
    {
        printf("%s file opened!\n", fnameA);
    }

    //パラメータの数を計算
    char bufA[BUF_SIZE];
    int param_numA = 0;

    while (fgets(bufA, BUF_SIZE, fpA) != NULL)
    {
        param_numA++;
    }

    printf("%d元連立方程式を読み込みました\n", param_numA);

    g_ParamNum = param_numA;

    rewind(fpA);

    double A[param_numA][param_numA];
    double calcDetA[param_numA][param_numA]; //行列式計算用に別に確保しておく

    //係数を格納する配列の添字に使うため、下のwhile文でカウントを行う

    int count_col = 0;

    //一つの式の係数部分の文字列の長さを十分にとる
    char strA[BUF_SIZE];
    char *tpA;

    while (fgets(strA, BUF_SIZE, fpA) != NULL)
    {

        tpA = strtok(strA, " ");
        //buf_numAに分割したトークンを代入
        A[count_col][0] = atof_extension(tpA, inputK); //count_col行目、一列目の要素を取得
        calcDetA[count_col][0] = atof_extension(tpA, inputK);

        //添字に使うため、下のwhile文をカウント

        int count_row = 1;
        while (tpA != NULL)
        {
            tpA = strtok(NULL, " ");
            if (tpA != NULL)
            {
                //buf_numAに分割したトークンを代入
                // printf("tpA=%s", tpA);

                A[count_col][count_row] = atof_extension(tpA, inputK);
                calcDetA[count_col][count_row] = atof_extension(tpA, inputK);

                count_row++;
            };
        }

        count_col++;
    }

    fclose(fpA); // ファイルを閉じる

    FILE *fpb; // FILE型構造体、bの数を読み込む
    char fnameb[20];
    printf("Ax=bのbにあたるファイル名を入力してください:");
    scanf("%s", fnameb);

    //学番下一桁を入力

    fpb = fopen(fnameb, "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fpA == NULL)
    {
        printf("%s file not open!\n", fnameb);
        return -1;
    }
    else
    {
        printf("%s file opened!\n", fnameb);
    }

    //パラメータの数を計算
    char buf_b[BUF_SIZE];
    int param_num_b = 0;

    while (fgets(buf_b, BUF_SIZE, fpb) != NULL)
    {
        param_num_b++;
    }

    rewind(fpb);

    double b[param_num_b];

    //係数を格納する配列の添字に使うため、下のwhile文でカウントを行う

    count_col = 0;

    //一つの式の係数部分の文字列の長さを十分にとる
    char str_b[BUF_SIZE];
    char *tpb;

    while (fgets(str_b, BUF_SIZE, fpb) != NULL)
    {

        tpb = strtok(str_b, " ");

        b[count_col] = atof_extension(tpb, inputK);

        count_col++;
    }

    fclose(fpb); // ファイルを閉じる

    //読み込んだ係数の確認

    // printf("読み込んだ係数を確認します\n");

    // printf("A=\n");

    // for (i = 0; i < param_numA; i++)
    // {
    //     for (j = 0; j < param_numA; j++)
    //     {
    //         printf("%lf", A[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("b=\n");
    // for (i = 0; i < param_num_b; i++)
    // {
    //     printf("%lf", b[i]);

    //     printf("\n");
    // }

    double c[param_numA][param_numA]; //単位行列を用意

    for (i = 0; i < param_numA; i++)
    {
        for (j = 0; j < param_numA; j++)
        {
            if (i == j)
            {
                c[i][j] = (double)1;
            }
            else
            {
                c[i][j] = (double)0;
            }
        }
    }

    for (k = 0; k < param_numA; k++)
    {
        for (i = 0; i < param_numA; i++)
        {
            //まずピボット操作が必要かどうかを確認する
            if (fabs(A[i][i]) < EPSIRON)
            {
                // pivot操作

                pivot(A, c, i);
            }
        }
        double invAkk = (double)1 / A[k][k];
        for (j = 0; j < param_numA; j++)
        {

            A[k][j] = A[k][j] * invAkk; //注目しているkの行で、行全体を対角要素でわる

            c[k][j] = c[k][j] * invAkk;
        }

        for (i = 0; i < param_numA; i++)
        {
            double tempAik = A[i][k];
            if (i != k)
            {
                for (j = k; j < param_numA; j++)
                {

                    A[i][j] = A[i][j] - A[k][j] * tempAik;
                }

                for (j = 0; j < param_numA; j++)
                {

                    c[i][j] = c[i][j] - c[k][j] * tempAik;
                }
            }
        }
    }

    // 結果の確認
    printf("結果\n");
    if (checkInverseMatrix(A) == 1)
    {

        double x[param_numA]; //答えを入れる

        for (i = 0; i < param_numA; i++)
        {

            x[i] = 0;
        }

        for (i = 0; i < param_numA; i++)
        {
            for (j = 0; j < param_numA; j++)
            {

                x[i] += c[i][j] * b[j];
            }
        }

        for (i = 0; i < param_numA; i++)
        {
            printf("x%d = %lf ,", i + 1, x[i]);
        }
        printf("\n");
        printf("A=\n");
        for (i = 0; i < param_numA; i++)
        {
            for (j = 0; j < param_numA; j++)
            {
                printf("%lf", c[i][j]);
            }
            printf("\n");
        }
        printf("行列式は、det=%lf\n", calcDet(calcDetA));
    }
    else
    {
        printf("No Inverse Matrix\n"); //checkInverseMatrix()が0の時
    }

    return 0;
}

//交換が必要な対角成分の添字をpとして受け取る
void pivot(double a[][g_ParamNum], double c[g_ParamNum][g_ParamNum], int p)
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

            temp[i] = c[p][i];
            c[p][i] = c[pivot][i];
            c[pivot][i] = temp[i];
        }
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

/* 逆行列を持つなら1を返す関数
ピボット操作を行ったのち、階数が変数の数と一致しない（全て要素が0になる行が存在する）場合線型独立でないと判断する */
double checkInverseMatrix(double A[][g_ParamNum])
{

    double checkzero = (double)0;

    for (int i = 0; i < g_ParamNum; i++)
    {
        for (int j = 0; j < g_ParamNum; j++)
        {
            checkzero += A[i][j];
        }
        if (checkzero == 0) //i行目が全て0なら
        {
            return 0;
        }
        checkzero = (double)0;
    }

    return 1;
}
/* 行列式を計算する関数
上三角行列を計算し、対角部分を掛け合わせる */
double calcDet(double A[][g_ParamNum])
{

    double empty[g_ParamNum][g_ParamNum]; //ここではAについてだけピボット操作をしたいので、適当な配列を用意

    for (int i = 0; i < g_ParamNum; i++)
    {
        //ピボット操作が必要かどうかを確認する
        if (fabs(A[i][i]) < EPSIRON)
        {

            pivot(A, empty, i);
        }
    }
    //上三角行列を作る

    for (int i = 0; i < g_ParamNum; i++)
    {
        for (int j = 0; j < g_ParamNum; j++)
        {
            if (i < j)
            {

                double tempA = A[j][i] / A[i][i];

                for (int k = 0; k < g_ParamNum; k++)
                {
                    A[j][k] = A[j][k] - A[i][k] * tempA;
                }
            }
        }
    }
    //対角要素を計算

    double det = (double)1;
    for (int d = 0; d < g_ParamNum; d++)
    {

        det = det * A[d][d];
    }
    return det;
}
