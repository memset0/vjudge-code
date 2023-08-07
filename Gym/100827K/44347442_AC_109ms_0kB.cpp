#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 5;
int T, a[N][N], t[N][N], ans[N][N], l[N], r[N], f[N], b[N];
inline int getc() {
  int c = getchar();
  while (isspace(c)) c = getchar();
  return c;
}
inline int getx() {
  int c = getc();
  return c == '-' ? -1 : c - '0';
}
bool fl;
template <const int n> void dfs(int i) {
  if (i == n) {
    for (int j = 0; j < n; j++) {
      if (~f[j]) {
        int x = -1, c = 0;
        for (int i = 0; i < n; i++)
          if (a[i][j] > x) {
            x = a[i][j];
            ++c;
          }
        if (c != f[j]) return;
      }
      if (~b[j]) {
        int x = -1, c = 0;
        for (int i = n - 1; i >= 0; i--)
          if (a[i][j] > x) {
            x = a[i][j];
            ++c;
          }
        if (c != b[j]) return;
      }
    }
    fl = true;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        ans[i][j] = a[i][j];
      }
    return;
  }
  for (int j = 0; j < n; j++) a[i][j] = j;
  do {
    bool ok = true;
    for (int j = 0; j < n; j++) ok &= t[i][j] == -1 || a[i][j] == t[i][j];
    if (!ok) continue;
    if (~l[i]) {
      int x = -1, c = 0;
      for (int j = 0; j < n; j++)
        if (a[i][j] > x) {
          x = a[i][j];
          ++c;
        }
      if (c != l[i]) continue;
    }
    if (~r[i]) {
      int x = -1, c = 0;
      for (int j = n - 1; j >= 0; j--)
        if (a[i][j] > x) {
          x = a[i][j];
          ++c;
        }
      if (c != r[i]) continue;
    }
    for (int pre = 0; pre < i; pre++)
      for (int j = 0; j < n; j++)
        if (a[i][j] == a[pre][j]) {
          ok = false;
        }
    if (!ok) continue;
    dfs<n>(i + 1);
    if (fl) return;
  } while (next_permutation(a[i], a[i] + n));
}
int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  scanf("%d", &T);
  while (T--) {
    int n = getc() - '0';
    getc();
    for (int i = 0; i < n; i++) f[i] = getx();
    getc();
    for (int i = 0; i < n; i++) {
      l[i] = getx();
      for (int j = 0; j < n; j++) {
        t[i][j] = getx();
        if (~t[i][j]) --t[i][j];
      }
      r[i] = getx();
    }
    getc();
    for (int i = 0; i < n; i++) b[i] = getx();
    getc();
    fl = false;
    if (n == 3) {
      dfs<3>(0);
    } else if (n == 4) {
      dfs<4>(0);
    } else {
      dfs<5>(0);
    }
    if (fl) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cout << (ans[i][j] + 1);
        }
        cout << '\n';
      }
    } else {
      cout << "no\n";
    }
    cout << '\n';
  }
}