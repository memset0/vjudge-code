#include <bits/stdc++.h>

inline int read() {
  char c, _c;
  int x;
  for (c = _c = getchar(); !isdigit(c); c = getchar()) {
    _c = c;
  }
  for (x = 0; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  return _c == '-' ? -x : x;
}

const int N = 2e3 + 5;

int T, n, m, a[N * 2], l[N], r[N], f[N][N * 2], g[N][N * 2];
std::vector<int> e[N];

void dfs(int u, int fa) {
  for (int i = 0; i < m; i++) {
    f[u][i] = 1e9;
  }
  for (auto v : e[u]) {
    if (v == fa) {
      continue;
    }
    dfs(v, u);
  }
  for (int i = l[u]; i <= r[u]; i++) {
    f[u][i] = 0;
    for (auto v : e[u]) {
      if (v == fa) {
        continue;
      }
      f[u][i] += g[v][i];
    }
  }
  int min = 1e9;
  for (int i = 0; i < m; i++) {
    min = std::min(min, f[u][i]);
  }
  for (int i = 0; i < m; i++) {
    g[u][i] = std::min(f[u][i], min + 1);
  }
}

int main() {
  for (int T = read(); T; T--) {
    n = read();
    for (int u = 1; u <= n; u++) {
      e[u].clear();
    }
    for (int i = 1; i < n; i++) {
      int u = read(), v = read();
      e[u].push_back(v);
      e[v].push_back(u);
    }
    m = 0;
    for (int u = 1; u <= n; u++) {
      l[u] = read();
      a[m++] = l[u];
      r[u] = read();
      a[m++] = r[u];
    }
    a[m++] = 0;
    std::sort(a, a + m);
    m = std::unique(a, a + m) - a;
    for (int u = 1; u <= n; u++) {
      l[u] = std::lower_bound(a, a + m, l[u]) - a;
      r[u] = std::lower_bound(a, a + m, r[u]) - a;
    }
    dfs(1, 0);
    int z = std::lower_bound(a, a + m, 0) - a;
    printf("%d\n", g[1][z]);
  }
  return 0;
}