#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 5e5 + 9, mod = 1e9 + 7;
int n, m, k, fa[N];
ll ans;
ull a[N];
map<ull, vector<pair<int, int>>> mp;
int power(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = (ll)a * a % mod)
    if (b & 1) s = (ll)s * a % mod;
  return s;
}
int find(int x) {
  if (x == fa[x]) return x;
  return fa[x] = find(fa[x]);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  for (int u, v, i = 1; i <= m; i++) {
    cin >> u >> v;
    ull x = a[u] ^ a[v];
    if (mp.find(x) == mp.end()) { mp[x] = {}; }
    mp[x].emplace_back(u, v);
  }
  ans = (ll)((1ull << k) - mp.size()) % mod * power(2, n) % mod;
  for (int i = 1; i <= n; i++) fa[i] = i;
  for (auto &[x, vec] : mp) {
    // cerr << "x = " << x << endl;
    int col = n;
    for (auto &[u, v] : vec) {
      // cerr << "! " << u << " " << v << endl;
      int fu = find(u);
      int fv = find(v);
      if (fu != fv) {
        --col;
        fa[fu] = fv;
      }
    }
    ans += power(2, col);
    for (auto &[u, v] : vec) {
      fa[u] = u;
      fa[v] = v;
    }
  }
  cout << (ans % mod) << endl;
}