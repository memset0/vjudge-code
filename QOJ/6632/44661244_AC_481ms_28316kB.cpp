#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), i##z = (b); i <= i##z; i++)
#define ROF(i, a, b) for (int i = (a), i##z = (b); i >= i##z; i--)
#define REP(i, u) for (int i = hd[u], v; v = to[i], i; i = nxt[i])
#define temT template <typename T>
#define temT12 template <typename T1, typename T2>
using namespace std;
typedef long long ll;
#define int ll
const int N = int(2e6) + 10, inf = int(1e16) + 7;

int T, n, m, K;
int a[N], f[N];

void Min(int &x, int y) { x = min(x, y); }

int get_low(int cur, int last) { return last / (cur + 1) + 1; }

bool check(int mid) {
  ll tot = 0;
  FOR(i, 1, n / 2 + 1) if (a[i] > mid) {
    tot += f[get_low(mid, a[i])];
    if (tot > K) return false;
  }
  return true;
}

signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif

  for (cin >> T; T--;) {
    cin >> n >> m >> K;
    FOR(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1);
    FOR(i, 1, m) cin >> f[i];
    f[1] = 0;
    FOR(i, m + 1, m * 2) f[i] = inf;
    m *= 2;
    FOR(i, 1, m) FOR(j, 1, m / i) Min(f[i * j], f[i] + f[j]);
    ROF(i, m - 1, 1) Min(f[i], f[i + 1]);
    FOR(i, 1, m) FOR(j, 1, i) if (i * j > m) {
      Min(f[m], f[i] + f[j]);
      break;
    }
    ROF(i, m - 1, 1) Min(f[i], f[i + 1]);

    int l = 0, r = a[n / 2 + 1], mid, ans = -1;
    while (l <= r) {
      mid = (l + r) / 2;
      if (check(mid)) {
        ans = mid, r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    // assert(ans != -1);
    cout << ans << "\n";
  }
  return 0;
}