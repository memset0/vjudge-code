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

const int N = 1e5 + 5;

int n, a, b, p[N];

void solve(std::vector<int> f) {
  for (int i = 0; i < n; i++) {
    p[i] = i + 1;
  }
  int l = 0, r;
  for (auto x : f) {
    r = l + x;
    std::reverse(p + l, p + r);
    l = r;
  }
  for (int i = 0; i < n; i++) {
    printf("%d", p[i]);
    if (i == n - 1) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}

int main() {
  for (int T = read(); T; T--) {
    n = read();
    a = read();
    b = read();
    std::vector<int> f;
    f.push_back(b);
    int s = n - b;
    a--;
    while (a > 0) {
      int res = -1;
      for (int x = 1; x <= b; x++) {
        if (s - x >= a - 1 && s - x <= (a - 1ll) * b) {
          res = x;
          break;
        }
      }
      if (res == -1) {
        break;
      }
      s -= res;
      a--;
      f.push_back(res);
    }
    if (s > 0 || a > 0) {
      printf("NO\n");
      continue;
    }
    std::sort(f.begin(), f.end());
    printf("YES\n");
    solve(f);
  }
  return 0;
}