#include <bits/stdc++.h>
using namespace std;

const int MAXN1 = 2e5 + 50, MAXN2 = 2100, MOD = 1e9 + 7, S = 2050;
long long N, ans;
long long a[MAXN1], b[MAXN1];
long long mul[MAXN2 << 2], invv[MAXN2 << 2];
long long f[MAXN2 << 1][MAXN2 << 1];

inline long long qpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1)
      res = (res * a) % MOD;
    b >>= 1;
    a = (a * a) % MOD;
  }
  return res;
}

inline long long inv(long long x) { return qpow(x, MOD - 2) % MOD; }

inline long long C(long long n, long long m) {
  return mul[n] * invv[n - m] % MOD * invv[m] % MOD;
}

int main() {
  memset(f, 0, sizeof(f));
  scanf("%lld", &N);
  for (long long i = 1; i <= N; i++)
    scanf("%lld%lld", &a[i], &b[i]), f[S - a[i]][S - b[i]]++;
  mul[0] = 1, invv[0] = inv(mul[0]);
  for (long long i = 1; i <= 8000; i++)
    mul[i] = mul[i - 1] * i % MOD, invv[i] = inv(mul[i]);
  for (long long i = 1; i <= S * 2; i++)
    for (long long j = 1; j <= S * 2; j++)
      f[i][j] = (f[i][j] + (f[i - 1][j] + f[i][j - 1]) % MOD) % MOD;
  for (long long i = 1; i <= N; i++) {
    ans = (ans + f[S + a[i]][S + b[i]]) % MOD;
    ans = (ans - C(2 * a[i] + 2 * b[i], 2 * a[i])) % MOD;
    ans = (ans + MOD) % MOD;
  }
  ans = (ans * 500000004) % MOD;
  printf("%lld\n", ans);
}