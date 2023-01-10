#include <stdio.h>

void gaussian_eliminate(double matrix[4][4], int row, int col, double lower[4][4], double upper[4][4]) {
  for(size_t i = 0; i < row - 1; i++) {
    double a = matrix[i][i];
    for(size_t j = i + 1; j < row; j++) {
      double leading = matrix[j][i];
      double mul = 1.0 * leading / a;
      lower[j][i] = mul;
      for(size_t k = 0; k < col; k++) {
        matrix[j][k] = matrix[j][k] - mul * matrix[i][k];
      }
    }  
  }

  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      if(j >= i) {
        upper[i][j] = matrix[i][j];
      }else {
        upper[i][j] = 0;
      }
    }
  }

  return;
}

void create_identity_matrix(double matrix[4][4], int row, int col) {
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      if(i == j) {
        matrix[i][j] = 1;
      }else {
        matrix[i][j] = 0;
      }
    }
  }
  return;
}

void print_matrix(double matrix[4][4], int row, int col) {
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      printf("%.1f ", matrix[i][j]);
    }
    printf("\n");
  }
  return;
}

int main() {
  int row = 4;
  int col = 4;

  double matrix[4][4] = {
    2, 1, 0, 0,
    0, 1, 2, 0,
    2, 4, 5, 1,
    8, 5, 0, 3
  };

  double lower[4][4] = {0};
  create_identity_matrix(lower, row, col);

  double upper[4][4] = {0};

  gaussian_eliminate(matrix, row, col, lower, upper);
  printf("Lower\n---\n");
  print_matrix(lower, row, col);
  printf("Upper\n---\n");
  print_matrix(upper, row, col);
  printf("---\n");
  
  double b[4] = {1, 1, 2, 0};
  double c[4] = {0};
  double x[4] = {0};
  for(size_t i = 0; i < 4; i++) {
    c[i] = 1;
    x[i] = 1;
  }

  for(size_t i = 0; i < row; i++) {
    double tmp = 0;
    for(size_t j = 0; j < i; j++) {
      tmp += lower[i][j] * c[j];
    }  
    c[i] = (b[i] - tmp) / lower[i][i];
  }

  for(size_t i = row; i > 0; i--) {
    double tmp = 0;
    for(size_t j = row; j > i; j--) {
      tmp += upper[i - 1][j - 1] * x[j - 1]; 
    }
    x[i - 1] = (c[i - 1] - tmp) / upper[i - 1][i - 1];
  }

  printf("x = %.4lf\n", x[0]);
  printf("y = %.4lf\n", x[1]);
  printf("z = %.4lf\n", x[2]);
  printf("w = %.4lf\n", x[3]);

  return 0;
}
