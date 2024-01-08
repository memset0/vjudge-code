#include "stdio.h"

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);

  if ((a < 60) + (b < 60) + (c < 60) == 1) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  
  return 0;
}