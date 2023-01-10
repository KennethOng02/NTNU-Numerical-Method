#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

double **get_a(double *x, int n, int m) {
  double **A = calloc(n, sizeof(double));
  for(int i = 0; i < n; i++)
    A[i] = calloc(m, sizeof(double));
  for(int i = 0; i < n; i++) {
    A[i][0] = 1;
    A[i][1] = x[i];
    A[i][2] = pow(x[i], 2);
    A[i][3] = pow(x[i], 3);
  }
  return A;
}
int main() {
  int row, col;
  row = 13; col = 4;
  double *x = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++)
    x[i] = i * 0.25;
  double *y = calloc(row, sizeof(double));
  y[0] = 6.3806;    y[1] = 7.1338;    y[2] = 9.1662;    y[3] = 11.5545; y[4] = 15.6414;
  y[5] = 22.7371;   y[6] = 32.0696;   y[7] = 47.0756;   y[8] = 73.1596; y[9] = 111.4684;
  y[10] = 175.9895; y[11] = 278.5550; y[12] = 446.4441;

  double **A = get_a(x, row, col);
  double **A_t = get_transposed(A, row, col);
  double **matrix = at_times_a(A_t, A, row, col);
  double *b = at_times_b(A_t, y, col, row);

  double *ans = gaussian_solve(matrix, b, col, col);

  char num = 'a';
  for(int i = 0; i < col; i++)
    printf("%c = %.4lf\n", num++, ans[i]);
  return 0;
}
