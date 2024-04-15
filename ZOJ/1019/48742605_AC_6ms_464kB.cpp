#include <cstdio>
#include <iostream>
using namespace std;
int m, n, p;
int grid[105][105];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Trip {
  int a;
  int b;
  int val;
} trips[10005];

int dfs(int x, int y, int step) {
  if (step == p) return 1;
  int a = trips[step].a;
  int b = trips[step].b;
  int dd = trips[step].val;
  int gx, gy;
  for (int i = 1; i < a; i++) {
    gx = x + dir[dd][0] * i, gy = y + dir[dd][1] * i;
    if (grid[gx][gy]) return 0;
    if (gx < 0 || gx >= m || gy < 0 || gy >= n) return 0;
  }

  for (int i = a; i <= b; i++) {
    gx = x + dir[dd][0] * i, gy = y + dir[dd][1] * i;
    if (gx < 0 || gx >= m || gy < 0 || gy >= n) break;
    if (grid[gx][gy]) break;
    if (dfs(gx, gy, step + 1)) return 1;
  }
  return 0;
}

int main() {
  // freopen("tmp.txt", "r", stdin);
  int icase, i, j;
  int a, b, val;
  char c;
  scanf("%d", &icase);
  while (icase--) {
    scanf("%d%d", &m, &n);
    p = 0;
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++) scanf("%d", &grid[i][j]);

    while (scanf("%d%d", &a, &b)) {
      if (a == 0 && b == 0) break;
      scanf(" %c", &c);
      if (c == 'U') val = 0;
      else if (c == 'R')
        val = 1;
      else if (c == 'D')
        val = 2;
      else
        val = 3;
      trips[p].a = a, trips[p].b = b, trips[p++].val = val;
    }

    int res = 0;
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
        if (grid[i][j] == 0) res += dfs(i, j, 0);
    printf("%d\n", res);
  }
  return 0;
}
