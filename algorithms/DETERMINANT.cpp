//Argumentos: 1) N - Dimension de la matriz cuadrada
//            2) A[i][j] para 0 <= i,j <= N 

#include<stdio.h>
double matrix[10][10];
int determinant(int n){
  double ratio, det;
  int i, j, k;
  /* Conversion of matrix to upper triangular */
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      if(j>i){
        ratio = matrix[j][i]/matrix[i][i];
        for(k = 0; k < n; k++){
          matrix[j][k] -= ratio * matrix[i][k];
        }
      }
    }
  }
  det = 1; //storage for determinant
  for(i = 0; i < n; i++)
    det *= matrix[i][i];
  
  return det;
}
