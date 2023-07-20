#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 1e6 + 9;
int T, n, d;
vector<int> a, p;

inline long long myabs(long long x) { return x < 0 ? -x : x; }
inline long long calc(const vector<int> &a) {
  long long sum = 0;
  for (int i = 1; i < a.size(); i++) {
    sum += myabs((long long)a[i] - a[i - 1] - d);
  }
  return sum;
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> d, a.resize(n), p.resize(n);
    rep(i, 0, n - 1) {
      cin >> a[i];
      p[i] = i;
    }
    long long ansv = calc(a);
    vector<int> ans = a;
    do {
      vector<int> cur(n);
      for (int i = 0; i < n; i++) cur[i] = a[p[i]];
      long long curv = calc(cur);
      if (curv < ansv) {
        ansv = curv;
        ans = cur;
      } else if (curv == ansv && cur < ans) {
        ans = cur;
      }
      // for (int i = 0; i < n; i++) cout << cur[i] << ' ';
      // cout << "-> " << curv << endl;
    } while (next_permutation(p.begin(), p.end()));
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i + 1 == n];
    // cerr << "! " << calc(ans) << endl;

    // vector<int> pre = a;
    // sort(pre.begin(), pre.end());
    // if (d < 0) reverse(pre.begin(), pre.end());
    // assert(calc(ans) == calc(pre));
  }
}