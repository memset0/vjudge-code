#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
#define all(x) (x).begin(), (x).end()
using namespace std;
const int N = 1e4 + 9, M = 1.1e3 + 9;
int n, m, cnt[M];
vector<int> f[M];
void upsolve(const vector<int> &f, vector<int> &g) {
  for (int i = 0; i + 1 < f.size(); i += 2) {
    g.push_back(f[i] + f[i + 1]);
  }
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int k, w, i = 1; i <= n; i++) {
    cin >> k >> w;
    f[k].push_back(w);
  }
  cin >> m;
  for (int k, x, i = 1; i <= m; i++) {
    cin >> k >> x;
    if (x == 0) {
      continue;
    }
    for (int j = 0; x; x >>= 1, j++) {
      if (x & 1) cnt[k + j]++;
    }
  }
  int ans = 0;
  for (int i = 0; i + 1 < M; i++) {
    sort(all(f[i]));
    reverse(all(f[i]));
    while (cnt[i]--) {
      if (f[i].empty()) {
        cout << -1 << endl;
        return 0;
      }
      // cerr << "use " << i << " " << f[i].back() << endl;
      ans += f[i].back();
      f[i].pop_back();
    }
    reverse(all(f[i]));
    upsolve(f[i], f[i + 1]);
    // if (f[i].size()) {
    //   cerr << "f " << i << " :: ";
    //   for (int x : f[i]) cerr << x << " ";
    //   cerr << endl;
    // }
  }
  cout << ans << endl;
}