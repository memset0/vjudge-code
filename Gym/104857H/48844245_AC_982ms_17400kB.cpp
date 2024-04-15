#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
using ll = long long;
const int L = 1e6;
int T;
ll f[L], g[L], mod, real_mod;
vector<pair<ll, ll>> fs, gs;
void init() {
  int k = 1;
  for (; k < L; k++) {
    f[k] = max<ll>(k, g[k / 2] + g[k / 3] + g[k / 5] + g[k / 7]);
    g[k] = max<ll>(k, f[k / 2] + f[k / 3] + f[k / 4] + f[k / 5]);
    if (f[k] > 1e15 && g[k] > 1e15) break;
  }
  for (int i = 0; i < k; i++) {
    f[i] %= mod, g[i] %= mod;
  }
  for (; k < L; k++) {
    f[k] = (g[k / 2] + g[k / 3] + g[k / 5] + g[k / 7]) % mod;
    g[k] = (f[k / 2] + f[k / 3] + f[k / 4] + f[k / 5]) % mod;
  }
}
ll F(ll n) {
  if (n < L) return f[n];
  auto it = --upper_bound(all(fs), make_pair(n, LLONG_MAX));
  return it->second;
}
ll G(ll n) {
  if (n < L) return g[n];
  auto it = --upper_bound(all(gs), make_pair(n, LLONG_MAX));
  return it->second;
}
ll calcF(ll n) { return (G(n / 2) + G(n / 3) + G(n / 5) + G(n / 7)) % mod; }
ll calcG(ll n) { return (F(n / 2) + F(n / 3) + F(n / 4) + F(n / 5)) % mod; }
void solve() {
  fs.emplace_back(L, calcF(L));
  gs.emplace_back(L, calcG(L));
  while (fs.back().first <= 1e15 || gs.back().first <= 1e15) {
    if (fs.back().first <= gs.back().first) {
      // extend f
      ll l = fs.back().first, r = 1e15, mid, res = -1;
      while (l <= r) {
        mid = (l + r) >> 1;
        if (calcF(mid) == fs.back().second) {
          res = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      assert(res != -1);
      fs.emplace_back(res + 1, calcF(res + 1));
    } else {
      // extend g
      ll l = gs.back().first, r = 1e15, mid, res = -1;
      while (l <= r) {
        mid = (l + r) >> 1;
        if (calcG(mid) == gs.back().second) {
          res = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      assert(res != -1);
      gs.emplace_back(res + 1, calcG(res + 1));
    }
  }
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> f[0] >> g[0] >> T >> real_mod;
  mod = real_mod;
  while (mod < 1e15) mod <<= 1;
  init();
  solve();
  while (T--) {
    ll m;
    cin >> m;
    cout << (F(m) % real_mod) << " " << (G(m) % real_mod) << endl;
  }
}