#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct {
  double h;
  double k;
  double r;
}jacobian_matrix;

double **getdmatrix1(jacobian_matrix x) {
  double **result = malloc(3 * sizeof(double));
  for(int i = 0; i < 3; i++)
    result[i] = malloc(3 * sizeof(double));
  result[0][0] = 16 + 2 * x.h; 
  result[0][1] = 8 + 2 * x.k;
  result[0][2] = -2 * x.r; 

  result[1][0] = -12 + 2 * x.h; 
  result[1][1] = -18 + 2 * x.k;
  result[1][2] = -2 * x.r;

  result[2][0] = -8 + 2 * x.h;
  result[2][1] = 18 + 2 * x.k;
  result[2][2] = -2 * x.r;

  return result;
}

double **getdmatrix2(jacobian_matrix x) {
  double **result = malloc(3 * sizeof(double));
  for(int i = 0; i < 3; i++)
    result[i] = malloc(3 * sizeof(double));
  result[0][0] = 2 + 2 * x.h; 
  result[0][1] = -12 + 2 * x.k;
  result[0][2] = -2 * x.r; 

  result[1][0] = 4 + 2 * x.h; 
  result[1][1] = 12 + 2 * x.k;
  result[1][2] = -2 * x.r;

  result[2][0] = -10 + 2 * x.h;
  result[2][1] = 2 * x.k;
  result[2][2] = -2 * x.r;

  return result;
}

double *getfmatrix1(jacobian_matrix x) {
  double *result = malloc(3 * sizeof(double));

  result[0] = -1 * (pow((-8 - x.h), 2) + pow((-4 - x.k), 2) - pow(x.r, 2)); 
  result[1] = -1 * (pow((6 - x.h), 2) + pow((9 - x.k), 2) - pow(x.r, 2)); 
  result[2] = -1 * (pow((4 - x.h), 2) + pow((-9 - x.k), 2) - pow(x.r, 2)); 

  return result;
}

double *getfmatrix2(jacobian_matrix x) {
  double *result = malloc(3 * sizeof(double));

  result[0] = -1 * (pow((-1 - x.h), 2) + pow((6 - x.k), 2) - pow(x.r, 2)); 
  result[1] = -1 * (pow((-2 - x.h), 2) + pow((-6 - x.k), 2) - pow(x.r, 2)); 
  result[2] = -1 * (pow((5 - x.h), 2) + pow((0 - x.k), 2) - pow(x.r, 2)); 

  return result;
}

double mdiff(jacobian_matrix initial, jacobian_matrix new) {
  double total = 0;
  total += fabs(initial.h - new.h);
  total += fabs(initial.k - new.k);
  total += fabs(initial.r - new.r);
  return total;
}

int main() {
  int row = 3; int col = 3;

  for(int k = 0; k < 2; k++) {
    jacobian_matrix initial_vector = {2, 2, 2};
    jacobian_matrix new_vector = {1, 1, 1};

    printf("Test %d\n", k + 1);

    while(mdiff(initial_vector, new_vector) >= 10e-6) {
      initial_vector.h = new_vector.h;
      initial_vector.k = new_vector.k;
      initial_vector.r = new_vector.r;

      double **matrix;
      double *oldb;
      if(k == 0) {
        matrix = getdmatrix1(initial_vector);
        oldb   = getfmatrix1(initial_vector);
      }else {
        matrix = getdmatrix2(initial_vector);
        oldb   = getfmatrix2(initial_vector);
      }
      
      double *x = gaussian_solve(matrix, oldb, row, col);

      new_vector.h = initial_vector.h + x[0];
      new_vector.k = initial_vector.k + x[1];
      new_vector.r = initial_vector.r + x[2];
    }

    printf("h = %.4lf\n", initial_vector.h);
    printf("k = %.4lf\n", initial_vector.k);
    printf("r = %.4lf\n", initial_vector.r);
  }
  return 0;
}
