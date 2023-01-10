#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main() {
  int row = 4;
  int col = 4;

  double **matrix = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++) matrix[i] = calloc(col, sizeof(double));
  matrix[0][0] =  0; matrix[0][1] =  0; matrix[0][2] = -1; matrix[0][3] =  1;
  matrix[1][0] =  1; matrix[1][1] =  1; matrix[1][2] = -1; matrix[1][3] =  2;
  matrix[2][0] = -1; matrix[2][1] = -1; matrix[2][2] =  2; matrix[2][3] =  0;
  matrix[3][0] =  1; matrix[3][1] =  2; matrix[3][2] =  0; matrix[3][3] =  2;

  double **upper = calloc(row, sizeof(double));
  double **lower = calloc(row, sizeof(double));
  double **P     = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++) {
    upper[i] = calloc(row, sizeof(double));
    lower[i] = calloc(row, sizeof(double));
    P[i]     = calloc(row, sizeof(double));
  }
  create_identity_matrix(lower, row, col);
  create_identity_matrix(P, row, col);

  gaussian_eliminate(matrix, row, col, lower, upper, P);

  printf("P: \n");
  print_matrix(P, row, col);
  printf("---\n");
  printf("Lower: \n");
  print_matrix(lower, row, col);
  printf("---\n");
  printf("Upper: \n");
  print_matrix(upper, row, col);

  return 0;
}
