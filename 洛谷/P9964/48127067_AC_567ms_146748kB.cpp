#include <bits/stdc++.h>

const int N = 5005;

int n, p[N], g[N][N];
short f[N][N];
char s[N];

struct infol {
  short i, j;
  bool operator<(const infol &rhs) const {
    if (f[i][j] < f[i][rhs.j]) {
      return false;
    }
    if (f[i][j] > f[i][rhs.j]) {
      return true;
    }
    if (g[i][j] + (j << 1) < g[i][rhs.j] + (rhs.j << 1)) {
      return false;
    }
    if (g[i][j] + (j << 1) > g[i][rhs.j] + (rhs.j << 1)) {
      return true;
    }
    return j < rhs.j;
  }
};
std::priority_queue<infol> ql[N];

struct infor {
  short i, j;
  bool operator<(const infor &rhs) const {
    if (f[i][j] < f[rhs.i][j]) {
      return false;
    }
    if (f[i][j] > f[rhs.i][j]) {
      return true;
    }
    if (g[i][j] - (i << 1) < g[rhs.i][j] - (rhs.i << 1)) {
      return false;
    }
    if (g[i][j] - (i << 1) > g[rhs.i][j] - (rhs.i << 1)) {
      return true;
    }
    return i < rhs.i;
  }
};
std::priority_queue<infor> qr[N];

int main() {
  scanf("%d%s", &n, s + 1);
  s[0] = '?';
  s[n + 1] = '!';
  for (int i = 1; i <= n; i++) {
    p[i] = 1;
    for (; (s[i - p[i]] == '^' && s[i + p[i]] == 'v') || (s[i - p[i]] == 'v' && s[i + p[i]] == '^'); p[i]++)
      ;
  }
  for (int len = 1; len <= n; len++) {
    for (int i = 1; i <= n; i++) {
      int j = i + len - 1;
      if (j > n) {
        break;
      }
      if (i == j) {
        f[i][j] = 1;
        g[i][j] = 0;
      } else {
        f[i][j] = n + 2;
        while (!ql[i].empty() && j > ql[i].top().j + std::min(p[ql[i].top().j + 1], ql[i].top().j - i + 2)) {
          ql[i].pop();
        }
        if (!ql[i].empty()) {
          if (f[i][j] > f[i][ql[i].top().j] + 1) {
            f[i][j] = f[i][ql[i].top().j] + 1;
            g[i][j] = g[i][ql[i].top().j] + (ql[i].top().j - i + 1) - (j - ql[i].top().j - 1);
          } else if (f[i][j] == f[i][ql[i].top().j] + 1) {
            g[i][j] = std::min(g[i][j], g[i][ql[i].top().j] + (ql[i].top().j - i + 1) - (j - ql[i].top().j - 1));
          }
        }
        while (!qr[j].empty() && i < qr[j].top().i - std::min(p[qr[j].top().i - 1], j - qr[j].top().i + 2)) {
          qr[j].pop();
        }
        if (!qr[j].empty()) {
          if (f[i][j] > f[qr[j].top().i][j] + 1) {
            f[i][j] = f[qr[j].top().i][j] + 1;
            g[i][j] = g[qr[j].top().i][j] + (j - qr[j].top().i + 1) - (qr[j].top().i - i - 1);
          } else if (f[i][j] == f[qr[j].top().i][j] + 1) {
            g[i][j] = std::min(g[i][j], g[qr[j].top().i][j] + (j - qr[j].top().i + 1) - (qr[j].top().i - i - 1));
          }
        }
      }
      if (j < n) {
        infol x = (infol){(short)i, (short)j};
        if (ql[i].empty() || ql[i].top() < x || ql[i].top().j + std::min(p[ql[i].top().j + 1], ql[i].top().j - i + 2) < j + std::min(p[j + 1], j - i + 2)) {
          ql[i].push(x);
        }
      }
      if (i > 1) {
        infor x = (infor){(short)i, (short)j};
        if (qr[j].empty() || qr[j].top() < x || qr[j].top().i - std::min(p[qr[j].top().i - 1], j - qr[j].top().i + 2) > i - std::min(p[i - 1], j - i + 2)) {
          qr[j].push(x);
        }
      }
    }
  }
  printf("%d %d\n", (int)f[1][n], g[1][n]);
  return 0;
}
