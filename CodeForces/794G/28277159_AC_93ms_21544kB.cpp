#include <cstdio>
#include <cstring>
#include <iostream>
#define abs(_o) ((_o < 0) ? -(_o) : _o)
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy {
char a[400001], b[400001];
inline int gcd(int a, int b) {
  while (b) {
    int r = a % b;
    a = b;
    b = r;
  }
  return (a);
}
ll dk[400001], jc[700001], jcny[700001];
inline ll cnm(int n, int m) {
  if (n < m)
    return (0);
  if (m < 0)
    return (0);
  ll cjr = jc[n];
  cjr *= jcny[m];
  cjr %= p;
  cjr *= jcny[n - m];
  return (cjr % p);
}
inline ll mi(int a, int b) {
  ll ans = 1, tmp = a;
  while (b) {
    if (b & 1)
      ans = (ans * tmp) % p;
    tmp = (tmp * tmp) % p;
    b >>= 1;
  }
  return (ans);
}
int n;
ll df[400001];
int miu[400001];
inline ll f(int da, int db) {
  if (da == db && !da)
    return (df[n]);
  if (da >= 0 && db >= 0)
    return (0);
  if (da <= 0 && db <= 0)
    return (0);
  da = abs(da), db = abs(db);
  if (da == db)
    return (dk[n + 1] - 2);
  int g = gcd(da, db);
  return (dk[n / max(da / g, db / g) + 1] - 2);
}
int prime[400001];
unsigned char bv[400001];
inline void prim(int n) {
  miu[1] = 1;
  int ptr = 0;
  dk[1] = 2;
  for (register int i = 2; i <= n; i++) {
    if (!bv[i]) {
      prime[ptr] = i;
      ptr++;
      miu[i] = p - 1;
    }
    for (register int j = 0; j < ptr; j++) {
      int cjr = i * prime[j];
      if (cjr > n)
        break;
      bv[cjr] = 1;
      if (i % prime[j] == 0)
        break;
      miu[cjr] = (p - miu[i]) % p;
    }
    dk[i] = (dk[i - 1] << 1) % p;
  }
  for (register int i = 1; i <= n; i++) {
    for (register int j = i; j <= n; j += i)
      df[j] = (df[j] + dk[i] * miu[j / i]) % p;
  }
  dk[n + 1] = (dk[n] << 1) % p;
  for (register int i = 1; i <= n; i++) {
    ll cjr = n / i;
    cjr *= (n / i);
    cjr %= p;
    cjr *= df[i];
    df[i] = (df[i - 1] + cjr) % p;
  }
}
void ywymain() {
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  int A = strlen(a + 1), B = strlen(b + 1);
  cin >> n;
  jc[0] = 1;
  for (register int i = 1; i <= max(A, B) * 2; i++)
    jc[i] = (jc[i - 1] * i) % p;
  jcny[max(A, B) * 2] = mi(jc[max(A, B) * 2], p - 2);
  for (register int i = max(A, B) * 2 - 1; i >= 0; i--)
    jcny[i] = (jcny[i + 1] * (i + 1)) % p;
  prim(n);
  int P = 0, Q = 0, dA = 0, dB = 0;
  for (register int i = 1; i <= A; i++)
    P += (a[i] == '?'), dA += (a[i] == 'A'), dB += (a[i] == 'B');
  for (register int i = 1; i <= B; i++)
    Q += (b[i] == '?'), dA -= (b[i] == 'A'), dB -= (b[i] == 'B');
  ll ans = 0;
  for (register int i = -max(P, Q); i <= max(P, Q); i++) {
    if (!cnm(P + Q, P - i))
      continue;
    ans = (ans + cnm(P + Q, P - i) * f(dA + i, dB + P - Q - i)) % p;
  }
  if (A == B) {
    for (register int i = 1; i <= A; i++)
      if (a[i] != b[i] && a[i] != '?' && b[i] != '?')
        goto s;
    ll tot = 1;
    for (register int i = 1; i <= A; i++)
      if (a[i] == '?' && b[i] == '?')
        tot = (tot << 1) % p;
    ans -= df[n] * tot;
    ans %= p;
    ans += p;
    ans %= p;
    ans += (((dk[n + 1] - 2) * (dk[n + 1] - 2ll)) % p) * tot;
    ans %= p;
  }
s:;
  cout << ans << endl;
}
} // namespace ywy
int main() {
  ywy::ywymain();
  return (0);
}