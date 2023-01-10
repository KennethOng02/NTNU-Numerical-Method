#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct {
  double x;
  double y;
  double k;
}jacobian_matrix;
double **getdrmatrix(jacobian_matrix p, int row, int col) {
  double **result = calloc(row, sizeof(double));
  for(int i = 0; i < row; i++)
    result[i] = calloc(col, sizeof(double));
  double S1 = sqrt(pow(p.x + 1, 2) + pow(p.y - 0, 2));
  result[0][0] = (p.x + 1) / S1;
  result[0][1] = (p.y - 0) / S1;
  result[0][2] = -1;

  double S2 = sqrt(pow(p.x - 1, 2) + pow(p.y - 0.5, 2));
  result[1][0] = (p.x - 1) / S2;
  result[1][1] = (p.y - 0.5) / S2;
  result[1][2] = -1;

  double S3 = sqrt(pow(p.x - 1, 2) + pow(p.y + 0.5, 2));
  result[2][0] = (p.x - 1) / S3;
  result[2][1] = (p.y + 0.5) / S3;
  result[2][2] = -1;

  double S4 = sqrt(pow(p.x - 0, 2) + pow(p.y - 1, 2));
  result[3][0] = (p.x - 0) / S4;
  result[3][1] = (p.y - 1) / S4;
  result[3][2] = -1;

  return result;
}
double *getrmatrix(jacobian_matrix p, int row) {
  double *result = malloc(row * sizeof(double));

  result[0] = sqrt(pow(p.x + 1, 2) + pow(p.y - 0, 2))   - (1 + p.k);
  result[1] = sqrt(pow(p.x - 1, 2) + pow(p.y - 0.5, 2)) - (0.5 + p.k);
  result[2] = sqrt(pow(p.x - 1, 2) + pow(p.y + 0.5, 2)) - (0.5 + p.k);
  result[3] = sqrt(pow(p.x - 0, 2) + pow(p.y - 1, 2))   - (0.5 + p.k);

  return result;
}

double mdiff(jacobian_matrix initial, jacobian_matrix new) {
  double total = 0;
  total += pow(initial.x - new.x, 2);
  total += pow(initial.y - new.y, 2);
  total += pow(initial.k - new.k, 2);
  return sqrt(total);
}

int main() {
    int row = 4; int col = 3;

    jacobian_matrix initial_vector = {2.0, 2.0, 2.0};
    jacobian_matrix new_vector     = {0.5, 0.5, 0.5};

    while(mdiff(initial_vector, new_vector) >= 10e-6) {
      initial_vector.x = new_vector.x;
      initial_vector.y = new_vector.y;
      initial_vector.k = new_vector.k;

      double **D_r   = getdrmatrix(initial_vector, row, col);
      double *r      = getrmatrix(initial_vector, row);
      double **D_r_t = get_transposed(D_r, row, col);

      double *b      = at_times_b(D_r_t, r, col, row);
      for(int i = 0; i < col; i++) {
        b[i] *= -1;
      }

      double **matrix = at_times_a(D_r_t, D_r, row, col);
      double *x       = gaussian_solve(matrix, b, col, col);

      new_vector.x = initial_vector.x + x[0];
      new_vector.y = initial_vector.y + x[1];
      new_vector.k = initial_vector.k + x[2];
    }

    printf("x = %.4lf\n", initial_vector.x);
    printf("y = %.4lf\n", initial_vector.y);
    printf("k = %.4lf\n", initial_vector.k);

    return 0;
}
