#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n 300
#define seed 0
#define epsilon 0.000001

// このプログラムよりも単純なプログラムにより短時間で良い許容解を
// 見つけることが可能でが，この授業の本題ではないので詳細は割愛．
//                     ( while( 1 ) の部分だけを繰り返し行えばよい ) 


double E(int **W,double *x){
  double e=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++)
      e += W[i][j]*x[i]*x[j];
  }
  return e;
}

// true if  x == xold
int identical(double *x, double *xold){
  for(int i=0;i<n;i++){
    if( x[i] != xold[i] )
      return 0;
  }
  return 1;
}

int main(int argc,char *argv[]){

  srand(seed);

  int **W;
  W = malloc(n*sizeof(int*));
  for(int i=0;i<n;i++)
    W[i] = malloc(n*sizeof(int));


  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++)
    W[i][j]=W[j][i] = rand()%(2*n) - n ;
  }

/*
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%3d ",W[i][j]);
    printf("\n");
  }
*/


  int bias = 10*n;
  for(int i=0;i<n;i++)
    W[i][i] =  -bias;

  double x[n],xold[n];
  double err,norm;

  for(int i=0;i<n;i++){
    x[i]    =  2*(rand()%2) -1;
    xold[i] =  2*(rand()%2) -1;
  }

  printf("power iteration based rounding(1)\n");
  while( 1 ){
    err=0;
    for(int i=0;i<n;i++){
      err += (xold[i]-x[i])*(xold[i]-x[i]);
      xold[i]=x[i];
    }

    // 変化が一定未満になるまで繰り返す
    if( sqrt(err) < epsilon*n ){
      for(int i=0;i<n;i++){
	if( x[i] >= 0 )
	  x[i] = 1;
	else
	  x[i] = -1;
	W[i][i] = 0;
	
      }
      
      printf("E = 0.5*x*W*x = %d found\n",(int)E(W,x));

      double u;

      // 仕上げ(線形代数と微分積分の応用,詳細は省略)．
      printf("multi-start local search mode\n");
      while( 1 ){
	for(int i=0;i<n;i++){
	  u=0;
	  xold[i]=x[i];
	  for(int j=0;j<n;j++)
	    u += W[i][j]*x[j];
	  if(u  >= 0 )
	    x[i] = -1;
	  else
	    x[i] =1 ;
	}
	if( identical(x,xold) ){
	  printf("E = 0.5*x*W*x = %d found\n",(int)E(W,x));
	  break;
	}
      }
      break;
    }

    // rw2.cと同じ計算
    // x := W*x
    norm = 0;
    for(int i=0;i<n;i++){
      x[i] = 0;
      for(int j=0;j<n;j++)
	x[i] -= W[i][j]*xold[j];
      norm += x[i]*x[i];
    }
    // x := x/|x| 
    norm = sqrt(norm);
    for(int i=0;i<n;i++)
      x[i] /= norm;

  }

  return 0;
  
}