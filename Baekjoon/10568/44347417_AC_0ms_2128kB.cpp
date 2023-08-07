#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 100;
int T, n, m, q;
double f[N][N];
string s, s1, s2;
struct point {
  string name;
  int x, y, z;
} a[N];
map<string, int> id;
constexpr double dis(const point &a, const point &b) { return sqrt((long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y) + (long long)(a.z - b.z) * (a.z - b.z)); }
int main() {
#ifdef memset0
  freopen("L.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  for (int t = 1; t <= T; t++) {
    id.clear();
    cout << "Case " << t << ":" << '\n';
    cin >> n;
    for (int i = 1; i <= n; i++) {
      fill(f[i] + 1, f[i] + n + 1, 0);
      cin >> a[i].name >> a[i].x >> a[i].y >> a[i].z;
      id[a[i].name] = i;
    }
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++) {
        f[i][j] = f[j][i] = dis(a[i], a[j]);
      }
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> s1 >> s2;
      int u = id[s1], v = id[s2];
      f[u][v] = 0;
    }
    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    cin >> q;
    for (int i = 1; i <= q; i++) {
      cin >> s1 >> s2;
      int u = id[s1], v = id[s2];
      int ans = f[u][v] + 0.5;
      cout << "The distance from " << s1 << " to " << s2 << " is " << ans << " parsecs.\n";
    }
  }
}