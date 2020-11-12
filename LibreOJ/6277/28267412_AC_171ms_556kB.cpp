#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
int n, opt, l, r, c, a[N], t[N << 2];

inline int lowbit(int x) { return x & -x; }

inline void add(int i, int x) {
  for (; i <= n; i += lowbit(i)) {
    t[i] += x;
  }
  return;
}

inline int query(int i) {
  int res = 0;
  for (; i; i -= lowbit(i)) {
    res += t[i];
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    add(i, a[i] - a[i - 1]);
  }
  for (int i = 1; i <= n; i++) {
    cin >> opt >> l >> r >> c;
    if (!opt) {
      add(l, c);
      add(r + 1, -c);
    } else {
      cout << query(r) << endl;
    }
  }
}