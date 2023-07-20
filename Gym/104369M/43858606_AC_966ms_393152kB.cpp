#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 9;
int T, L, n, s[N];
long long f[N][N], g[N][N];
struct Node {
  int x, y;
  friend inline Node operator-(const Node &a, const Node &b) { return {a.x - b.x, a.y - b.y}; }
  friend inline bool operator<(const Node &a, const Node &b) { return (long long)a.x * b.y < (long long)a.y * b.x; }
  friend inline bool operator==(const Node &a, const Node &b) { return (long long)a.x * b.y == (long long)a.y * b.x; }
  friend inline bool operator<=(const Node &a, const Node &b) { return (long long)a.x * b.y <= (long long)a.y * b.x; }
  friend inline long long operator*(const Node &a, const Node &b) { return (long long)a.x * b.y - (long long)a.y * b.x; }
} a[N << 1], c[N];
struct Vector {
  Node n;
  int k;
  friend inline bool operator<(const Vector &a, const Vector &b) { return a.n == b.n ? a.k < b.k : a.n < b.n; }
} b[N << 2];
constexpr long long dis(const Node &x, const Node &y) { return (long long)(x.x - y.x) * (x.x - y.x) + (long long)(x.y - y.y) * (x.y - y.y); }
inline long long get_ans(int i, int j) {
  if (i > j) swap(i, j);
  // cerr << "find " << i << " " << j << " :: " << f[i][j] << " " << g[i][j] << " " << f[1][i] << " " << f[j][n] << endl;
  return f[i][j] + max(g[i][j], max(f[1][i], f[j][n]));
}
inline void add(int k) {
  for (; k < L; k += k & -k) s[k]++;
}
inline int ask(int k) {
  int ans = 0;
  for (; k; k -= k & -k) ans += s[k];
  return ans;
}
int main() {
#ifdef memset0
  freopen("M.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    long long ans = 4e18;
    cin >> n, L = n + 5;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y;
      a[i + n] = a[i];
    }
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++) {
        f[i][j] = g[i][j] = dis(a[i], a[j]);
        // cerr << "dis " << i << " " << j << " " << f[i][j] << endl;
      }
    for (int len = 2; len <= n; len++)
      for (int l = 1, r = len; r <= n; l++, r++) {
        f[l][r] = max(f[l][r], f[l + 1][r]);
      }
    for (int len = 2; len <= n; len++)
      for (int l = 1, r = len; r <= n; l++, r++) {
        f[l][r] = max(f[l][r], f[l][r - 1]);
      }
    for (int len = n - 1; len >= 1; len--)
      for (int l = 2, r = len + 1; r <= n; l++, r++) {
        // fprintf(stderr, "g[%d][%d] < %d %d\n", l, r, g[l][r], g[l - 1][r]);
        g[l][r] = max(g[l][r], g[l - 1][r]);
      }
    for (int len = n - 1; len >= 1; len--)
      for (int l = 1, r = len; r < n; l++, r++) {
        g[l][r] = max(g[l][r], g[l][r + 1]);
      }

    // __int128 all, sum;
    long long all, sum;
    for (int i = 1; i <= n; i++) {
      all = sum = 0;
      for (int j = i + 2; j <= i + n - 1; j++) {
        all += (a[j - 1] - a[i]) * (a[j] - a[i]);
      }
      for (int j = i + 2; j <= i + n - 2; j++) {
        sum += (a[j - 1] - a[i]) * (a[j] - a[i]);
        // cerr << j << " :: " << sum << " " << (all - sum) << endl;
        if (sum > 0 && all - sum > 0) {
          ans = min(ans, get_ans(i, j > n ? j - n : j));
        }
      }
    }

    // for (int i = 1; i <= n; i++) {
    //   int j = i + 2;
    //   while (j <= n && (a[j] - a[i]) == (a[i + 1] - a[i])) j++;
    //   Node mn = a[i + 1] - a[i], mx = a[i + 1] - a[i];
    //   for (; j <= n; j++) {
    //     mn = min(mn, a[j] - a[i]);
    //     mx = max(mx, a[j] - a[i]);
    //     if (((a[j] - a[i]) <= mn && mx <= (a[i] - a[j])) || ((a[i] - a[j]) <= mn && mx <= (a[j] - a[i]))) {
    //       if (i == 1 && j == n) continue;
    //       // cerr << "find " << i << " " << j << " :: " << get_ans(i, j) << " :: " << f[i][j] << " " << g[i][j] << " " << f[1][i] << " " << f[j][n] << endl;
    //       ans = min(ans, get_ans(i, j));
    //     }
    //   }
    // }

    // for (int i = 1; i <= n; i++) {
    //   int jmin = i + 2;
    //   while (jmin <= n && (a[jmin] - a[i]) == (a[i + 1] - a[i])) jmin++;
    //   if (jmin > n) break;
    //   int m = 0;
    //   for (int j = 1; j <= n; j++)
    //     if (i != j) {
    //       b[++m] = {a[j] - a[i], j};
    //       b[++m] = {a[i] - a[j], -j};
    //     }
    //   sort(b + 1, b + m + 1);
    //   for (int i = 1; i <= m; i++) b[i + m] = b[i];
    //   m <<= 1;
    //   for (int _ = 0; _ < 2; _++) {
    //     if (_) reverse(b + 1, b + m + 1);
    //     cerr << "!!! " << i << " " << _ << endl;
    //     for (int i = 1; i < n; i++) cerr << b[i].n.x << " " << b[i].n.y << " : " << b[i].k << endl;
    //     memset(s, 0, L << 2);
    //     add(i);
    //     for (int k = 1; k < n; k++) {
    //       int j = b[k].k;
    //       add(j);
    //       if (k + 1 < n && b[k].n == b[k + 1].n) {
    //         continue;
    //       }
    //       if (j > i + 1 && (i != 1 || j != n) && !((a[i + 1] - a[i]) == b[j].n) && ask(j) - ask(i - 1) == j - i + 1) {
    //         cerr << "find " << i << " " << j << " " << get_ans(i, j) << endl;
    //         ans = min(ans, get_ans(i, j));
    //       }
    //     }
    //   }
    // }

    cout << ans << endl;
  }
}