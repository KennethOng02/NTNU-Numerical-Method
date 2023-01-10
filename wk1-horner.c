#include <stdio.h>

int main() {
  // P(x) = 1 + x + x^2 + x^3
  //      = 1 + x(1 + x(1 + 1*x))
  //      = 1 + x(1 + x + x^2)
  //      = 1 + x + x^2 + x^3
  double x = 1.0001;

  double result = 1;
  for(int i = 0; i < 50; i++) {
    result = result * x;
    result = result + 1;
  }
  printf("P(1.0001) = %.4lf\n", result);
  return 0;
}
