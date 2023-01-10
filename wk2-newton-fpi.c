#include <stdio.h>
#include <math.h>

double newton1(double x) {
  return x - (pow(x, 5) + x - 1) / (5 * pow(x, 4) + 1);
}

double newton2(double x) {
  return x - (log(x) + pow(x, 2) - 3) / (1/x + 2 * x);
}

double newton3(double x) {
  return x - (sin(x) - 6 * x - 5) / (cos(x) - 6);
}

int main() {
  double x1 = 0.1;
  double prev1 = 0;
  do {
    prev1 = x1;
    x1 = newton1(x1);
  }while(fabs(x1 - prev1) > 1e-6);

  double x2 = 0.1;
  double prev2 = 0;
  do {
    prev2 = x2;
    x2 = newton2(x2);
  }while(fabs(x2 - prev2) > 1e-6);

  double x3 = 0.1;
  double prev3 = 0;
  do {
    prev3 = x3;
    x3 = newton3(x3);
  }while(fabs(x3 - prev3) > 1e-6);

  printf("1: %.4f\n", x1);
  printf("2: %.4f\n", x2);
  printf("3: %.4f\n", x3);
  return 0;
}
