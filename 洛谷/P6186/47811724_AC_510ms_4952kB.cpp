#include "bits/stdc++.h"
using namespace std;
int n, m;
const int maxn = 222222;
int a[maxn];
int z[maxn];
int q[maxn];
long long bit[maxn];
#define lb(x) ((x)&-(x))
void add(int x, int y)
{
  if (x == 0) {
    bit[x] += y;
  } else while (x) {
    bit[x] += y;
    x -= lb(x);
  }
}
long long sum(int x)
{
  long long y = 0;
  if (x == 0) y += bit[x], ++x;
  while (x < maxn) {
    y += bit[x];
    x += lb(x);
  }
  return y;
}
int main()
{
  cin.sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    z[i] = sum(a[i]);
    add(a[i], 1);
  }
  memset(bit, 0, sizeof bit);
  for (int i = 1; i <= n; ++i) {
    add(z[i], 1);
  }
  for (int i = 0; i <= n; ++i) {
    q[i] = sum(i);
  }
  memset(bit, 0, sizeof bit);
  for (int i = 0; i <= n; ++i) {
    add(i, q[i]);
  }
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    if (u == 1) {
      swap(a[v], a[v + 1]);
      swap(z[v], z[v + 1]);
      if (a[v] > a[v + 1]) {
        z[v + 1]++;
        q[z[v + 1]]++;
        add(z[v + 1], 1);
      } else {
        q[z[v]]--;
        add(z[v], -1);
        z[v]--;
      }
    } else {
      cout << sum(v + 1) << '\n';
    }
  }
}