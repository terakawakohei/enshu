#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n  8
#define LOOP 1000000


int main(int argc, char *argv[]){

  int seed = 0;

  // rw2.cに相互リンクの中身無しページを三つ(6,7,8)追加した場合を想定
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


  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%.2f ",A[i][j]);
    printf("\n");
  }
  printf("\n");

  srand(seed);

  int index = rand()%n;

  double x[n];
  double xnew[n]; // 計算用バッファ

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

    for(int i=0;i<n;i++)
      x[i]=xnew[i]/norm;

    loop = loop + 1;
  }


  for(int i=0;i<n;i++)
    printf("%.3f  ",x[i]);
  printf("\n");

  return 0;
}