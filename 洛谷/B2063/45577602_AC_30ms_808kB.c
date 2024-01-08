#include "stdio.h"

int main() {
  int x, n;
  scanf("%d%d", &x, &n);
  
  double s = x;
  for (int i = 1; i <= n; i++) {
    s *= 1.001;
  }
  printf("%.4lf\n", s);
  
  return 0;
}