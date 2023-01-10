#include <stdio.h>
#include <stdlib.h>

int main() {
  int matrix[10][10] = {0};
  int b[10];
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      if(i == j) {
        matrix[i][j] = -4;
      }else if(abs(i - j) == 1) {
        matrix[i][j] = 2;
      }else if(abs(i - j) >= 2) {
        matrix[i][j] = 0;
      }
      b[i] = i + 2;
    }
  }

  double inverse_d[10][10] = {0};
  double l_plus_u[10][10] = {0};
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      if(i == j) {
        inverse_d[i][j] = 1.0 / matrix[i][j];
      }else {
        l_plus_u[i][j] = 1.0 * matrix[i][j];
      }
    }
  }

  double old2[10] = {0};
  for(int i = 0; i < 10; i++)
    old2[i] = 1;
  for(int k = 0; k < 1000; k++) {
    double temp[10] = {0};
    for(int i = 0; i < 10; i++) {
      for(int j = 0; j < 10; j++) {
        if(l_plus_u[i][j] != 0) {
          temp[i] += 2 * old2[j];
        }
      }
    }
    for(int i = 0; i < 10; i++) {
      temp[i] = b[i] - temp[i];
    }
    for(int i = 0; i < 10; i++) {
      for(int j = 0; j < 10; j++) {
        if(inverse_d[i][j] != 0) {
          old2[i] = inverse_d[i][j] * temp[j];
        }
      }
    }
  }
  for(int i = 0; i < 10; i++)
    printf("%.4lf\n", old2[i]);
  printf("-------\n");

  double old[11] = {0};
  for(int i = 1; i <= 10; i++)
    old[i] = 100;
  double new[11] = {0};
  for(int i = 0; i < 100000; i++) {
    new[1]  = -0.25 * (2  - 2 * (old[2]));
    new[2]  = -0.25 * (3  - 2 * (old[1] + old[3]));
    new[3]  = -0.25 * (4  - 2 * (old[2] + old[4]));
    new[4]  = -0.25 * (5  - 2 * (old[3] + old[5]));
    new[5]  = -0.25 * (6  - 2 * (old[4] + old[6]));
    new[6]  = -0.25 * (7  - 2 * (old[5] + old[7]));
    new[7]  = -0.25 * (8  - 2 * (old[6] + old[8]));
    new[8]  = -0.25 * (9  - 2 * (old[7] + old[9]));
    new[9]  = -0.25 * (10 - 2 * (old[8] + old[10]));
    new[10] = -0.25 * (11 - 2 * (old[9]));

    for(int j = 1; j <= 10; j++) {
      old[j] = new[j];
    }
  }

  for(int j = 1; j <= 10; j++) {
    printf("%.4lf\n", old[j]);
  }
  return 0;
}
