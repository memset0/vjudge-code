#include <bits/stdc++.h>
using namespace std;
int T, x, y, a, b;

pair<int, int> solve() {
  // cerr << "solve " << x << " " << y << " " << a << " " << b << endl;
  if (x == y && a > x && b > y) {
    return make_pair(x + 1, y + 1);
  }

  int m = sqrt(y) + 5;
  vector<pair<vector<int>, int>> xx;
  for (int i = 2; i <= m && i <= a; i++) {
    vector<int> v;
    for (int u = x; u; u /= i) {
      v.push_back(u % i);
    }
    xx.emplace_back(v, i);
  }
  sort(xx.begin(), xx.end());
  for (int i = 2; i <= m && i <= b; i++) {
    vector<int> v;
    for (int u = y; u; u /= i) {
      v.push_back(u % i);
    }
    auto it = lower_bound(xx.begin(), xx.end(), make_pair(v, -1));
    if (it != xx.end() && it->first == v) {
      // for (int t : it->first) cerr << t << " ";
      // cerr << endl;
      // for (int t : v) cerr << t << " ";
      // cerr << endl;
      // cerr << "!! " << it->second << " " << i << endl;
      return make_pair(it->second, i);
    }
  }
  // cerr << "!!" << endl;

  pair<int, int> tmpans;
  auto check = [&](int i) -> bool {
    int d = (y - x) / i;
    int m1 = (x) / (i + 1) + 1;
    int m2 = (y) / (i + 1) + 1;
    if (m2 - m1 < d) m2 = m1 + d;
    if (m2 - m1 > d) m1 = m2 - d;
    if (m1 == 1) {
      ++m1, ++m2;
    }
    if (m1 <= i) {
      m2 += i - m1 + 1;
      m1 += i - m1 + 1;
    }
    if (m1 <= a && m2 <= b && (long long)i * m1 <= x) {
      // fprintf(stderr, "check %d -> %d %d\n", i, m1, m2);
      tmpans = make_pair(m1, m2);
      return true;
    } else {
      return false;
    }
  };

  if (a > m || b > m) {
    for (int i = 1; i * i <= (y - x); i++)
      if ((y - x) % i == 0) {
        if (check(i)) return tmpans;
        if (i * i != y - x && check((y - x) / i)) return tmpans;
      }
  }

  return make_pair(0, 0);
}

int main() {
#ifdef memset0
  freopen("J.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> x >> y >> a >> b;
    bool rev = false;
    if (x > y) {
      rev = true;
      swap(x, y), swap(a, b);
    }
    auto ans = solve();
    if (rev) {
      swap(ans.first, ans.second);
    }
    if (ans.first && ans.second) {
      cout << "YES" << endl;
      cout << ans.first << " " << ans.second << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}