#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double get_result(double mid) {
  return mid - pow(mid, (double) 1/3) - 2;
}
int main() {
  // f(x) = x - x^(1/3) - 2
  double low = 3;
  double high = 4;
  double mid = 1;
  double stopping_point = 10e-6;
  double result = 1;
  while(high - low > stopping_point || fabs(result) > stopping_point) {
    mid = (high + low) / 2;
    result = get_result(mid);
    if(result < 0) low = mid; else high = mid;
  }
  printf("%.4lf\n", mid);
  return 0;
}
