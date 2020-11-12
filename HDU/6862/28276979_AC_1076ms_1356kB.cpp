#include <bits/stdc++.h>

inline int read() {
  char c;
  int x;
  for (c = getchar(); !isdigit(c); c = getchar())
    ;
  for (x = 0; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  return x;
}

void solve(int n) {
  if (n == 1) {
    return;
  }
  if (n == 2) {
    printf("234562");
    return;
  }
  printf("4");
  int x = 3, y = 5, c;
  for (int i = 0; i < 6; i++) {
    c = i == 5 ? n - 3 : n - 2;
    for (int j = 0; j < c; j++) {
      printf("%d%d", x, y);
    }
    printf("%d", x);
    x = (x + 4) % 6 + 1;
    y = (y + 4) % 6 + 1;
  }
  printf("3");
  solve(n - 2);
}

int main() {
  for (int T = read(); T; T--) {
    int n = read();
    solve(n);
    printf("\n");
  }
  return 0;
}