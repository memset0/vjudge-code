#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
int n, m, x, y;
set<int> a, b;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  while (true) {
    cin >> n >> m;
    if (!n && !m) break;
    a.clear(), b.clear();
    rep(i, 1, n) { cin >> x, a.insert(x); }
    rep(i, 1, m) { cin >> x, b.insert(x); }
    for (int x : b)
      if (a.count(x)) a.erase(x);
    if (!a.size()) {
      cout << "NULL" << endl;
    } else {
      for (int x : a) cout << x << " ";
      cout << endl;
    }
  }
}