#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int maxn = 114514;
const int maxm = 5 * maxn;

struct ufset {
  int fa[maxn];
  void init() { memset(fa, -1, sizeof fa); }
  int f(int x) {
    if (fa[x] < 0)
      return x;
    return fa[x] = f(fa[x]);
  }
  int operator[](int x) { return f(x); }
  bool merge(int x, int y) {
    if ((x=f(x)) == (y=f(y))) return false;
    if (fa[x] > fa[y]) swap(x, y);
    fa[x] += fa[y];
    fa[y] = x;
    return true;
  }
  bool query(int x, int y) { return f(x) == f(y); }
} uf[62];
int n, m, q;
ll z;

struct edge {
  int u, v;
  ll w;
} e[maxm];

void init() {
  --z;
  if(z<0) {
    uf[0].init();
    for (int i = 1; i <= m; i++) {
      uf[0].merge(e[i].u, e[i].v);
    }
    return;
  }
  for (int j = 1; j <= 60; j++) {
    uf[j].init();
    ll upper_mask = (((1ll << 60) - 1) >> j) << j;
    ll that_bit = (1ll << (j - 1));
    if ((z & that_bit) != 0) continue;
    ll good_mask = (z & upper_mask) | that_bit;
    for (int i = 1; i <= m; i++) {
      if ((e[i].w & good_mask) == good_mask) {
        uf[j].merge(e[i].u, e[i].v);
      }
    }
  }
}

bool query(int x, int y) {
  if (z<0) {
    return uf[0].query(x, y);
  }
  for (int j = 60; j >= 1; j--) {
    if (uf[j].query(x, y)) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0), ios::sync_with_stdio(false);
  cin >> n >> m >> q;
  cin >> z;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].u >> e[i].v >> e[i].w;
  }
  init();
  for (int i = 1; i <= q; i++) {
    int x, y;
    cin >> x >> y;
    cout << (query(x,y) ? "Yes\n" : "No\n");
  }
  return 0;
}
