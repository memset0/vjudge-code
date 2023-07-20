#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9, M = N << 3, mod = 1e9 + 7;
int l, t, n, m, tot, ans, a[N], f[M], g[M], mu[N << 1], pri[N];
bool tag[N << 1], flg[N << 1];
vector<int> fac[N << 1];
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

namespace NTT {
const int mod = 998244353;
int k, lim = 1, rev[M], w[M];
inline int dec(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
inline int inc(int x, int y) { return (x += y) >= mod ? x - mod : x; }
inline int fpow(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) s = 1ll * s * a % mod;
  return s;
}
void dft(int *a) {
  for (int i = 0; i < lim; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int len = 1; len < lim; len <<= 1)
    for (int i = 0; i < lim; i += (len << 1))
      for (int j = 0; j < len; j++) {
        int x = a[i + j], y = 1ll * a[i + j + len] * w[j + len] % mod;
        a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
      }
}
void idft(int *a) {
  reverse(a + 1, a + lim), dft(a);
  int inv_lim = fpow(lim, mod - 2);
  for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv_lim % mod;
}
void init(int len) {
  while (lim <= len) lim <<= 1, ++k;
  for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  for (int wn, len = 1; len < lim; len <<= 1) {
    wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
    for (int i = 1; i < len; i++) w[i + len] = 1ll * w[i + len - 1] * wn % mod;
  }
}
} // namespace NTT

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> l >> t >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);
  l <<= 1, m = a[n] + a[n - 1];

  // for (int i = 1; i <= n; i++)
  //   for (int j = i + 1; j <= n; j++) {
  //     tag[a[j] - a[i]] = tag[a[i] + a[j]] = 1;
  //   }
  // for (int i = 1; i <= m; i++) cerr << tag[i] << " \n"[i == m];
  // memset(tag, 0, sizeof(tag));

  NTT::init((a[n] << 1) + 5);
  for (int i = 1; i <= n; i++) f[a[i]] = g[a[n] - a[i]] = 1;
  NTT::dft(f), NTT::dft(g);
  for (int i = 0; i < NTT::lim; i++) {
    g[i] = 1ll * f[i] * g[i] % NTT::mod;
    f[i] = 1ll * f[i] * f[i] % NTT::mod;
  }
  NTT::idft(f), NTT::idft(g);
  for (int i = 1; i <= n; i++) f[a[i] << 1] = (f[a[i] << 1] + NTT::mod - 1) % NTT::mod;
  for (int i = 1; i <= a[n] + a[n - 1]; i++) {
    if (f[i]) tag[i] = true;
  }
  for (int i = 1; i <= a[n] - a[1]; i++) {
    if (g[a[n] + i]) tag[i] = true;
  }
  // for (int i = 1; i <= m; i++) cerr << tag[i] << " \n"[i == m];

  for (int i = 1; i <= m; i++) {
    fac[i].push_back(i);
    for (int j = (i << 1); j <= m; j += i) {
      tag[i] |= tag[j];
      fac[j].push_back(i);
    }
  }

  // for (int x = 1; x <= m; x++)
  //   if (tag[x]) {
  //     for (int k = 1; k <= (long long)x * t / l; k++)
  //       if (gcd(x, k) == 1) {
  //         ans++;
  //       }
  //   }
  // cout << ans << endl;
  // ans = 0;

  mu[1] = 1;
  for (int i = 2; i <= m; ++i) {
    if (!flg[i]) pri[++tot] = i, mu[i] = -1;
    for (int j = 1; j <= tot && i * pri[j] <= m; ++j) {
      flg[i * pri[j]] = 1;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        break;
      }
      mu[i * pri[j]] = -mu[i];
    }
  }

  for (int i = 1; i <= m; i++) {
    if (tag[i])
      for (int j = 0; j < fac[i].size(); j++) {
        ans = (ans + 1ll * (((long long)i * t / l) / fac[i][j]) % mod * mu[fac[i][j]]) % mod;
      }
  }
  ans = (ans + mod) % mod;
  cout << ans << endl;
}