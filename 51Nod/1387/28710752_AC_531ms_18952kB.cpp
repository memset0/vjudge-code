#include <bits/stdc++.h>
#define ll long long
#define int long long
#define pb push_back
#define SZ 666666
using namespace std;
int mod;
ll w[2][SZ], G, fac[SZ], rfac[SZ];
inline ll qp(ll a, ll b) {
  ll ans = 1;
  a %= mod;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}
inline ll org_root() {
  static ll yss[2333];
  int yyn = 0;
  ll xp = mod - 1;
  for (ll i = 2; i * i <= xp; i++) {
    if (xp % i)
      continue;
    yss[++yyn] = i;
    while (xp % i == 0)
      xp /= i;
  }
  if (xp != 1)
    yss[++yyn] = xp;
  ll ans = 1;
  while (1) {
    bool ok = 1;
    for (int i = 1; i <= yyn; i++)
      if (qp(ans, (mod - 1) / yss[i]) == 1) {
        ok = 0;
        break;
      }
    if (ok)
      return ans;
    ++ans;
  }
}
int K;
ll rv;
inline void fftinit(int n) {
  for (K = 1; K < n; K <<= 1)
    ;
  w[0][0] = w[0][K] = 1;
  ll g = qp(G, (mod - 1) / K);
  for (int i = 1; i < K; i++)
    w[0][i] = w[0][i - 1] * g % mod;
  for (int i = 0; i <= K; i++)
    w[1][i] = w[0][K - i];
  rv = qp(K, mod - 2);
}
inline void fft(int *x, int v) {
  for (int i = 0; i < K; i++)
    (x[i] < 0) ? (x[i] += mod) : 0;
  for (int i = 0, j = 0; i < K; i++) {
    if (i > j)
      swap(x[i], x[j]);
    for (int l = K >> 1; (j ^= l) < l; l >>= 1)
      ;
  }
  for (int i = 2; i <= K; i <<= 1)
    for (int l = 0; l < i >> 1; l++) {
      register int W = w[v][K / i * l], *p = x + l + (i >> 1), *q = x + l, t;
      for (register int j = 0; j < K; j += i) {
        p[j] = (q[j] - (t = (ll)p[j] * W % mod) < 0) ? (q[j] - t + mod)
                                                     : (q[j] - t);
        q[j] = (q[j] >= mod - t) ? (q[j] - mod + t) : (q[j] + t);
      }
    }
  if (!v)
    return;
  for (int i = 0; i < K; i++)
    x[i] = x[i] * rv % mod;
}
ll ff[SZ];
int A[SZ], B[SZ], C[SZ];
inline void calc(int *h, int *o, int d, int k) {
  int off = k - d - 1;
  ff[0] = 1;
  for (int j = 1; j <= d + d + 3; ++j) {
    int s = (j + off) % mod;
    if (s < 0)
      s += mod;
    ff[j] = ff[j - 1] * (ll)s % mod;
  }
  fftinit(d + d + d + 5);
  memset(A, 0, sizeof(A[0]) * K);
  memset(B, 0, sizeof(B[0]) * K);
  for (int i = 0; i <= d; ++i) {
    A[i] = h[i] * (ll)rfac[i] % mod * rfac[d - i] % mod;
    if ((d - i) & 1)
      A[i] = (mod - A[i]) % mod;
  }
  for (int i = 0; i <= d + d; ++i)
    B[i] = qp(i - d + k, mod - 2);
  if (K <= (1 << 16)) {
    fft(A, 0);
    fft(B, 0);
    for (int i = 0; i < K; ++i)
      C[i] = (ll)A[i] * B[i] % mod;
    fft(C, 1);
  } else //这里可能是错的，注意
  {
    fftinit(K >> 1);
    fft(A, 0);
    fft(A + K, 0);
    fft(B, 0);
    fft(B + K, 0);
    for (int i = 0; i < K; ++i)
      C[i + K] = (A[i] * (ll)B[i + K] + (ll)B[i] * A[i + K]) % mod;
    for (int i = 0; i < K; ++i)
      C[i] = A[i] * (ll)B[i] % mod;
    fft(C, 1);
    fft(C + K, 1);
  }
  for (int i = 0; i <= d; ++i) {
    // i+k-d...i+k
    o[i] = C[i + d] * ff[i + k - off] % mod *
           qp(ff[i + k - d - off - 1], mod - 2) % mod;
    (o[i] < 0) ? (o[i] += mod) : 0;
  }
}
int V;
ll rV;
int aa[SZ], bb[SZ];
inline void work(int x, vector<int> &v) {
  if (x == 0) {
    v.pb(1);
    return;
  }
  if (x & 1) {
    work(x - 1, v);
    for (int i = 0; i < v.size(); ++i)
      v[i] = (ll)v[i] * (i * V + x) % mod;
    ll p = 1;
    for (int i = 1; i <= x; ++i)
      p = p * (V * x + i) % mod;
    v.pb(p);
    return;
  }
  int d = x >> 1;
  work(d, v);
  for (int i = 0; i <= d; ++i)
    aa[i] = v[i];
  calc(aa, aa + d + 1, d, d + 1);
  calc(aa, bb, d + d, d * rV % mod);
  v.resize(x + 1);
  for (int i = 0; i <= x; ++i)
    v[i] = aa[i] * (ll)bb[i] % mod;
}
inline ll gfac_(int x) {
  V = sqrt(x);
  rV = qp(V, mod - 2);
  vector<int> tmp;
  work(V, tmp);
  ll ans = 1;
  for (int i = 0; i < V; ++i)
    ans = ans * tmp[i] % mod;
  for (int i = V * V + 1; i <= x; ++i)
    ans = ans * i % mod;
  return ans;
}
inline ll gfac(int x) {
  if (x >= mod)
    return 0;
  if (x > mod - x - 1) {
    int s = qp(gfac(mod - x - 1), mod - 2);
    if (x % 2)
      ;
    else
      s = -s;
    return s;
  }
  return gfac_(x);
}
signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  int n;
  cin >> n >> mod;
  fac[0] = 1;
  for (int i = 1; i < SZ; ++i)
    fac[i] = fac[i - 1] * i % mod;
  rfac[SZ - 1] = qp(fac[SZ - 1], mod - 2);
  for (int i = SZ - 1; i >= 1; --i)
    rfac[i - 1] = rfac[i] * i % mod;
  G = org_root();
  int ans = (gfac(n) % mod + mod) % mod;
  if (n & 1) {
    ans = ans & 1 ? (ans + mod) >> 1 : ans >> 1;
  }
  cout << ans << endl;
}/////