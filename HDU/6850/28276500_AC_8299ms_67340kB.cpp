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

int n, m;
bool ban[N], f[N][N];

struct Point {
  int x, y;
} p[N];

struct Edge {
  long long x;
  int i, j;
} e[N * N];

bool operator<(const Edge &i, const Edge &j) { return i.x > j.x; }

long long get(Point u, Point v) {
  return 1ll * (u.x - v.x) * (u.x - v.x) + 1ll * (u.y - v.y) * (u.y - v.y);
}

int main() {
  for (int T = read(); T; T--) {
    n = read();
    m = 0;
    for (int i = 0; i < n; i++) {
      p[i].x = read();
      p[i].y = read();
      ban[i] = false;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }
        e[m++] = (Edge){get(p[i], p[j]), i, j};
      }
    }
    std::sort(e, e + m);
    for (int i = 0, j; i < m; i = j) {
      for (int _j = i; _j < m && e[i].x == e[_j].x; _j++) {
        int u = e[_j].i, v = e[_j].j;
        f[u][v] = !ban[u];
      }
      for (j = i; j < m && e[i].x == e[j].x; j++) {
        int u = e[j].i, v = e[j].j;
        ban[v] |= f[u][v];
      }
    }
    bool ans = false;
    for (int i = 1; i < n; i++) {
      ans |= f[i][0];
    }
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}