#include <bits/stdc++.h>
using namespace std;

const int N = 109;
int n, a[N];
set<int> primes;
vector<pair<int, int>> f[N];

vector<pair<int, int>> split(int x) {
  vector<pair<int, int>> res;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0) {
      res.emplace_back(i, 0);
      while (x % i == 0) {
        x /= i;
        res.back().second++;
      }
    }
  if (x > 1) res.emplace_back(x, 1);
  sort(res.begin(), res.end());
  return res;
}

const int X = 2e7;
int _sg[X];

int SG(int x) {
  if (x < X && (~_sg[x])) return _sg[x];
  set<int> s;
  for (int i = 1; (1 << (i - 1)) <= x; i++) {
    // cerr << i << " " << (x >> i) << " " << (x & ((1 << (i - 1)) - 1)) << endl;
    s.insert(SG((x >> i) | (x & ((1 << (i - 1)) - 1))));
  }
  for (int i = 0;; i++) {
    if (!s.count(i)) {
      // fprintf(stderr, "SG(%d) = %d\n", x, i);
      if (x < X) {
        _sg[x] = i;
      }
      return i;
    }
  }
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  memset(_sg, -1, sizeof(_sg));
  _sg[0] = 0;
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i] = split(a[i]);
    for (auto [p, k] : f[i]) {
      primes.insert(p);
    }
  }
  int sg = 0;
  for (int p : primes) {
    set<int> b;
    for (int i = 1; i <= n; i++)
      for (auto [_p, _k] : f[i])
        if (p == _p) {
          b.insert(_k);
        }
    int x = 0;
    for (int k : b) x |= 1 << (k - 1);
    sg ^= SG(x);
  }
  cout << (sg ? "Mojtaba" : "Arpa") << endl;
}