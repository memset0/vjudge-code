#include <bits/stdc++.h>
using namespace std;

const int N = 1e8, M = 5e6, K = 2e4 + 9, mod = 1e9 + 7;

int n, m, jc1[N + 5], jc2[N + 5], po[M + 5], tot, prime[M / 10], inv[M + 5],
    pro[M + 5], pro_inv[M + 5];
int w[K], w1[K], g[K], G[K], G1[K], sqrtm, h1[K], h2[K];
bool not_prime[M + 5];

int fpow(int x, int y, int mod) {
  int ans = 1;
  while (y) {
    if (y & 1)
      ans = (long long)ans * x % mod;
    x = (long long)x * x % mod;
    y >>= 1;
  }
  return ans;
}

void pre() {
  po[1] = 1;
  for (int i = 2; i <= M; i++) {
    if (!not_prime[i])
      po[i] = fpow(i, n, mod - 1);
    for (int j = 1; j <= tot && i * prime[j] <= M; j++) {
      po[i * prime[j]] = (long long)po[i] * po[prime[j]] % (mod - 1);
      if (i % prime[j] == 0)
        break;
    }
  }
}

void init() {
  jc1[0] = jc2[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i <= N; i++)
    jc1[i] = (long long)jc1[i - 1] * i % mod,
    jc2[i] = (long long)jc2[i - 1] * jc1[i] % mod;
  ;
  for (int i = 2; i <= M; i++)
    inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
  for (int i = 0; i <= M; i++)
    pro[i] = pro_inv[i] = 1;
  for (int i = 2; i <= M; i++) {
    if (!not_prime[i]) {
      prime[++tot] = i;
      for (int j = 1; j <= M / i; j *= i)
        pro[i * j] = i, pro_inv[i * j] = inv[i];
    }
    pro[i] = (long long)pro[i - 1] * pro[i] % mod;
    pro_inv[i] = (long long)pro_inv[i - 1] * pro_inv[i] % mod;
    for (int j = 1; j <= tot && i * prime[j] <= M; j++) {
      not_prime[i * prime[j]] = 1;
      if (i % prime[j] == 0)
        break;
    }
  }
}

void pre_calc_g(int m) {
  int num = 0;
  for (int i = 1; i <= m; i = m / (m / i) + 1)
    w1[++num] = m / i;
  int t = fpow(m, n, (mod - 1));
  for (int i = num; i >= 1; i--) {
    int p = w1[i], id = p <= sqrtm ? h1[p] : h2[m / p];
    g[id] = (t + (mod - 1) - fpow(m - p, n, (mod - 1))) % (mod - 1);
    for (int j = 2, last; j <= p; j = last + 1) {
      last = p / (p / j);
      int q = p / j, id1 = q <= sqrtm ? h1[q] : h2[m / q];
      (g[id] += (mod - 1) - (long long)(last - j + 1) * g[id1] % (mod - 1)) %=
          (mod - 1);
    }
  }
}

int get_S(int m) {
  if (m <= M) {
    int ans = fpow(pro[m], po[m], mod);
    for (int i = 1, last; i <= m; i = last + 1) {
      last = m / (m / i);
      ans = (long long)ans *
            fpow((long long)pro_inv[last] * pro[i - 1] % mod, po[m - m / i],
                 mod) %
            mod;
    }
    return ans;
  }
  pre_calc_g(m);
  int ans = 1;
  for (int i = 1, last; i <= m; i = last + 1) {
    last = m / (m / i);
    int p = m / i, id = p <= sqrtm ? h1[p] : h2[m / p];
    ans = (long long)ans *
          fpow((long long)jc1[last] * fpow(jc1[i - 1], mod - 2, mod) % mod,
               g[id], mod) %
          mod;
  }
  return ans;
}

void pre_calc_G(int num) {
  for (int i = num; i >= 1; i--) {
    int p = w[i], id = p <= sqrtm ? h1[p] : h2[m / p];
    G1[id] = fpow(p, n, (mod - 1));
    G[id] = 1;
    for (int j = 2, last; j <= p; j = last + 1) {
      last = p / (p / j);
      int q = p / j, id1 = q <= sqrtm ? h1[q] : h2[m / q];
      (G1[id] += (mod - 1) - (long long)(last - j + 1) * G1[id1] % (mod - 1)) %=
          (mod - 1);
      G[id] = (long long)G[id] * fpow(G[id1], last - j + 1, mod) % mod;
      G[id] = (long long)G[id] *
              fpow((long long)jc1[last] * fpow(jc1[j - 1], mod - 2, mod) % mod,
                   G1[id1], mod) %
              mod;
    }
    G[id] = (long long)get_S(p) * fpow(G[id], mod - 2, mod) % mod;
  }
}

int get_pro(int l, int r) {
  int ans =
      (long long)fpow(jc1[r], r, mod) * fpow(jc2[r - 1], mod - 2, mod) % mod;
  if (l <= 1)
    return ans;
  int w = (long long)fpow(jc1[l - 1], l - 1, mod) *
          fpow(jc2[l - 2], mod - 2, mod) % mod;
  return (long long)ans * fpow(w, mod - 2, mod) % mod;
}

int solve() {
  pre();
  int num = 0;
  sqrtm = sqrt(m);
  for (int i = 1, last; i <= m; i = last + 1) {
    last = m / (m / i);
    w[++num] = m / i;
    if (m / i <= sqrtm)
      h1[m / i] = num;
    else
      h2[last] = num;
  }
  pre_calc_G(num);
  int ans = 1;
  for (int i = 1, last; i <= m; i = last + 1) {
    last = m / (m / i);
    int p = m / i, id = p <= sqrtm ? h1[p] : h2[m / p];
    ans = (long long)ans *
          fpow(G[id], (long long)(last - i + 1) * (last + i) / 2 % (mod - 1),
               mod) %
          mod;
    ans = (long long)ans * fpow(get_pro(i, last), G1[id], mod) % mod;
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  init();
  while (T--) {
    scanf("%d%d", &n, &m);
    printf("%d\n", solve());
  }
  return 0;
}