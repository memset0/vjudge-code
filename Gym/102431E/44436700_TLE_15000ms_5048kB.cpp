#include <bits/stdc++.h>
using namespace std;

struct item {
  int x, y;
  double weight;
  int index;
  inline bool operator<(const item &other) const { return weight > other.weight; }
};

void solve() {
  int n, m;
  double l;
  cin >> n >> m >> l;

  vector<bool> vis(n);
  double limit = m * m * (1 - l) / (1 + l);
  double weight = m;

  vector<item> a;
  for (int i = 0; i < n; i++) {
    int x, y;
    double v;
    cin >> x >> y >> v;
    a.push_back({x, y, v, i + 1});
  }
  sort(a.begin(), a.end());

  function<pair<int, int>(int, int)> locate = [&](int x, int y) { return make_pair(int(x / weight), int(y / weight)); };

  function<long long(const pair<int, int> &)> trans = [&](const pair<int, int> &p) { return (long long)p.first * 100000000 + p.second; };

  map<long long, vector<int>> map;
  for (int i = 0, x, y; i < n; i++) {
    auto pair = locate(a[i].x, a[i].y);
    auto it = map.find(trans(pair));
    if (it == map.end()) {
      map[trans(pair)] = vector<int>{i};
    } else {
      it->second.push_back(i);
    }
  }

  // for (int i = 0, x, y; i < n; i++) {
  //   tie(x, y) = locate(a[i].x, a[i].y);
  //   printf("%d : %d %d\n", a[i].index, x, y);
  // }

  function<bool(item &, item &)> cross = [&](item &i, item &j) {
    int l = abs(i.x - j.x);
    int r = abs(i.y - j.y);
    long long s = (long long)m * (l + r) - (long long)l * r;
    return s <= limit;
  };

  vector<int> ans;
  for (int i = 0; i < n; i++)
    if (!vis[i]) {
      int x, y, cur = i;
      vis[i] = 1;
      tie(x, y) = locate(a[i].x, a[i].y);
      ans.push_back(a[i].index);

      for (int deltax = -1; deltax <= 1; deltax++)
        for (int deltay = -1; deltay <= 1; deltay++) {
          auto pair = make_pair(x + deltax, y + deltay);
          auto it = map.find(trans(pair));
          if (it == map.end()) continue;

          vector<int> &vec = it->second;
          vector<int> now;
          for (int x : vec) {
            if (!vis[x] && cross(a[cur], a[x])) {
              // printf("check %d %d\n", a[cur].index,
              // a[x].index);
              vis[x] = 1;
            } else {
              now.push_back(x);
            }
          }
          swap(vec, now);
        }
    }

  sort(ans.begin(), ans.end());
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " \n"[i + 1 == ans.size()];
  }
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
  // freopen("1.out", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  for (int task = 1; task <= T; task++) {
    cout << "Case #" << task << ": ";
    solve();
  }
}