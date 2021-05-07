#include<stdio.h>
#include<stdlib.h>

#define n 300
#define seed 0
#define LOOP 1234

// E = 0.5*x*W*x
// この値を小さくする {-1,+1}^n の要素を見つけたい
int E(int **W,int *x){
  double e=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++)
      e += W[i][j]*x[i]*x[j];
  }
  return e;
}

int main(int argc,char *argv[]){

  srand(seed);

  int **W;
  W = malloc(n*sizeof(int*));
  for(int i=0;i<n;i++)
    W[i] = malloc(n*sizeof(int));

  for(int i=0;i<n;i++){
    W[i][i]=0;
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

  int x[n];

  int loop=0;
  int opt = 1, e;

  printf("random search(%d)\n",LOOP);

  while( loop <= LOOP ){
    // {-1,+1}^n の要素を一様に生成(どれも等確率で生成)
    for(int i=0;i<n;i++)
      if( rand()%2 )
	x[i] =  1;
      else
	x[i] = -1; 

    e = E(W,x);
    // より良いものが見つかれば更新
    if( e < opt ){
      opt = e;
      printf("E = 0.5*x*W*x = %d found\n",opt);
    }
    loop++;
  }


  return 0;
  
}
