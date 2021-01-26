#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n, m, k, ans[N], ind[N];
bool tag[N];
set<int> q, p;
vector<int> G[N];
vector<pair<int, int>> res;

int main() {
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1, u, v; i <= m; i++) {
    cin >> u >> v;
    ind[v]++;
    G[u].push_back(v);
  }
  for (int i = 1; i <= n; i++)
    if (!ind[i]) {
      p.insert(i);
    }
  for (int i = 1; i <= n; i++) {
    vector<int> v;
    int x = 0;
    while (p.size() > 1 && k) {
      x = *p.begin();
      p.erase(x), q.insert(x);
      --k, tag[x] = 1;
    }
    if (k && p.size() == 1 && q.size() && (*p.begin()) < (*q.rbegin())) {
      x = *p.begin();
      p.erase(x), q.insert(x);
      --k, tag[x] = 1;
    }
    if (!p.size()) {
      ans[i] = x = *q.rbegin();
      q.erase(x);
      res.push_back(make_pair(ans[i - 1], x));
    } else {
      ans[i] = x = *p.begin();
      p.erase(x);
    }
    for (auto v : G[x]) {
      ind[v]--;
      if (!ind[v]) {
        p.insert(v);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  cout << res.size() << endl;
  for (const auto &v : res) {
    cout << v.first << " " << v.second << '\n';
  }
}