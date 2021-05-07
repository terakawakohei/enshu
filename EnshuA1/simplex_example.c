#include <stdio.h>
#define epsiron 0.00005
#define ROW 2
#define SLACK 2
#define COLUMN 2

int main(void)
{
	int i, j, k, end_flag, pivot_column, pivot_row;
	double temp;
	double A[ROW][COLUMN + SLACK] = {{1, 2, 1, 0}, {1, 1, 0, 1}}; /* 制約式の左辺＋スラック変数の係数を入れた配列 */
	double B[ROW] = {6, 4};										  /* 制約式の右辺の値を入れた配列 */
	double C[COLUMN + SLACK] = {-3, -4, 0, 0};					  /* 目的関数の係数を入れた配列 */
	double d[COLUMN + SLACK] = {-3, -4, 0, 0};					  /* 残差を入れた配列 */
	int Cbx[ROW] = {2, 3};										  /* 基底変数となる配列番号を入れた配列 */
	double Cb[ROW] = {0, 0};									  /* 基底変数となる目的関数の係数を入れた配列 */
	double min_val;
	int min_num;

	int c = 0;

	end_flag = 0; /* 全てのdが0以上になったかを判断するためのフラグ */
	while (1)
	{
		c++;
		i = 0;
		while (d[i] > -epsiron)
		{ /* 全てのdが0以上になったかどうか */
			i++;
			if (i == SLACK + COLUMN)
			{ /* 全てのdが0以上であれば */
				end_flag = 1;
				break;
			}
		}

		if (end_flag == 0)
		{ /* シンプレックス法を解く */
			min_num = 0;
			min_val = -1;

			temp = d[0];
			for (j = 0; j < SLACK + COLUMN; j++)
			{ /* ピボットする列の決定するため，最も小さいdの値を探索 */
				if (temp >= d[j])
				{
					min_num = j;
					min_val = d[j];
				}
			}

			pivot_column = min_num; /* ピボットする列の決定 min_numに最も小さいdの値となった配列番号を入れている */

			printf("Pivot Column = %d, value = %lf\n", pivot_column, min_val);

			min_val = 10000;
			min_num = -1;

			temp = B[0] / A[0][pivot_column];
			/* pivotする行の決定 */
			for (j = 0; j < ROW; j++)
			{
				if ((A[j][pivot_column] != 0) && (B[j] / A[j][pivot_column] > epsiron))
				{
					/* ピボットする行の変換は，Aの値が0でなく，B[j]/A[j][pivot_column]が正の値のうち，最も小さい値 */

					if (temp >= B[j] / A[j][pivot_column])
					{
						min_num = j;
						min_val = B[j] / A[j][pivot_column];
					}

					/* ピボット操作を行う行を調べるプロぐむラムを書く */
				}
			}
			pivot_row = min_num;
			printf("Pivot Row = %d, value = %lf\n", pivot_row, min_val);

			/* pivot_rowに対する演算 */
			/*  */
			temp = A[pivot_row][pivot_column];
			for (i = 0; i < COLUMN + SLACK; i++)
			{
				A[pivot_row][i] /= temp;
			}
			B[pivot_row] /= temp;

			// printf("基準の行を作ったわよ : %lf-%lf-%lf-%lf-%lf\n", A[0][0], A[0][1], A[0][2], A[0][3], d[0]);
			/* pivot_row以外に対する演算 */
			for (j = 0; j < ROW; j++)
			{
				if (j != pivot_row)
				{ //ピボットの列でないなら
					temp = A[j][pivot_column];
					for (i = 0; i < COLUMN + SLACK; i++)
					{

						A[j][i] -= A[pivot_row][i] * temp;
					}
					B[j] -= B[pivot_row] * temp;
				}
			}
			temp = d[pivot_column];
			for (i = 0; i < COLUMN + SLACK; i++)
			{
				d[i] -= A[pivot_row][i] * temp;
			}

			/* 残差の計算プログラムを記載 */

			/* 基底変数の入れ替え */
			Cb[pivot_column] = C[pivot_row];
			Cbx[pivot_column] = pivot_row;

			for (k = 0; k < ROW; k++)
			{ /* 途中の変換の様子を出力 */
				for (j = 0; j < COLUMN + SLACK; j++)
				{
					printf("%lf ", A[k][j]);
				}
				printf("%lf\n", B[k]);
			}
		}
		else
		{ /* 全てのdが0以上になったら */
			double ob;
			ob = 0.000;

			for (k = 0; k < ROW; k++)
			{ /* 目的関数値の計算 */
				ob += Cb[k] * B[k];
			}
			printf("Objective Function = %lf\n", ob);
			for (k = 0; k < ROW; k++)
			{ /* 基底変数の番号とその値の出力 */
				if (Cbx[k] < ROW)
				{
					printf("Basic variable: x%d = %lf\n", Cbx[k], B[k]);
				}
				else
				{
					printf("Basic variable: Lambda%d = %lf\n", Cbx[k], B[k]);
				}
			}

			break;
		}

		if (c == 5)
		{
			// break;
		}
	}

	return 0;
}
