#include "bits/stdc++.h"
typedef std::pair<int, int> pii;
const int N = 5011;
const int mx[] = {0, 1, 0, -1}, my[] = {1, 0, -1, 0};
char a[N], tp[N];
int dis[N][51];
int n, m, k, lim;
char &ch(int x, int y) { return a[(x - 1) * m + y]; }
int &d(int x, int y, int f) { return dis[(x - 1) * m + y][f]; }
struct atom {
  int x, y, f;
};
std::queue<atom> q[N * 3];
int bfs(int sx, int sy) {
  for (int t = 1; t <= lim; t++) {
    while (q[t].size()) q[t].pop();
  }
  d(sx, sy, 0) = 1;
  q[1].push({sx, sy, 0});
  for (int t = 1; t <= lim; t++) {
    while (q[t].size()) {
      int x = q[t].front().x;
      int y = q[t].front().y;
      int f = q[t].front().f;
      // fprintf(stderr, "%d %d %d\n", x, y, f);
      q[t].pop();
      if (t != d(x, y, f)) {
        continue;
      }
      for (int i = 0; i < 4; ++i) {
        int vx = x + mx[i], vy = y + my[i];
        if (vx > 0 && vx <= n && vy > 0 && vy <= m && ch(vx, vy) != '#') {
          if (ch(vx, vy) == '.') {
            if (!d(vx, vy, f) || t + 1 < d(vx, vy, f)) {
              d(vx, vy, f) = t + 1;
              q[t + 1].push({vx, vy, f});
            }
          } else if (ch(vx, vy) == 'D') {
            if (f < k) {
              if (!d(vx, vy, f + 1) || t + 2 < d(vx, vy, f + 1)) {
                d(vx, vy, f + 1) = t + 2;
                q[t + 2].push({vx, vy, f + 1});
              }
            } else {
              if (k > 1 || ch(x, y) != 'D') {
                if (!d(vx, vy, k) || t + 3 < d(vx, vy, k)) {
                  d(vx, vy, k) = t + 3;
                  q[t + 3].push({vx, vy, k});
                }
              }
            }
          } else if (ch(vx, vy) == 'B') {
            return t;
          }
        }
      }
    }
  }
  return 0;
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  int task;
  scanf("%d", &task);
  while (task--) {
    scanf("%d%d%d", &n, &m, &k);
    int sx = 0, sy = 0;
    lim = n * m * 3;
    for (int i = 1; i <= n; ++i) {
      scanf("%s", tp + 1);
      for (int j = 1; j <= m; ++j) {
        ch(i, j) = tp[j];
        if (tp[j] == 'A') sx = i, sy = j;
        for (int f = 0; f <= k; ++f) d(i, j, f) = 0;
      }
    }
    int res = bfs(sx, sy);
    if (res) {
      printf("%d\n", res);
    } else {
      puts("HAHAHUHU");
    }
  }
}