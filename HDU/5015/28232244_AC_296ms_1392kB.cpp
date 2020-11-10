#include <bits/stdc++.h>
#define PB push_back
#define fst first
#define sec second
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a, x) memset(a, x, sizeof(a))
typedef long long LL;
#define pi pair<int, int>
#define MP make_pair

using namespace std;
int n, m;
int a[15];
const LL MOD = 10000007;

struct Mat {
  LL mat[15][15];
  void clear() { ms(mat, 0); }
  void print() {
    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= n + 1; j++) {
        printf("%lld ", mat[i][j]);
      }
      printf("\n");
    }
  }
} M, M1;

inline Mat operator*(Mat a, Mat b) {
  Mat c;
  c.clear();
  for (int i = 0; i <= n + 1; i++)
    for (int j = 0; j <= n + 1; j++)
      for (int k = 0; k <= n + 1; k++)
        c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
  return c;
}

inline Mat operator^(Mat a, LL b) {
  Mat ret;
  ret.clear();
  for (int i = 0; i <= n + 1; i++)
    ret.mat[i][i] = 1;
  while (b > 0) {
    if (b & 1)
      ret = ret * a;
    b = b >> 1LL;
    a = a * a;
  }
  return ret;
}

LL solve() {
  M1.clear();
  M.clear();
  M1.mat[0][0] = 23;
  M1.mat[n + 1][0] = 3;
  for (int i = 1; i <= n; i++) {
    M1.mat[i][0] = a[i];
  }
  for (int i = 0; i <= n + 1; i++) {
    for (int j = 0; j <= n + 1; j++) {
      if (j == 0) {
        if (i != n + 1)
          M.mat[i][j] = 10;
      } else if (j == n + 1) {
        M.mat[i][j] = 1;
      } else if (i <= n && j >= 1 && j <= i) {
        M.mat[i][j] = 1;
      }
    }
  }
  Mat ans;
  ans.clear();
  ans = (M ^ (m)) * M1;
  return ans.mat[n][0];
}

int main() {
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    LL ret = solve() % MOD;
    printf("%lld\n", ret);
  }
}
