#include <stdio.h>
#include <math.h>

double get_slope(double x) {
  return 4 * pow(x, 3) - 6 * pow(x, 2);
}
int main() {
  double learning_rate = 0.2;
  double initial_point = 0;
  double new_point = 1;
  while(fabs(get_slope(new_point) - get_slope(initial_point)) >= 10e-6) {
    initial_point = new_point;
    new_point = initial_point - learning_rate * get_slope(initial_point);
  }
  printf("%.4lf\n", initial_point);
  return 0;
}
