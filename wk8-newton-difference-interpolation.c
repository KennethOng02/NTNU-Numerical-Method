#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void divided_difference_table(double *x, double **y, int n) {
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n - i; j++) {
      y[j][i] = (y[j][i - 1] - y[j + 1][i - 1]) / (x[j] - x[i + j]);
    }
  }
}
void print_diff_table(double **y, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i; j++) {
      printf("%lf ", y[i][j]);
    }
    printf("\n");
  }
}
double calc_interpolation(double p, double *x, double **y, int32_t n) {
  double sum = y[0][n-1];
  for(size_t i = n-1; i > 0; i--) {
    sum *= (p - x[i-1]);
    sum += y[0][i-1];
  }
  return sum;
}

int main() {
  int32_t n = 5;
  double x[] = {0.6, 0.7, 0.8, 0.9, 1.0};
  double **y = calloc(n, sizeof(double));
  for(size_t i = 0; i < n; i++) y[i] = calloc(n, sizeof(double));
  y[0][0] = 1.433329;
  y[1][0] = 1.632316;
  y[2][0] = 1.896481;
  y[3][0] = 2.247908;
  y[4][0] = 2.718282;

  divided_difference_table(x, y, n);

  // print_diff_table(y, n);

  double p1, p2;
  p1 = 0.82; p2 = 0.98;

  printf("%lf\n", calc_interpolation(p1, x, y, n));
  printf("%lf\n", calc_interpolation(p2, x, y, n));

  return 0;
}
