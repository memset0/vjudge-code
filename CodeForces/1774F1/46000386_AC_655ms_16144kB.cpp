#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9, mod = 998244353;
int T, x, op, mul = 1;
long long sumx, sumd;
map<long long, int> mp;
int power(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = (long long)a * a % mod)
    if (b & 1) s = (long long)s * a % mod;
  return s;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> op;
    if (op == 1) {
      cin >> x;
      (mp[x + sumx] += power(mul, mod - 2)) %= mod;
    } else if (op == 2) {
      cin >> x;
      if (sumx == 0) {
        for (auto &it : mp) { it.second = (long long)it.second * mul % mod; }
        mul = 1;
      }
      sumx += x;
      while (mp.size() && mp.begin()->first <= sumx) { mp.erase(mp.begin()); }
      sumd += x;
    } else {
      if (sumd > N) { continue; }
      if (sumd) {
        vector<pair<long long, int>> tp(mp.begin(), mp.end());
        for (const auto &it : tp) {
          if (it.first - sumd > sumx) { (mp[it.first - sumd] += it.second) %= mod; }
        }
        sumd <<= 1;
      } else {
        mul = (mul << 1) % mod;
      }
    }
    // cerr << ">>> " << op << " " << x << endl;
    // for (auto x : st) { cerr << x.first << "," << x.second << " "; }
    // cerr << endl << "sumx = " << sumx << "  sumd = " << sumd << endl;
  }

  long long ans = 0;
  for (const auto &it : mp) { ans += it.second; }
  cout << (ans % mod * mul % mod) << endl;
}