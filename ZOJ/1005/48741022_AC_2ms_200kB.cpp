#include <stdio.h>
#include <string>

int main() {
  int ca, cb, N, nowA, nowB;
  while (scanf("%d%d%d", &ca, &cb, &N) != EOF) {
    nowA = 0;
    nowB = 0;
    if (cb == N) {
      printf("fill B\n");
      printf("success\n");
      continue;
    }
    if (ca == N) {
      printf("fill A\n");
      printf("pour A B\n");
      printf("success\n");
      continue;
    }
    while (nowB != N) {
      if (nowB == 0) {
        nowB = cb;
        printf("fill B\n");
      }
      if (nowA == ca) {
        nowA = 0;
        printf("empty A\n");
      }
      if (nowB > (ca - nowA)) {
        nowB -= (ca - nowA);
        nowA = ca;
        printf("pour B A\n");
      } else {
        nowA += nowB;
        nowB = 0;
        printf("pour B A\n");
      }
    }
    printf("success\n");
  }
}
