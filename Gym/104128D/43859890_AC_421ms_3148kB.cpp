#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int n, k, m, c, d, a[N], b[N], tr[(N << 1) + 100];
inline void upd(int k, int w) {
  // cerr << "upd " << k << " " << w << endl;
  for (; k <= n + m + 7; k += k & -k) tr[k] += w;
}
inline int ask(int k) {
  int ans = 0;
  // cerr << "ask " << k;
  for (; k; k -= k & -k) ans += tr[k];
  // cerr << " -> " << ans << endl;
  return ans;
}
inline bool check(long long cur) {
  // cerr << "check " << cur << endl;
  int need = k;
  for (int i = 1; i <= n; i++) {
    if (a[i] > cur) {
      need -= 1;
      b[i] = -1;
    } else if (a[i] + c + (long long)(m - 1) * d <= cur) {
      b[i] = -1;
    } else if (a[i] + c > cur) {
      b[i] = 0;
    } else {
      b[i] = (cur - a[i] - c) / d;
      if (a[i] + c + (long long)b[i] * d <= cur) ++b[i];
    }
  }
  // cerr << "need = " << need << endl;
  // for (int i = 1; i <= n; i++) cerr << b[i] << " \n"[i == n];
  if (need <= 0) {
    return true;
  }
  memset(tr, 0, (n + m + 10) << 2);
  multiset<int> st;
  for (int i = 1; i < m; i++) {
    if (b[i] != -1) {
      upd(i - b[i] + (m + 3), 1);
    }
  }
  for (int i = m; i <= n; i++) {
    if (b[i] != -1) {
      upd(i - b[i] + (m + 3), 1);
    }
    if (i - m >= 1 && b[i - m] != -1) {
      upd(i - m - b[i - m] + (m + 3), -1);
    }
    int cur = ask(n + m + 5) - ask(i - m + (m + 3));
    // cerr << i << " " << cur << endl;
    if (cur >= need) {
      return true;
    }
  }
  return false;
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k >> m >> c >> d;
  long long l = 1e18, r = -1e18, ans = -1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l = min<long long>(a[i], l);
    r = max<long long>(a[i] + c + (long long)(m - 1) * d, r);
  }
  l = max<long long>(l - 5, 0), r += 5;
  while (l <= r) {
    long long mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << (ans + 1) << endl;
}