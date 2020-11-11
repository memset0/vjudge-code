#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 5;
const int maxm = 1e6 + 5;
typedef long long ll;
ll ans, sum[maxn], n, prime[maxn], phi[maxn], num;
bool isp[maxn];

inline void sieve(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; ++i)
    isp[i] = true;
  for (int i = 2; i <= n; ++i) {
    if (isp[i])
      prime[++num] = i, phi[i] = i - 1;
    for (int j = 1; j <= num; ++j) {
      if (prime[j] * i > n)
        break;
      isp[prime[j] * i] = false;
      if (i % prime[j])
        phi[i * prime[j]] = phi[i] * (prime[j] - 1);
      else {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    sum[i] = sum[i - 1] + phi[i];
}

int main() {
  sieve(maxn - 4);
  while (~scanf("%lld", &n) && n) {
    ll ans = 0;
    for (int i = 1, j; i <= n; i = j + 1) {
      j = n / (n / i), ans += (sum[j] - sum[i - 1]) * (n / i) * (n / i);
    }
    printf("%lld\n", (ans - n * (n + 1) / 2) / 2);
  }
  return 0;
}