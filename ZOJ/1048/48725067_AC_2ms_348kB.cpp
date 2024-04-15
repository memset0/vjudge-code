#include <stdio.h>

int main() {
  double sum = 0;
  for (int i = 1; i < 13; i++) {
    double tmp = 0;
    scanf("%lf", &tmp);
    sum += tmp;
  }
  printf("$%.2lf\n", sum / 12);
  return 0;
}