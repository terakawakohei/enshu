#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n  8
#define LOOP 1000000


int main(int argc, char *argv[]){

  int seed = 0;

  // rw3.cに相互リンクへの簡易対策を追加したもの
  double A[n][n]={
    {    0,     0,     0, 0,  1.0/2,     0,     0,      0},
    {1.0/4,     0,     0, 0,      0,     0,     0,      0},
    {1.0/4, 1.0/3,     0, 0,      0,     0,     0,      0},
    {1.0/4, 1.0/3, 1.0/2, 0,      0,     0,     0,      0},
    {1.0/4, 1.0/3, 1.0/2, 1,      0,     0,     0,      0},
    {    0,     0,     0, 0,  1.0/2,     0, 1.0/2,  1.0/2},
    {    0,     0,     0, 0,      0, 1.0/2,     0,  1.0/2},
    {    0,     0,     0, 0,      0, 1.0/2, 1.0/2,      0},
  };

  // 相互リンクを無いものとして扱う
  for(int i=0;i<n;i++)
    for(int j=0;j<i;j++)
      if ( A[i][j] && A[j][i] )
	A[i][j] = A[j][i] = 0;

  // グラフの連結性の確保
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      A[i][j] = A[i][j] + 0.01;

  // 各列の和が1になるように規格化
  for(int j=0;j<n;j++){
    double dtmp =0;
    for(int i=0;i<n;i++)
      dtmp = dtmp + A[i][j];
    for(int i=0;i<n;i++)
      A[i][j] = A[i][j]/dtmp;
  }

  // これ以降はrw3.cとほぼ同じ

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%.4f ",A[i][j]);
    printf("\n");
  }
  printf("\n");

  srand(seed);

  int index = rand()%n;

  double x[n];
  double xnew[n];

  for(int i=0;i<n;i++){
    if( index == i )
      x[i]=1;
    else
      x[i]=0;
  }

  int loop=0;
  double norm;

  while( loop < LOOP ){
    for(int i=0;i<n;i++){
      xnew[i]=0;
      for(int j=0;j<n;j++)
	xnew[i] = xnew[i] + A[i][j]*x[j];
    }
    norm = 0;
    for(int i=0;i<n;i++)
      norm = norm + xnew[i];
    norm = sqrt(norm);

    for(int i=0;i<n;i++)
      x[i]=xnew[i]/norm;

    loop = loop + 1;
  }


  printf("resulting x = \n");
  for(int i=0;i<n;i++)
    printf("%.3f  ",x[i]);
  printf("\n");


  // おまけ
  printf("A*x = \n");
  for(int i=0;i<n;i++){
    double dtmp =0;
    for(int j=0;j<n;j++)
      dtmp = dtmp + A[i][j]*x[j];
    printf("%.3f  ",dtmp);
  }
  printf("\n");  

  return 0;
}