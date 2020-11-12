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

const int N = 1e6 + 5;

int n, k, l[N], r[N];

bool check() {
  for (int j = 0; j < 23; j++) {
    for (int i = 1; i < n; i++) {
      l[i] = std::max(l[i], l[i - 1] - k);
      r[i] = std::min(r[i], r[i - 1] + k);
      if (l[i] > r[i]) {
        return false;
      }
    }
    for (int i = 0; i < n - 1; i++) {
      l[i] = std::max(l[i], l[i + 1] - k);
      r[i] = std::min(r[i], r[i + 1] + k);
      if (l[i] > r[i]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  for (int T = read(); T; T--) {
    n = read();
    k = read();
    for (int i = 0; i < n; i++) {
      l[i] = read();
      r[i] = read();
    }
    if (!check()) {
      printf("NO\n");
      continue;
    }
    printf("YES\n");
    int now = l[0];
    printf("%d", now);
    for (int i = 1; i < n; i++) {
      if (std::abs(now - l[i]) <= k) {
        now = l[i];
      } else {
        now = r[i];
      }
      printf(" %d", now);
    }
    printf("\n");
  }
  return 0;
}