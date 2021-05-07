#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define ITERATION 2000   // Number of Iteration
#define ETA 0.05         // learning coeffcient
#define MAX_N_DATA 10000 // number of maximum input data size

float calc_y(float a, float b, float c, float d, float x)
{
    // calculate the result y of input x using parameters a, b, c and d
    float y_calc;

    // Need to change the formulation
    y_calc = a * pow(x, 3) + b * pow(x, 2) + c * x + d;

    return y_calc;
}

float get_loss(int n_data, float *x, float *y, float a, float b, float c, float d)
{
    float loss_total = 0;
    float y_calc, y_diff, loss;

    for (int i = 0; i < n_data; i++)
    {
        // Need to implementation

        // Calculation of y of input x using parameters
        y_calc = calc_y(a, b, c, d, x[i]);

        y_diff = (y_calc - y[i]);

        loss = pow(y_diff, 2);

        loss_total += loss;

        // the error is diference between the prediction and the real result y.

        // the loss is defined as the squared error.

        // sum up the loss
    }
    return loss_total / n_data; // return to mean square errors
}

float get_grad_a(int n_data, float *x, float *y, float a, float b, float c, float d)
{
    float grad_total = 0;
    float y_calc, grad;

    for (int i = 0; i < n_data; i++)
    {
        y_calc = calc_y(a, b, c, d, x[i]);

        grad = 2 * pow(x[i], 3) * (y_calc - y[i]);

        grad_total += grad;
        // Need to implementation
    }
    return grad_total / n_data; // return to gradient
}

float get_grad_b(int n_data, float *x, float *y, float a, float b, float c, float d)
{
    float grad_total = 0;
    float y_calc, grad;

    for (int i = 0; i < n_data; i++)
    {
        y_calc = calc_y(a, b, c, d, x[i]);

        grad = 2 * pow(x[i], 2) * (y_calc - y[i]);

        grad_total += grad;
        // Need to implementation
    }
    return grad_total / n_data; // return to gradient
}

float get_grad_c(int n_data, float *x, float *y, float a, float b, float c, float d)
{
    float grad_total = 0;
    float y_calc, grad;

    for (int i = 0; i < n_data; i++)
    {
        y_calc = calc_y(a, b, c, d, x[i]);

        grad = 2 * x[i] * (y_calc - y[i]);

        grad_total += grad;
        // Need to implementation
    }
    return grad_total / n_data; // return to gradient
}

float get_grad_d(int n_data, float *x, float *y, float a, float b, float c, float d)
{
    float grad_total = 0;
    float y_calc, grad;

    for (int i = 0; i < n_data; i++)
    {
        y_calc = calc_y(a, b, c, d, x[i]);

        grad = 2 * (y_calc - y[i]);

        grad_total += grad;
        // Need to implementation
    }
    return grad_total / n_data; // return to gradient
}

int load_data(float *x, float *y, char *filename)
{
    // Data is loaded from "data_kadai.dat".
    FILE *fp;
    int n_data = 0;
    int n_data_loaded;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("File data_kadai cannot be opened.\n");
    }
    // How many data is loaded
    while (1)
    {
        // A pair of measures is loaded.
        n_data_loaded = fscanf(fp, "%f %f\n", &x[n_data], &y[n_data]);
        // When no pair is loaded, break.
        if (n_data_loaded < 2)
        {
            break;
        }
        // The number of loaded pairs is incremented.
        // printf("%d: %lf %lf\n", n_data, x[n_data], y[n_data]);
        n_data++;
    }
    fclose(fp);

    // Return the number of data
    return n_data;
}
int main(void)
{
    int flag = 0;
    while (1)
    {
        if (flag == 1)
        { //反復回数の上限まで無事に達したら
            printf("別ファイルを読み込みますか？\n");
            printf("はい( 1 )/いいえ( 0 ) :");
            int select;
            scanf("%d", &select);

            if (select == 0)
            {
                break; //プログラム終了
            }

            flag = 0; //別ファイルを読み込む場合、もとに戻す
        }
        // initialization
        //    float *x,*y;
        float x[MAX_N_DATA], y[MAX_N_DATA];
        float a, b, c, d; // coefficient
        float loss, grad_a, grad_b, grad_c, grad_d;
        int n_data;

        //    x = (float *)malloc(sizeof(float)*MAX_N_DATA);
        //    y = (float *)malloc(sizeof(float)*MAX_N_DATA);

        char filename[20];
        printf("データを読み込むファイル名を入力してください\n");
        scanf("%s", filename);

        n_data = load_data(x, y, filename);
        //    x = (float *)realloc(x, sizeof(float)*n_data);
        //   y = (float *)realloc(y, sizeof(float)*n_data);
        printf("%d pairs are loaded.\n", n_data);

        float eta = ETA;

        // initial parameter
        // a = 1.0;
        // b = 1.0;
        // c = 1.0;
        // d = 1.0;

        // main loop

        printf("初期値を設定してください\n");

        printf("a=");
        scanf("%f", &a);

        printf("b=");
        scanf("%f", &b);

        printf("c=");
        scanf("%f", &c);

        printf("d=");
        scanf("%f", &d);

        printf("学習係数を設定してください\n");

        printf("ETA=");
        scanf("%f", &eta);

        for (int t = 0; t < ITERATION; t++)
        {

            //誤差の変化が大きい時は、再設定
            if (t != 0 && loss * 1000 < get_loss(n_data, x, y, a, b, c, d))
            {

                printf("誤差関数が発散したため、条件を再設定します\n");

                break;
            }
            loss = get_loss(n_data, x, y, a, b, c, d);

            grad_a = get_grad_a(n_data, x, y, a, b, c, d);
            grad_b = get_grad_b(n_data, x, y, a, b, c, d);
            grad_c = get_grad_c(n_data, x, y, a, b, c, d);
            grad_d = get_grad_d(n_data, x, y, a, b, c, d);

            a = a - eta * grad_a;
            b = b - eta * grad_b;
            c = c - eta * grad_c;
            d = d - eta * grad_d;
            // printf("%d a=%1.5f, b=%1.5f, c=%1.5f, d=%1.5f, L=%1.5f\n", t, a, b, c, d, loss);

            if (t == ITERATION - 1) //反復回数の上限まで達したら
            {
                printf("y=(%f)x^3+(%f)x^2+(%f)x+%f\n", a, b, c, d);

                flag = 1;
            }
        }
    }

    return 0;
}