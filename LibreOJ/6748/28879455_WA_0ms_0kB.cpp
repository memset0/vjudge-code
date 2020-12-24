#include <bits/stdc++.h>
using namespace std;
const int N = 310;
inline void nosolution() {
  cout << "No" << endl;
  exit(0);
}
int lim[N];
int s[N][N], n, m;

inline void solve(int l, int r) {
  if (l > r)
    return;
  if (l == 1) {
    int beg = 1;
    for (int i = r; i >= l; i--) {
      beg = beg == 2 ? 1 : 2;
      for (int j = beg, t = 1; t <= lim[i]; j += 2, t++)
        s[j][i] = 1;
    }
  } else if ((r - l + 1) % 2 || r == m) {
    int beg = 1;
    for (int i = l; i <= r; i++) {
      beg = beg == 2 ? 1 : 2;
      for (int j = beg, t = 1; t <= lim[i]; j += 2, t++)
        s[j][i] = 1;
    }
  } else {
    int beg = 1;
    for (int i = l; i <= r; i++) {
      beg = beg == 2 ? 1 : 2;
      int last = n;
      if (beg == 1)
        last = n - 1;
      bool flag = 0;
      for (int tmp = 0; tmp <= lim[i]; tmp++) {
        int f = 1;
        int L = beg, R = last;
        for (int j = 1; j <= tmp; j++, L += 2)
          if (s[L][i - 1])
            f = 0;
        for (int j = 1; j <= lim[i] - tmp; j++, R -= 2)
          if (s[R][i - 1])
            f = 0;
        if (f) {
          flag = 1;
          L = beg, R = last;
          for (int j = 1; j <= tmp; j++, L += 2)
            s[L][i] = 1;
          for (int j = 1; j <= lim[i] - tmp; j++, R -= 2)
            s[R][i] = 1;
          break;
        }
      }
      if (!flag)
        nosolution();
    }
    for (int i = 1; i <= n; i++)
      if (s[i][r] && s[i][r + 1])
        nosolution();
  }
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &lim[i]);
    if (lim[i] > (n + 1) / 2) {
      nosolution();
    }
  }
  if (n % 2 == 0) {
    solve(1, n);
  } else {
    int last = 0;
    for (int i = 1; i <= m; i++) {
      if (lim[i] == (n + 1) / 2) {
        for (int j = 1; j <= n; j += 2)
          s[j][i] = 1;
        solve(last + 1, i - 1);
        if (last != 0 && last + 1 == i)
          nosolution();
        last = i;
      }
    }
    if (last != m)
      solve(last + 1, m);
  }
  cout << "Yes" << endl;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      assert(0 <= s[i][j] && s[i][j] <= 1);
      assert(i == n || !s[i][j] || !s[i + 1][j]);
      assert(j == m || !s[i][j] || !s[i][j + 1]);
    }
  for (int i = 1; i <= m; i++) {
    int tmp = 0;
    for (int j = 1; j <= n; j++)
      tmp += s[j][i];
    assert(tmp == lim[i]);
  }
}