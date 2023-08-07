#include <bits/stdc++.h>
using ull = unsigned long long;
using namespace std;
const int N = 1e5 + 9;
int n, used[N];
vector<int> p0, px[100];
vector<pair<int, int>> ans;
struct node {
  ull v;
  int i;
  inline bool operator<(const node &rhs) const { return v == rhs.v ? i < rhs.i : v < rhs.v; }
} a[N];
map<ull, vector<int>> mp;
constexpr int cntl(ull x) {
  int l = 0;
  while (x) {
    if (x & 1) {
      if (x == 1) {
        return l;
      } else {
        return -1;
      }
    }
    x >>= 1;
    ++l;
  }
  return -1;
}
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].v;
    a[i].i = i;
    auto it = mp.find(a[i].v);
    if (it == mp.end()) {
      mp[a[i].v] = {};
    }
    mp[a[i].v].push_back(a[i].i);
  }
  sort(a + 1, a + n + 1);
  for (int i = n; i >= 1; i--)
    if (a[i].v) {
      if (used[a[i].i]) {
        continue;
      }
      assert(mp[a[i].v].back() == a[i].i);
      mp[a[i].v].pop_back();
      ull x = 1;
      while (x <= a[i].v) x <<= 1;
      x -= a[i].v;
      // cerr << ">> " << a[i].v << " " << x << endl;
      if (a[i].v && x != a[i].v) {
        auto it = mp.find(x);
        if (it == mp.end() || it->second.empty()) {
          continue;
        }
        ans.emplace_back(a[i].i, it->second.back());
        used[a[i].i] = true;
        used[it->second.back()] = true;
        it->second.pop_back();
      }
    }
  for (int i = 1; i <= n; i++)
    if (!used[a[i].i]) {
      // cerr << "notused: " << a[i].i << " " << a[i].v << endl;
      if (a[i].v == 0) {
        p0.push_back(a[i].i);
      }
      int x = cntl(a[i].v);
      px[x].push_back(a[i].i);
    }
  for (int i = 0; i < 100; i++)
    if (p0.size() && (px[i].size() & 1)) {
      ans.emplace_back(p0.back(), px[i].back());
      p0.pop_back();
      px[i].pop_back();
    }
  for (int i = 0; i < 100; i++)
    while (p0.size() && px[i].size()) {
      ans.emplace_back(p0.back(), px[i].back());
      p0.pop_back();
      px[i].pop_back();
    }
  for (int i = 0; i < 100; i++)
    while (px[i].size() > 1) {
      int tmp = px[i].back();
      px[i].pop_back();
      ans.emplace_back(tmp, px[i].back());
      px[i].pop_back();
    }
  cout << ans.size() << endl;
  for (const auto &it : ans) {
    cout << it.first << " " << it.second << endl;
  }
}