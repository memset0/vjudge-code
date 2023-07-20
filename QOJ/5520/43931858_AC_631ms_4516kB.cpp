#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 509;
int T, n, cnt, a[N][N], d[N];
bool fl;
string s;
void bfs(int s) {
  static int l, r, q[N];
  static bool vis[N];
  fill(vis + 1, vis + n + 1, false);
  l = r = 1, q[1] = s, d[s] = 0, vis[s] = true;
  while (l <= r) {
    int u = q[l++];
    rep(v, 1, n) if (a[u][v] && !vis[v]) {
      vis[v] = true;
      d[v] = d[u] ^ 1;
      q[++r] = v;
    }
  }
  rep(i, 1, n) if (!vis[i]) fl = false;
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n, cnt = 0;
    rep(i, 1, n) {
      fill(a[i] + 1, a[i] + n + 1, 0);
      cin >> s;
      rep(j, 1, n) if (s[j - 1] == '1') { a[i][j] = 1, ++cnt; }
    }
    fl = true;
    rep(s, 1, n) {
      bfs(s);
      rep(i, 1, n) if (d[i] != a[s][i]) { fl = false; }
      if (!fl) break;
    }
    if (fl) {
      cout << "YES" << endl;
      cout << (cnt >> 1) << endl;
      rep(i, 1, n) rep(j, i + 1, n) if (a[i][j]) cout << i << " " << j << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}