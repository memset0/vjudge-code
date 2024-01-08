#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
int n, m;
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  long long s = 0;
  for (int i = 1; i <= n; i++) {
    s += i;
    // cerr << i << ": " << s << " " << (s - (n - i)) << " " << m << endl;
    if (s - (n - i) == m) {
      cout << (n - i) << endl;
      return 0;
    }
  }
}