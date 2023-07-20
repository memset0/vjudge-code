#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
int T, n, d;
vector<int> a;

inline long long myabs(long long x) { return x < 0 ? -x : x; }
inline long long calc(const vector<int> &a) {
  long long sum = 0;
  for (int i = 1; i < a.size(); i++) {
    sum += myabs((long long)a[i] - a[i - 1] - d);
  }
  return sum;
}

vector<int> solve() {
  vector<int> ans;
  sort(a.begin(), a.end());
  if (d >= 0) {
    return a;
  }
  d *= -1;
  reverse(a.begin(), a.end());

  // auto check = [&](int x, vector<int> a) {
  //   if (x > a[0] + d) return false;
  //   for (int i = 1; i < a.size(); i++)
  //     if (a[i - 1] > a[i] + d) return false;
  //   return true;
  // };

  auto interact = [&](vector<int> a) {
    // printf("interact %d\n", (int)a.size());
    ans.push_back(a[0]);
    a.erase(a.begin());
    while (a.size() > 1) {
      bool fl = false;
      int l = 0, r = (int)a.size() - 2, mid, res;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] >= ans.back() - d) {
          res = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      for (int i = res; i >= 0; i--) {
        if (i == 0 || (a[i] <= a[0] + d && a[i - 1] <= a[i + 1] + d)) {
          ans.push_back(a[i]);
          a.erase(a.begin() + i);
          fl = true;
          break;
        }
      }
      assert(fl);
    }
    if (a.size()) {
      ans.push_back(a[0]);
    }
  };

  int pre = 0;
  rep(i, 0, (int)a.size() - 2) {
    // fprintf(stderr, "%d : %d(%d)\n", a[i], a[i + 1], a[i + 1] + d);
    if (a[i] > a[i + 1] + d) {
      interact(vector<int>(a.begin() + pre, a.begin() + i + 1));
      pre = i + 1;
    }
  }
  interact(vector<int>(a.begin() + pre, a.end()));
  return ans;
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> d, a.resize(n);
    rep(i, 0, n - 1) { cin >> a[i]; }
    vector<int> ans = solve();
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i + 1 == n];
  }
}