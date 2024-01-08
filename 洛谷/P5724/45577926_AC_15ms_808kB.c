#include "stdio.h"
#define N 109

int n, a[N];

int main() {
  scanf("%d", &n);
  int max = 0;
  int min = 1000;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if (a[i] > max) max = a[i];
    if (a[i] < min) min = a[i];
  }
  printf("%d\n", max - min);
}