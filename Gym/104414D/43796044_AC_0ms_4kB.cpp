#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 9;
int n, t, x, y, a[N];
bool tag[N];
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  cin.tie(0), ios::sync_with_stdio(0);
  cin >> n >> t;
  tag[1] = true;
  while (t--) {
    cin >> x >> y;
    if (x == -1 || y == -1) {
      continue;
    }
    tag[x] |= tag[y];
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++)
    if (tag[i]) {
      ans.push_back(i);
    }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " \n"[i + 1 == ans.size()];
  }
}