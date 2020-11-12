#include <bits/stdc++.h>

const int N = 2e3 + 5;

bool ban[N];
int T, n, m, q, a[N], b[N * 2], f[N][N * 2][2][2], g[N][N * 2][2][2];
std::vector<int> vec1[N], vec2[N], ansl, ansr;
std::vector<std::vector<int>> ans;

std::vector<int> get() {
  std::vector<int> res;
  std::string str;
  getline(std::cin, str);
  if (str[0] == ' ') {
    str.erase(str.begin(), str.begin() + 1);
  }
  str = str + ' ';
  for (int i = 0, j = 0; i < str.size(); i++) {
    if (str[i] == ' ') {
      int x = 0;
      for (; j < i; j++) {
        if (str[j] >= '0' && str[j] <= '9') {
          x = x * 10 + str[j] - '0';
        }
      }
      if (x > 0) {
        res.push_back(x);
      }
    }
  }
  return res;
}

void dfs(int i, int j, int x, int y, int u, int v) {
  if (i == 0 && j == 0) {
    return;
  }
  if (x == 0 && y == 0) {
    if (f[i][j][0][0] == f[i - 1][j - 1][0][0] + 1 &&
        g[i][j][0][0] == g[i - 1][j - 1][0][0]) {
      dfs(i - 1, j - 1, 0, 0, -1, -1);
      return;
    }
    if (f[i][j][0][0] == f[i - 1][j - 1][1][1] + 1 &&
        g[i][j][0][0] == g[i - 1][j - 1][1][1] + 1) {
      dfs(i - 1, j - 1, 1, 1, i - 1, j - 1);
      return;
    }
  }
  if (x == 1 && y == 0) {
    if (f[i][j][1][0] == f[i - 1][j][0][0] &&
        g[i][j][1][0] == g[i - 1][j][0][0]) {
      ansl.push_back(i);
      ansr.push_back(u);
      std::vector<int> tmp;
      for (int k = j + 1; k <= v; k++) {
        tmp.push_back(b[k]);
      }
      ans.push_back(tmp);
      dfs(i - 1, j, 0, 0, -1, -1);
      return;
    }
    if (f[i][j][1][0] == f[i - 1][j][1][0] &&
        g[i][j][1][0] == g[i - 1][j][1][0]) {
      dfs(i - 1, j, 1, 0, u, v);
      return;
    }
  }
  if (x == 0 && y == 1) {
    if (f[i][j][0][1] == f[i][j - 1][0][0] &&
        g[i][j][0][1] == g[i][j - 1][0][0]) {
      ansl.push_back(i + 1);
      ansr.push_back(u);
      std::vector<int> tmp;
      for (int k = j; k <= v; k++) {
        tmp.push_back(b[k]);
      }
      ans.push_back(tmp);
      dfs(i, j - 1, 0, 0, -1, -1);
      return;
    }
    if (f[i][j][0][1] == f[i][j - 1][0][1] &&
        g[i][j][0][1] == g[i][j - 1][0][1]) {
      dfs(i, j - 1, 0, 1, u, v);
      return;
    }
  }
  if (x == 1 && y == 1) {
    if (i > 0) {
      if (f[i][j][1][1] == f[i - 1][j][0][1] &&
          g[i][j][1][1] == g[i - 1][j][0][1]) {
        dfs(i - 1, j, 0, 1, u, v);
        return;
      }
      if (f[i][j][1][1] == f[i - 1][j][1][1] &&
          g[i][j][1][1] == g[i - 1][j][1][1]) {
        dfs(i - 1, j, 1, 1, u, v);
        return;
      }
    }
    if (j > 0) {
      if (f[i][j][1][1] == f[i][j - 1][1][0] &&
          g[i][j][1][1] == g[i][j - 1][1][0]) {
        dfs(i, j - 1, 1, 0, u, v);
        return;
      }
      if (f[i][j][1][1] == f[i][j - 1][1][1] &&
          g[i][j][1][1] == g[i][j - 1][1][1]) {
        dfs(i, j - 1, 1, 1, u, v);
        return;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  for (std::cin >> T; T; T--) {
    std::cin >> n >> q;
    for (int i = 1; i <= n + 1; i++) {
      vec1[i].clear();
      vec2[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
      ban[i] = false;
    }
    ban[n + 1] = true;
    for (int i = 0; i < q; i++) {
      char opt;
      std::cin >> opt;
      if (opt == 'A') {
        int l;
        std::cin >> l;
        vec1[l] = get();
      } else if (opt == 'D') {
        int l, r;
        std::cin >> l >> r;
        for (int j = l; j <= r; j++) {
          ban[j] = true;
        }
        vec2[l].clear();
      } else {
        int l, r;
        std::cin >> l >> r;
        for (int j = l; j <= r; j++) {
          ban[j] = true;
        }
        vec2[l] = get();
      }
    }
    m = 0;
    for (int i = 1; i <= n + 1; i++) {
      for (auto x : vec1[i]) {
        b[++m] = x;
      }
      for (auto x : vec2[i]) {
        b[++m] = x;
      }
      if (!ban[i]) {
        b[++m] = a[i];
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        f[i][j][0][0] = -1e9;
        f[i][j][0][1] = -1e9;
        f[i][j][1][0] = -1e9;
        f[i][j][1][1] = -1e9;
        if (i == 0 && j == 0) {
          f[i][j][0][0] = 0;
        } else {
          if (i > 0) {
            f[i][j][1][0] = std::max(
                f[i][j][1][0], std::max(f[i - 1][j][0][0], f[i - 1][j][1][0]));
            f[i][j][1][1] = std::max(
                f[i][j][1][1], std::max(f[i - 1][j][0][1], f[i - 1][j][1][1]));
          }
          if (j > 0) {
            f[i][j][0][1] = std::max(
                f[i][j][0][1], std::max(f[i][j - 1][0][0], f[i][j - 1][0][1]));
            f[i][j][1][1] = std::max(
                f[i][j][1][1], std::max(f[i][j - 1][1][0], f[i][j - 1][1][1]));
          }
          if (i > 0 && j > 0 && a[i] == b[j]) {
            f[i][j][0][0] = std::max(
                f[i][j][0][0],
                std::max(f[i - 1][j - 1][0][0], f[i - 1][j - 1][1][1]) + 1);
          }
        }
        g[i][j][0][0] = 1e9;
        g[i][j][0][1] = 1e9;
        g[i][j][1][0] = 1e9;
        g[i][j][1][1] = 1e9;
        if (i == 0 && j == 0) {
          g[i][j][0][0] = 0;
        } else {
          if (i > 0) {
            if (f[i][j][1][0] == f[i - 1][j][0][0]) {
              g[i][j][1][0] = std::min(g[i][j][1][0], g[i - 1][j][0][0]);
            }
            if (f[i][j][1][0] == f[i - 1][j][1][0]) {
              g[i][j][1][0] = std::min(g[i][j][1][0], g[i - 1][j][1][0]);
            }
            if (f[i][j][1][1] == f[i - 1][j][0][1]) {
              g[i][j][1][1] = std::min(g[i][j][1][1], g[i - 1][j][0][1]);
            }
            if (f[i][j][1][1] == f[i - 1][j][1][1]) {
              g[i][j][1][1] = std::min(g[i][j][1][1], g[i - 1][j][1][1]);
            }
          }
          if (j > 0) {
            if (f[i][j][0][1] == f[i][j - 1][0][0]) {
              g[i][j][0][1] = std::min(g[i][j][0][1], g[i][j - 1][0][0]);
            }
            if (f[i][j][0][1] == f[i][j - 1][0][1]) {
              g[i][j][0][1] = std::min(g[i][j][0][1], g[i][j - 1][0][1]);
            }
            if (f[i][j][1][1] == f[i][j - 1][1][0]) {
              g[i][j][1][1] = std::min(g[i][j][1][1], g[i][j - 1][1][0]);
            }
            if (f[i][j][1][1] == f[i][j - 1][1][1]) {
              g[i][j][1][1] = std::min(g[i][j][1][1], g[i][j - 1][1][1]);
            }
          }
          if (i > 0 && j > 0 && a[i] == b[j]) {
            if (f[i][j][0][0] == f[i - 1][j - 1][0][0] + 1) {
              g[i][j][0][0] = std::min(g[i][j][0][0], g[i - 1][j - 1][0][0]);
            }
            if (f[i][j][0][0] == f[i - 1][j - 1][1][1] + 1) {
              g[i][j][0][0] =
                  std::min(g[i][j][0][0], g[i - 1][j - 1][1][1] + 1);
            }
          }
        }
      }
    }
    ansl.clear();
    ansr.clear();
    ans.clear();
    if (f[n][m][0][0] == f[n][m][1][1]) {
      if (g[n][m][0][0] < g[n][m][1][1] + 1) {
        printf("%d %d\n", n - f[n][m][0][0], g[n][m][0][0]);
        dfs(n, m, 0, 0, -1, -1);
      } else {
        printf("%d %d\n", n - f[n][m][1][1], g[n][m][1][1] + 1);
        dfs(n, m, 1, 1, n, m);
      }
    } else if (f[n][m][0][0] > f[n][m][1][1]) {
      printf("%d %d\n", n - f[n][m][0][0], g[n][m][0][0]);
      dfs(n, m, 0, 0, -1, -1);
    } else {
      printf("%d %d\n", n - f[n][m][1][1], g[n][m][1][1] + 1);
      dfs(n, m, 1, 1, n, m);
    }
    std::reverse(ansl.begin(), ansl.end());
    std::reverse(ansr.begin(), ansr.end());
    std::reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
      printf("%d %d", ansl[i], ansr[i]);
      for (auto x : ans[i]) {
        printf(" %d", x);
      }
      printf("\n");
    }
  }
  return 0;
}