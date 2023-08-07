#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1 << 8;
const int P = 1000000000 + 9;

int N, M, n;
struct Matrix {
  int a[MAX_N][MAX_N];

  Matrix() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) a[i][j] = 0;
      a[i][i] = 1;
    }
  }

  inline Matrix operator*(const Matrix &x) const {
    Matrix res;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) res.a[i][j] = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++) {
          res.a[i][j] = (1ll * a[i][k] * x.a[k][j] + res.a[i][j]) % P;
        }
    return res;
  }
};

Matrix power(Matrix a, int n) {
  Matrix ans;
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n >>= 1;
  }
  return ans;
}

void solve() {
  scanf("%d%d", &M, &N);
  n = 1 << (M * 2);
  Matrix x;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i & (1 << M) - 1) != (j >> M & (1 << M) - 1)) {
        x.a[i][j] = 0;
        continue;
      }
      bool ok = 1;
      for (int k = 0; k < M && ok; k++) {
        if (k && j >> k & 1 && i >> k + M - 1 & 1) ok = 0;
        if (k + 1 < M && j >> k & 1 && i >> k + M + 1 & 1) ok = 0;
        if (k + 2 < M && j >> k + M & 1 && i >> k + M + 2 & 1) ok = 0;
        if (k - 2 >= 0 && j >> k + M & 1 && i >> k + M - 2 & 1) ok = 0;
      }
      if (ok) x.a[i][j] = 1;
      else
        x.a[i][j] = 0;
    }
  }
  x = power(x, N);
  int ans = 0;
  for (int i = 0; i < n; i++) ans = (ans + x.a[i][0]) % P;
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
  return 0;
}