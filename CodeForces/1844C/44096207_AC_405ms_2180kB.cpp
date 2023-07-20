#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 2e5 + 9;
int T, n, a[N];

long long solve(const vector<int> &a) {
  if (!a.size()) return -1e9 - 9;
  long long ans = a[0], sum = 0;
  for (int i = 0; i < a.size(); i++) {
    ans = max(ans, (long long)a[i]);
    if (a[i] > 0) {
      sum += a[i];
      ans = max(ans, sum);
    }
  }
  return ans;
}

int main() {
#ifdef memset0
  freopen("C.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n;
    vector<int> x, y;
    rep(i, 1, n) {
      cin >> a[i];
      if (i & 1) {
        x.pb(a[i]);
      } else {
        y.pb(a[i]);
      }
    }
    cout << max(solve(x), solve(y)) << endl;
  }
}