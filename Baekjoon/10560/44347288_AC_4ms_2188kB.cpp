#include <bits/stdc++.h>
using lf = long double;
using namespace std;
const int N = 100;
int T, n, m, a, b, c, d, r, tot;
lf mat[N][N], sol[N];
map<int, int> pos;
inline lf sqr(lf x) { return x * x; }
inline lf myabs(lf x) { return x > 0 ? x : -x; }
void init(int n, lf *vec) {
  fill(vec, vec + N, 0);
  if (n > 0) {
    vec[pos[n]] += r;
    vec[pos[m - n * 2]] -= d + r * sqr((lf)n / m);
    vec[tot + 1] = c;
  } else {
    vec[pos[n]] += r;
    vec[pos[-m - n * 2]] -= b + r * sqr((lf)n / m);
    vec[tot + 1] = a;
  }
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    tot = 0, pos.clear();
    cin >> n >> m >> a >> b >> c >> d >> r;
    int u = n;
    while (pos.find(u) == pos.end()) {
      pos[u] = ++tot;
      if (u > 0) {
        u = m - u * 2;
      } else {
        u = -m - u * 2;
      }
    }
    for (const auto &it : pos) {
      // cerr << it.first << " -> " << it.second << endl;
      init(it.first, mat[it.second]);
    }
    // cerr << "tot=" << tot << endl;
    // for (int i = 1; i <= tot; i++)
    //   for (int j = 1; j <= tot + 1; j++) fprintf(stderr, "%.3lf%c", (double)mat[i][j], " \n"[j == tot + 1]);
    // cerr << endl;
    for (int i = 1; i <= tot; i++) {
      int ii = i;
      for (int j = i + 1; j <= tot; j++)
        if (myabs(mat[j][i]) > myabs(mat[ii][i])) {
          ii = j;
        }
      if (ii != i) {
        for (int j = i; j <= tot + 1; j++) swap(mat[i][j], mat[ii][j]);
      }
      for (int j = 1; j <= tot; j++)
        if (j != i)
          for (int k = tot + 1; k >= i; k--) {
            mat[j][k] -= mat[j][i] / mat[i][i] * mat[i][k];
          }
    }
    // for (int i = 1; i <= tot; i++)
    //   for (int j = 1; j <= tot + 1; j++) fprintf(stderr, "%.3lf%c", (double)mat[i][j], " \n"[j == tot + 1]);
    // cerr << endl;
    for (int i = 1; i <= tot; i++) sol[i] = mat[i][tot + 1] / mat[i][i];
    printf("%.12lf\n", (double)sol[pos[n]]);
  }
}