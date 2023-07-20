#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 9;
int n, q, tot, cnt, cnt0, cnt1, a[N];
bool s[N];
inline void add(int k) {
  for (; k < N; k += k & -k) s[k] ^= 1;
}
inline void ask(int k, int &x) {
  for (; k; k -= k & -k) x ^= s[k];
}
inline void update(int k, int w) {
  if (a[k] == k) cnt += w;
  if ((k & 1) && (a[k] & 1)) cnt1 += w;
  if (!(k & 1) && !(a[k] & 1)) cnt0 += w;
}
int main() {
#ifdef memset0
  freopen("J.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  rep(i, 1, n) {
    cin >> a[i];
    update(i, 1);
  }
  per(i, n, 1) ask(a[i], tot), add(a[i]);
  for (int x, y, i = 1; i <= q; i++) {
    cin >> x >> y;
    update(x, -1), update(y, -1);
    swap(a[x], a[y]);
    update(x, 1), update(y, 1);
    tot ^= 1;
    if (cnt == n) {
      cout << -1 << endl;
    } else if (tot) {
      cout << n << endl;
    } else if (cnt0 == (n >> 1) && cnt1 == n - (n >> 1)) {
      cout << n - 2 << endl;
    } else {
      cout << n - 1 << endl;
    }
  }
}