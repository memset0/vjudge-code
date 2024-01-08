#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N = 1e5 + 9;
int n, m, q, a[N], b[N];
long long x;
set<long long> st;
long long myabs(long long x) { return x < 0 ? -x : x; }
long long query() {
  long long ans = LLONG_MAX;
  auto it = st.lower_bound(x);
  if (it != st.end()) { ans = min(ans, myabs(*it - x)); }
  if (it != st.begin()) {
    --it;
    ans = min(ans, myabs(*it - x));
  }
  return ans;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    x += (i & 1 ? 1 : -1) * a[i];
  }
  for (int i = 1; i <= m; i++) { cin >> b[i]; }
  long long y = 0;
  for (int i = 1; i <= n; i++) { y += (i & 1 ? 1 : -1) * b[i]; }
  // cerr << "y = " << y << endl;
  st.insert(y);
  for (int i = n + 1; i <= m; i++) {
    y -= b[i - n];
    y *= -1;
    y += b[i] * (n & 1 ? 1 : -1);
    st.insert(y);
  }
  // for (auto t : st) cerr << "! " << t << endl;
  // cerr << "x = " << x << endl;
  cout << query() << endl;
  for (int l, r, v, i = 1; i <= q; i++) {
    cin >> l >> r >> v;
    if ((r - l + 1) % 2) {
      if (l & 1) {
        x += v;
      } else {
        x -= v;
      }
    }
    cout << query() << endl;
  }
}