#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<long long> a;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  a.resize(n + m);
  for (long long &x : a) {
    cin >> x;
  }
  vector<int> r(a.size(), -1);
  long long sum = 0;
  set<pair<long long, int>> s;
  for (int i = 0; i < a.size(); ++i) {
    long long x = a[i];
    if (x > 0) {
      sum += x;
      r[i] = 0;
    } else {
      x = -x;
      if (x <= sum) {
        s.insert(make_pair(x, i));
        sum -= x;
      } else if (!s.empty()) {
        auto it = s.end();
        --it;
        long long y = it->first;
        if (x < y) {
          s.erase(it);
          s.insert(make_pair(x, i));
          sum += y - x;
        }
      }
    }
  }
  for (const pair<long long, int> &a : s) {
    r[a.second] = 1;
  }
  for (int r : r) {
    cout << (r ? (r == 1 ? "approved" : "declined") : "resupplied") << '\n';
  }
}