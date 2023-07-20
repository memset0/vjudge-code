#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1048576 + 9, M = 1e5 + 9;
int x, n, len = 1, k, tot, mu[N], cnt[N], pri[N];
bool flg[N];

constexpr long long gcd(long long a, long long b) {
  while (b != 0) {
    long long tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

struct query {
  long long l, r, p, ans;
  int id;

  void F(long long t) {
    if (t <= 0) return;
    // rep(k, 0, t) { cerr << k<< " "<< ((long long)k * x ^ x) % x << endl; }
    long long p = t / len;
    ans += p * cnt[len - 1] + cnt[t % len];
    // cerr << "F " << t << " :: " << p * cnt[x - 1] << " " << cnt[t % x] << endl;
  }

  void G() {
    if (r <= 0) return;
    p = r / len;
    l = p * len;
    F(l - 1);
    r = r % len;
  }
} q[M << 1];

void getMu() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!flg[i]) pri[++tot] = i, mu[i] = -1;
    for (int j = 1; j <= tot && i * pri[j] < N; ++j) {
      flg[i * pri[j]] = 1;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        break;
      }
      mu[i * pri[j]] = -mu[i];
    }
  }
}

int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> x >> n;
  while (len <= x) len <<= 1, ++k;
  rep(i, 0, len - 1) cnt[i] = gcd(x, (long long)i * x ^ x) == 1;
  rep(i, 1, len) cnt[i] += cnt[i - 1];
  rep(i, 1, n) {
    cin >> q[i].l >> q[i].r;
    // int cnt = 0;
    // rep(k, q[i].l, q[i].r) {
    //   if (gcd(x, (long long)k * x ^ x) == 1) {
    //     cnt++;
    //   }
    // }
    // cerr << i << " ==> " << cnt << endl;
    q[i + n].r = q[i].l - 1, q[i].l = 0;
  }
  n <<= 1;
  rep(i, 1, n) {
    q[i].id = i;
    q[i].G();
  }
  // rep(i, 1, n) fprintf(stderr, "q[%d] : r=%lld ans=%lld\n", i, q[i].r, q[i].ans);
  getMu();
  sort(q + 1, q + n + 1, [](const query &a, const query &b) { return a.r < b.r; });
  vector<pair<int, int>> f;
  rep(i, 1, x) if (x % i == 0) { f.emplace_back(i, 0); }
  for (int k = 1, r = 0; r < len; r++) {
    int u = ((long long)r * x ^ x) % x;
    // fprintf(stderr, "r=%d u=%d x=%d rx=%d rx^x=%d\n", r, u, x, r * x, r * x ^ x);
    for (auto &[i, v] : f) {
      if (u % i == 0) {
        // fprintf(stderr, "v[%d] += 1\n", i);
        v++;
      }
    }
    while (k <= n && q[k].r < r) k++;
    while (k <= n && q[k].r == r) {
      for (auto &[i, v] : f) {
        q[k].ans += mu[i] * v;
        // fprintf(stderr, "q[%d].ans += %d * %d : %d\n", q[k].id, mu[i], v, i);
      }
      k++;
    }
  }
  sort(q + 1, q + n + 1, [](const query &a, const query &b) { return a.id < b.id; });
  // rep(i, 1, n) fprintf(stderr, "q[%d] : r=%lld ans=%lld\n", i, q[i].r, q[i].ans);
  n >>= 1;
  rep(i, 1, n) { cout << (q[i].ans - q[i + n].ans) << endl; }
}