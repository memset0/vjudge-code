#include <bits/stdc++.h>
using namespace std;
const int N = 12;
int n, m, arr[N][N];
int dfs(int x, int y) {
  if (x < 0 || x >= m || y < 0 || y >= n || arr[x][y] == 0)
    return 0;
  arr[x][y] = 0;
  int ret = 1;
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      ret += dfs(x + i, y + j);
  return ret;
}
int main() {
  cin >> m >> n;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> arr[i][j];
    }
  }
  int best = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      best = max(best, dfs(i, j));
    }
  }
  cout << best << endl;
}