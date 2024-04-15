#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N = 3e3 + 9;
int n, k, q, a[N], ok[N], deg[N];
vector<int> G[N];
bool check(int l, int r) {
  // cerr << "check " << l << " " << r << endl;
  fill_n(deg + 1, n, 0);
  for (int i = 1; i <= n; i++) { G[i].clear(); }
  for (int i = l; i < r; i++) {
    int x = a[i], y = a[i + 1];
    if ((i - l) & 1) swap(x, y);
    G[x].push_back(y);
    deg[y]++;
    // cerr << x << "->" << y << endl;
  }
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (!deg[i]) { q.push(i); }
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int v : G[u]) {
      --deg[v];
      if (!deg[v]) { q.push(v); }
    }
  }
  for (int i = 1; i <= n; i++)
    if (deg[i]) return false;
  return true;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  for (int l, r, mid, i = 1; i <= n; i++) {
    ok[i] = i, l = i + 1, r = n;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (check(i, mid)) {
        ok[i] = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
  }
  for (int l, r, i = 1; i <= q; i++) {
    cin >> l >> r;
    cout << (r <= ok[l] ? "YES" : "NO") << endl;
  }
}