// AC Onsite
#include <bits/stdc++.h>
using namespace std;
int n, m, r;
void calc(int v, vector<pair<int, int>> &res) {
  int las = -1;
  bool cont = false;
  for (int i = 0; i < n; i++) {
    int g = ((v >> i) & 1);
    if (g == 1) {
      if (cont) {
        cont = false;
        res.emplace_back(i - las, las);
      }
    } else if (!cont) {
      cont = true;
      las = i;
    }
  }
  if (cont) res.emplace_back(n - las, las);
}
void print(int x, char ch) {
  for (int i = 0; i < n; i++) printf("%d", ((x >> i) & 1));
  putchar(ch);
}
vector<pair<int, int>> prew[1 << 14];
vector<tuple<int, int, vector<char>>> forw;
const int mod = 998244353;
void add_mod(int &a, int b) {
  if ((a += b) >= mod) a -= mod;
}
int f[1 << 14], g[1 << 14];
vector<int> bits[1 << 14];
vector<int> ubits[1 << 14];
vector<tuple<int, int, int>> ask[1010];
int main() {
  scanf("%d%d%d", &n, &m, &r);
  for (int i = 0, a, b, c, d; i < r; i++) {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a == 1 && d == 0) {
      // cells in the first column must be different
      printf("0");
      return 0;
    }
    if (a != 1) ask[a].emplace_back(b - 1, c - 1, d);
  }
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++)
      if (((i >> j) & 1)) bits[i].emplace_back(j);
      else
        ubits[i].emplace_back(j);
  }
  auto build = [&](int X, int Y) {
    int l = bits[X].size();
    auto &x = bits[X], &y = bits[Y];
    vector<char> res(n);
    for (int i = 0; i < l; i++) {
      auto [a, b] = minmax(x[i], y[i]);
      for (int j = a; j <= b; j++) res[j] = i + 1;
    }
    forw.emplace_back(X, Y, res);
  };
  for (int i = 0; i < (1 << n); i++) {
    auto &v = ubits[i];
    function<void(int, int, int)> dfs = [&](unsigned int len, int S, int lst) {
      if (len == v.size()) return build(i, S), void();
      for (auto pos : {v[len] - 1, v[len] + 1})
        if (pos > lst && pos >= 0 && pos < n) dfs(len + 1, S ^ (1 << pos), pos);
    };
    dfs(0, (1 << n) - 1, -1);
  }
  f[(1 << n) - 1] = 1;
  int ptr = 1;
  while (--m) {
    ++ptr;
    memset(g, 0, sizeof g);
    for (int l = 1; l < (1 << n); l <<= 1)
      for (int i = 0; i < (1 << n); i += (l << 1))
        for (int j = 0; j < l; j++) add_mod(f[i + j], f[i + j + l]);
    for (auto &[i, j, col] : forw) {
      bool flg = true;
      for (auto [x, y, diff] : ask[ptr]) flg &= (diff ^ (col[x] == col[y]));
      if (flg) add_mod(g[j], f[i]);
    }
    swap(f, g);
  }
  int ans = 0;
  for (int i = 0; i < (1 << n); i++) add_mod(ans, f[i]);
  printf("%d", ans);
}
