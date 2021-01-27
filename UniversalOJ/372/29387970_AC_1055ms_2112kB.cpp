#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
const int N = 30, mod = 998244353, inv2 = (mod + 1) >> 1;
int n, m, tim, G[N], vis[N];
struct z {
  int x;
  z(int x = 0) : x(x) {}
  friend inline z operator*(z a, z b) { return (long long)a.x * b.x % mod; }
  friend inline z operator-(z a, z b) {
    return (a.x -= b.x) < 0 ? a.x + mod : a.x;
  }
  friend inline z operator+(z a, z b) {
    return (a.x += b.x) >= mod ? a.x - mod : a.x;
  }
} ans, inp[N], inv[N], C[N][N];
std::unordered_map<int, std::vector<z>> map;
inline std::vector<z> operator*(const std::vector<z> &a,
                                const std::vector<z> &b) {
  std::vector<z> c(a.size() + b.size() - 1);
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < b.size(); j++)
      c[i + j] = c[i + j] + a[i] * b[j];
  return c;
}
inline std::vector<z> integral(std::vector<z> f) {
  std::vector<z> g(f.size() + 1);
  for (int i = 1; i <= f.size(); i++)
    g[i] = f[i - 1] * inv[i];
  return g;
}
inline z evaluation(std::vector<z> a, int l, int r) {
  a = integral(a);
  z p, s;
  int i;
  for (p = 1, i = 0; i < a.size(); i++)
    s = s + a[i] * p, p = p * r;
  for (p = 1, i = 0; i < a.size(); i++)
    s = s - a[i] * p, p = p * l;
  return s;
}
void initfac(int n) {
  inp[0] = inv[0] = inv[1] = 1;
  for (int i = 2; i < n; i++)
    inv[i] = (mod - mod / i) * inv[mod % i];
  for (int i = 1; i < n; i++)
    inp[i] = inp[i - 1] * inv2;
  for (int i = 0; i < n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
  }
}
int dfs(int u, int s) {
  int res = 1 << u;
  vis[u] = tim;
  for (int v = 0; v < n; v++)
    if (((s >> v) & 1) && ((G[u] >> v) & 1) && vis[v] != tim)
      res |= dfs(v, s);
  return res;
}
void update(std::vector<z> &s, std::vector<z> a, int k) {
  // printf("update <%d> <%d> %d\\n",s.size(),a.size(),k);
  std::vector<z> b(k + 1);
  for (int i = 0; i <= k; i++)
    b[i] = C[k][i] * (i & 1 ? mod - 1 : 1);
  a = integral(a * b);
  for (int i = 0; i < a.size(); i++)
    s[i] = s[i] + a[i], s[0] = s[0] - inp[i] * a[i];
}
std::vector<z> solve(int s) {
  if (map.count(s))
    return map[s];
  int l = __builtin_popcount(s);
  std::vector<z> res;
  std::vector<int> set;
  for (int t, i = 0; i < n; i++)
    if ((s >> i) & 1)
      ++tim, t = dfs(i, s), set.push_back(t), s ^= t;
  for (int x : set)
    s |= x;
  if (set.size() > 1) {
    res = {1};
    for (auto t : set)
      res = res * solve(t);
  } else {
    res.resize(l + 1), res[0] = inp[l];
    for (int i = 0; i < n; i++)
      if ((s >> i) & 1) {
        int t = s ^ (s & (G[i] | (1 << i)));
        update(res, solve(t), __builtin_popcount(s & G[i]));
      }
  }
  return map[s] = res;
}
int main() {
#ifdef local
  freopen("1.in", "r", stdin);
#endif
  std::cin >> n >> m, initfac(N), map[0] = {1};
  for (int u, v, i = 0; i < m; i++)
    std::cin >> u >> v, --u, --v, G[u] |= 1 << v, G[v] |= 1 << u;
  std::vector<z> s = solve((1 << n) - 1), a(n + 1);
  for (int i = 0; i < s.size(); i++)
    a[n] = a[n] + s[i];
  std::reverse(s.begin(), s.end());
  std::cout << (2 - evaluation(s, 1, 2) - evaluation(a, 0, 1)).x << std::endl;
}