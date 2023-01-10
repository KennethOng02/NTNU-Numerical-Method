#include <stdio.h>
#include <math.h>

double g(double x) {
  return pow(2 * x + 2, (double) 1 / 3);
}

int main() {
  double x = 0.1;
  double prev = 0;
  while(fabs(x - prev) > 10e-6) {
    prev = x;
    x = g(x);
  }
  printf("%f\n", x);
  return 0;
}
