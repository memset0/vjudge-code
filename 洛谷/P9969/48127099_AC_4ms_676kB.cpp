#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const double eps = 1e-8;
const int mod = 998244353, gen = 3;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int sub(int x, int y) { return x - y >= 0 ? x - y : x - y + mod; }
inline int power(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % mod) {
    if (y & 1) { res = 1ll * res * x % mod; }
  }
  return res;
}
namespace Combin {
vector<int> inv, fac, invf;
void getCombin(int n) {
  if (inv.empty()) { inv = fac = invf = vector<int>(2, 1); }
  int m = inv.size();
  n++;
  if (m < n) {
    inv.resize(n);
    fac.resize(n);
    invf.resize(n);
    for (int i = m; i < n; i++) {
      inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
      fac[i] = 1ll * fac[i - 1] * i % mod;
      invf[i] = 1ll * invf[i - 1] * inv[i] % mod;
    }
  }
}
inline int binom(int n, int m) {
  if (n < m || m < 0) { return 0; }
  getCombin(n);
  return 1ll * fac[n] * invf[m] % mod * invf[n - m] % mod;
}
} // namespace Combin
using namespace Combin;
namespace Polynom {
vector<int> rev, rt;
void getRevRoot(int n) {
  int m = log(n) / log(2) + eps;
  rev.resize(n);
  for (int i = 1; i < n; i++) { rev[i] = rev[i >> 1] >> 1 | (i & 1) << m - 1; }
  static int len = 1;
  if (len < n) {
    rt.resize(n);
    for (; len < n; len *= 2) {
      int uni = power(gen, (mod - 1) / (len * 2));
      rt[len] = 1;
      for (int i = 1; i < len; i++) { rt[i + len] = 1ll * rt[i + len - 1] * uni % mod; }
    }
  }
}
void ntt(vector<int> &f, int n) {
  f.resize(n);
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) { swap(f[i], f[rev[i]]); }
  }
  for (int len = 1; len < n; len *= 2) {
    for (int i = 0; i < n; i += len * 2) {
      for (int j = 0; j < len; j++) {
        int x = f[i + j], y = 1ll * f[i + j + len] * rt[j + len] % mod;
        f[i + j] = add(x, y);
        f[i + j + len] = sub(x, y);
      }
    }
  }
}
vector<int> operator*(vector<int> f, vector<int> g) {
  int n = 1, m = f.size() + g.size();
  m--;
  while (n < m) { n *= 2; }
  int invn = power(n, mod - 2);
  getRevRoot(n);
  ntt(f, n);
  ntt(g, n);
  for (int i = 0; i < n; i++) { f[i] = 1ll * f[i] * g[i] % mod; }
  reverse(f.begin() + 1, f.end());
  ntt(f, n);
  f.resize(m);
  for (int i = 0; i < m; i++) { f[i] = 1ll * f[i] * invn % mod; }
  return f;
}
} // namespace Polynom
using Polynom::operator*;
const int N = 5e5 + 9;
int n, a[N], b[N];
string s;
vector<tuple<int, int, int>> ans;
int take_move(int op, int x, int y = -1) {
  if (op == 2) {
    if (x == 0) return y;
    if (y == 0) return x;
  }
  ans.emplace_back(op, x, y);
  return ans.size();
}
int calc_move(vector<int> arr) {
  if (arr.size() <= 1) { return 0; }
  if (arr.size() == 2) { return arr[1] - arr[0]; }
  int m = arr.back();
  vector<int> f(m);
  for (const auto &x : arr) { f[x - 1]++; }
  vector<int> g = f;
  reverse(g.begin(), g.end());
  f = f * g;
  int ans = m - 1;
  for (int k = (arr.back() - arr[0]) / 2 + 1; k <= m - 1; k++) {
    if (f[m - 1 + ans] < f[m - 1 + k]) { ans = k; }
  }
  return ans;
}
int solve(vector<int> vec) {
  if (vec.size() == 0) return 0;
  if (vec.size() == 1) { return take_move(1, vec[0]); }
  if (vec.size() > 1e5) {
    int diff = calc_move(vec);
    vector<int> s;
    vector<int> t; // 可以平移
    for (int x : vec) b[x] = true;
    for (int x : vec)
      if (b[x]) {
        if (x + diff <= n && b[x + diff]) {
          t.push_back(x);
          b[x + diff] = 0;
        } else {
          s.push_back(x);
        }
      }
    for (int x : vec) b[x] = false;
    if (t.size()) {
      int x = solve(s);
      int y1 = solve(t);
      int y2 = take_move(3, y1, diff);
      if (t.size() < s.size()) {
        return take_move(2, x, take_move(2, y1, y2));
      } else {
        return take_move(2, y1, take_move(2, x, y2));
      }
    }
  }
  int mid = vec.size() >> 1;
  int x = solve(vector<int>(vec.begin(), vec.begin() + mid));
  int y = solve(vector<int>(vec.begin() + mid, vec.end()));
  return take_move(2, x, y);
}
int main() {
#ifdef memset0
  freopen("I2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> s;
  vector<int> vec;
  for (int i = 1; i <= n; i++) {
    a[i] = s[i - 1] == '1';
    if (a[i]) { vec.push_back(i); }
  }
  solve(vec);
  cout << ans.size() << endl;
  for (auto [op, x, y] : ans) {
    if (op == 1) {
      cout << "1 " << x << endl;
    } else {
      cout << op << " " << x << " " << y << endl;
    }
  }
#ifdef memset0
  vector<vector<int>> data;
  for (auto [op, x, y] : ans) {
    if (op == 1) {
      data.push_back({x});
    } else if (op == 2) {
      auto t = data[x - 1];
      t.insert(t.end(), data[y - 1].begin(), data[y - 1].end());
      data.push_back(t);
    } else if (op == 3) {
      auto t = data[x - 1];
      for (int &u : t) u += y;
      data.push_back(t);
    }
  }
  long long sum = 0;
  for (const auto &vec : data) { sum += vec.size(); }
  cerr << "sigma size: " << sum << endl;
  auto mine = data.back();
  sort(mine.begin(), mine.end());
  // for (int x : vec) cerr << x << " ";
  // cerr << endl;
  // for (int x : mine) cerr << x << " ";
  // cerr << endl;
  assert(mine == vec);
#endif
}
