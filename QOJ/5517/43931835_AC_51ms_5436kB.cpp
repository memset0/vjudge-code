#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 9;
int T, n, a[N];
long long ans;
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1);
    deque<int> q;
    for (int i = n; i >= 1; i--) {
      if (i & 1) {
        q.push_back(a[i]);
      } else {
        q.push_front(a[i]);
      }
    }
    vector<int> b(q.begin(), q.end());
    ans = 0;
    for (int i = 1; i < b.size(); i++) {
      ans += (long long)b[i] * b[i - 1];
    }
    ans += (long long)b.front() * b.back();
    cout << ans << endl;
  }
}