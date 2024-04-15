#include <bits/stdc++.h>
using namespace std;
#define map _map

int map[105][105];
int vis[105][105];
int n, k;

bool judge(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < n) return true;
  return false;
}
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int dp(int x, int y) {
  if (vis[x][y] != -1) return vis[x][y];
  int i, j;
  vis[x][y] = map[x][y];
  int max = -1, temp;
  for (i = 1; i <= k; i++) {
    for (j = 0; j < 4; j++) {
      int a = x + i * dx[j];
      int b = y + i * dy[j];
      if (judge(a, b) && map[a][b] > map[x][y])
        if (max < (temp = map[x][y] + dp(a, b))) max = temp;
    }
  }
  if (max != -1) vis[x][y] = max;
  return vis[x][y];
}
int main() {
  int i, j;
  while (scanf("%d%d", &n, &k) != EOF) {
    if (n == -1 && k == -1) break;
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++) {
        scanf("%d", &map[i][j]);
        vis[i][j] = -1;
      }
    printf("%d\n", dp(0, 0));
  }
  return 0;
}