#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

void print_matrix(double **matrix, int row, int col) {
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      printf("%.4lf ", matrix[i][j]);
    }
    printf("\n");
  }
}
void exchange_row(double **matrix, int a, int b, int col) {
  for(int i = 0; i < col; i++) {
    double temp = matrix[b][i];
    matrix[b][i] = matrix[a][i];
    matrix[a][i] = temp;
  }
}
void gaussian_eliminate(double **matrix, int row, int col, double **lower, double **upper, double **P) {
  for(int i = 0; i < row - 1; i++) {
    double leading_entry = matrix[i][i];
    int index = i;
    for(int k = i; k < row; k++) {
      if(fabs(matrix[k][i]) < leading_entry) { // found smaller leading entry
        leading_entry = matrix[k][i];
        index = k;
      }
    }
    if(i != index) { // swap roll
      exchange_row(matrix, i, index, col);
      exchange_row(P, i, index, col);
      leading_entry = matrix[i][i];
    }

    for(int j = i + 1; j < row; j++) {
      double leading = matrix[j][i]; // leading entry of respective row
      double multiple = leading / leading_entry;
      lower[j][i] = multiple; // fill in the lower matrix
      for(int k = 0; k < col; k++) {
        matrix[j][k] = matrix[j][k] - multiple * matrix[i][k];
      }
    }
  }

  // fill the upper right triangle
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      upper[i][j] = (j < i) ? 0 : matrix[i][j];
    }
  }
}
void create_identity_matrix(double **matrix, int row, int col) {
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      matrix[i][j] = (i == j) ? 1 : 0;
    }
  }
}
double *gaussian_solve(double **matrix, double *oldb, int row, int col) {
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

  double *b = calloc(row, sizeof(double));
  double *c = calloc(row, sizeof(double));
  double *x = calloc(row, sizeof(double));

  // matrix P times matrix b
  // initialize c and x to be 1
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < row; j++) {
      if(P[i][j] == 1) {
        b[i] = oldb[j];
      }
    }
    c[i] = 1;
    x[i] = 1;
  }

  // Solve Lc = Pb for c(forward substitution)
  for(int i = 0; i < row; i++) {
    double tmp = 0;
    for(int j = 0; j < i; j++) {
      tmp += lower[i][j] * c[j];
    }
    c[i] = (b[i] - tmp) / lower[i][i];
  }

  // Solve Ux = c for x(backward substitution)
  for(int i = row; i > 0; i--) {
    double tmp = 0;
    for(int j = row; j > i; j--) {
      tmp += upper[i - 1][j - 1] * x[j - 1];
    }
    x[i - 1] = (c[i - 1] - tmp) / upper[i - 1][i - 1];
  }
  return x;
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
double **get_transposed(double **x, int n, int m) {
    double **new = calloc(m, sizeof(double));
    for(int i = 0; i < m; i++)
      new[i] = calloc(n, sizeof(double));
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        new[j][i] = x[i][j];
      }
    }
    return new;
}
double **at_times_a(double **at, double **a, int n, int m) {
    double **new = calloc(m, sizeof(double));
    for(int i = 0; i < m; i++)
      new[i] = calloc(m, sizeof(double));
    for(int i = 0; i < m; i++) {
      for(int j = 0; j < m; j++) {
        new[i][j] = 0;
        for(int k = 0; k < n; k++)
          new[i][j] += at[i][k] * a[k][j];
      }
    }
    return new;
}
double *at_times_b(double **at, double *b, int row, int col) {
    double *new = calloc(row, sizeof(double));
    for(int i = 0; i < row; i++) {
      new[i] = 0;
      for(int j = 0; j < col; j++)
        new[i] += at[i][j] * b[j];
    }
    return new;
}
