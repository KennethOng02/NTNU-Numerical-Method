#include <stdio.h>

int main() {
  int num = 4;
  double x[] = {1, 1.05, 1.1, 1.15};
  double fx[] = {0.1924, 0.2414, 0.2933, 0.3492};
  double p = 1.09;
  double res = 0;
  for(size_t i = 0; i < num; i++) {
    double up = 1.0;
    double down = 1.0;
    double acc = 1.0;
    for(size_t j = 0; j < num; j++) {
      if(i != j) {
        up *= (p - x[j]);
        down *= (x[i] - x[j]);
      }
    }
    res += (fx[i] * up / down);
    // res += acc;
  }
  printf("%lf\n", res);
  return 0;
}
