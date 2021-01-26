#include <bits/stdc++.h>
using namespace std;

const int N = 510;
vector<int> w[N];
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    w[i].resize(m + 1);
    w[i][0] = 0;
    for (int j = 1; j <= m; j++)
      scanf("%d", &w[i][j]);
    sort(w[i].begin(), w[i].end());
    w[i].push_back(0x3f3f3f3f);
  }
  for (int i = 1; i <= n; i++) {
    vector<pair<int,int>> res;
    for (int j = 1; j <= n; j++)
      if (j != i) {
        int a = 0, b = 0;
        long long cura = 0, curb = 0;
        int curx = 0, nx;
        auto check = [&](long long X, long long Y) -> void { // interval < 0
          if (Y == 0) {
            if (X >= 0)
              return;
            if (curx < nx) {
              res.push_back(make_pair(curx, 1));
              res.push_back(make_pair(nx, -1));
            }
          } else if (Y < 0) {
            long long Zropit = -X / Y;
            while (X + Zropit * Y >= 0)
              ++Zropit;
            long long _l = max(1ll * curx, 1ll * curx + Zropit);
            int _r = nx - 1;
            if (_l <= _r) {
              res.push_back(make_pair(_l, 1));
              res.push_back(make_pair(_r + 1, -1));
            }
          } else {
            long long Zropit = -X / Y;
            while (X + Zropit * Y >= 0)
              --Zropit;
            int _l = curx;
            long long _r = min(1ll * (nx - 1), 1ll * Zropit + curx);
            if (_l <= _r) {
              res.push_back(make_pair(_l, 1));
              res.push_back(make_pair(_r + 1, -1));
            }
          }
        };
        while (a < m || b < m) {
          if (w[i][a + 1] < w[j][b + 1]) {
            nx = w[i][a + 1];
            long long X = cura - curb;
            int Y = (m - a) - (m - b);
            check(X, Y);
            cura += 1ll * (m - a) * (nx - curx);
            curb += 1ll * (m - b) * (nx - curx);
            curx = nx;
            ++a;
          } else {
            nx = w[j][b + 1];
            long long X = cura - curb;
            int Y = (m - a) - (m - b);
            check(X, Y);
            cura += 1ll * (m - a) * (nx - curx);
            curb += 1ll * (m - b) * (nx - curx);
            curx = nx;
            ++b;
          }
        }
        if (cura < curb) {
          res.push_back(make_pair(curx, 1));
        }
      }
    sort(res.begin(), res.end());
    int ans = n, cur = n;
    for (auto v : res) {
      cur -= v.second;
      ans = min(ans, cur);
    }
    printf("%d\n", ans);
  }
}