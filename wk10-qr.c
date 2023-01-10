#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void print_matrix(double **matrix, int row, int col) {
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      printf("%.4lf ", matrix[i][j]);
    }
    printf("\n");
  }
  return;
}
void qr(double **A, double **Q, double **R, int row, int col) {
  // calc the first unit vector
  double first_len = 0;
  for(int i = 0; i < row; i++) {
    first_len += pow(A[i][0], 2);
  }
  first_len = sqrt(first_len);
  for(int i = 0; i < row; i++) {
    Q[i][0] = A[i][0] / first_len;
  }
  R[0][0] = first_len;

  // Initial y
  double **y = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++) y[i] = calloc(col, sizeof(double));
  for(int i = 0; i < row; i++)
    for(int j = 0; j < col; j++)
      y[i][j] = A[i][j];

  for(int cur_col = 1; cur_col < col; cur_col++) { // iterate each column
    for(int i = 0; i < cur_col; i++) { // iterate each col of Q to multiple the column of A
      double r_ij = 0;
      for(int j = 0; j < row; j++) { // multiple Q^T and A_j
        r_ij += Q[j][i] * A[j][cur_col];
      }
      R[i][cur_col] = r_ij;
      for(int j = 0; j < row; j++) {
        y[j][cur_col] -= Q[j][i] * r_ij;
      }
    }
    double length = 0;
    for(int i = 0; i < row; i++) { // calc ||y_j||_2
      length += pow(y[i][cur_col], 2);
    }
    length = sqrt(length);
    R[cur_col][cur_col] = length;
    for(int i = 0; i < row; i++) {
      Q[i][cur_col] = y[i][cur_col] / length;
    }
  }
}
int main() {
  int row, col;
  row = 5; col = 3;
  double **A = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++) A[i] = calloc(col, sizeof(double));
  A[0][0] = 3;  A[0][1] = -1; A[0][2] = 2;
  A[1][0] = 4;  A[1][1] = 1;  A[1][2] = 0;
  A[2][0] = -3; A[2][1] = 2;  A[2][2] = 1;
  A[3][0] = 1;  A[3][1] = 1;  A[3][2] = 5;
  A[4][0] = -2; A[4][1] = 0;  A[4][2] = 3;

  double **Q = calloc(row, sizeof(double));
  double **R = calloc(col, sizeof(double));
  for(int i = 0; i < row; i++) 
    Q[i] = calloc(col, sizeof(double));
  for(int i = 0; i < col; i++) 
    R[i] = calloc(col, sizeof(double));

  qr(A, Q, R, row, col);

  printf("Q: \n"); print_matrix(Q, row, col);
  printf("R: \n"); print_matrix(R, col, col);
  return 0;
}
