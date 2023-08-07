#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int n, m, ans, cnt[N];
bool tag[N], used[N];
vector<int> ins[N];
int main() {
#ifdef memset0
  freopen("A0.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  vector<int> a;
  cin >> n, a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> tmp = a;
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  m = tmp.size();
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
    ++cnt[a[i]];
  }
  // for (int i = 0; i < n; i++) cerr << a[i] << " \n"[i + 1 == n];
  vector<int> b;
  for (int l = 0, r; l < n; l = r + 1) {
    r = l;
    while (r + 1 < n && a[r] == a[r + 1]) ++r;
    if (cnt[a[l]] == r - l + 1) {
      tag[a[l]] = true;
    }
    b.push_back(a[l]);
  }
  n = b.size(), swap(a, b);
  for (int x = 0; x < n; x++)
    if (!used[x] && tag[a[x]]) {
      int l = x, r = x;
      if (l && !used[l - 1] && !tag[a[l - 1]] && a[l - 1] == a[l] - 1) --l;
      while (r + 1 < n && !used[r + 1] && tag[a[r + 1]] && a[r + 1] == a[r] + 1) ++r;
      if (r + 1 < n && !used[r + 1] && !tag[a[r + 1]] && a[r + 1] == a[r] + 1) ++r;
      for (int i = l; i <= r; i++) used[i] = true;
      // cerr << "find " << l << " " << r << " :: " << a[l] << " " << a[r] << endl;
      ++ans;
    }
  // for (int i = 0; i < n; i++) cerr << a[i] << " \n"[i + 1 == n];
  // for (int i = 0; i < n; i++) cerr << used[i] << " \n"[i + 1 == n];
  // for (int i = 0; i < n; i++) cerr << tag[a[i]] << " \n"[i + 1 == n];
  // cerr << "ans = " << ans << endl;
  for (int l = 0, r; l < n; l = r + 1) {
    r = l;
    if (used[l]) continue;
    while (r + 1 < n && !used[r + 1] && a[r + 1] == a[r] + 1) ++r;
    ans += r - l + 1;
    if (l < r) {
      // cerr << "find " << l << " " << r << " :: " << a[l] << " " << a[r] << endl;
      ins[a[l]].push_back(a[r] - 1);
    }
  }
  // cerr << "ans = " << ans << endl;
  priority_queue<int> q[2];
  for (int i = 1; i <= m; i++) {
    for (int x : ins[i]) {
      // cerr << "push " << i << " " << x << endl;
      q[x & 1].push(-x);
    }
    while (q[0].size() && -q[0].top() < i) q[0].pop();
    while (q[1].size() && -q[1].top() < i) q[1].pop();
    int t = -1;
    if (q[0].size() && q[1].size()) {
      t = -q[i & 1].top();
      q[i & 1].pop();
    } else if (q[0].size()) {
      t = -q[0].top();
      q[0].pop();
    } else if (q[1].size()) {
      t = -q[1].top();
      q[1].pop();
    }
    if (~t) {
      // cerr << "find " << i << " " << t << endl;
      if (i + 2 <= t) ins[i + 2].push_back(t);
      --ans;
    }
  }
  // cerr << "ans = " << ans << endl;
  cout << (ans - 1) << endl;
}