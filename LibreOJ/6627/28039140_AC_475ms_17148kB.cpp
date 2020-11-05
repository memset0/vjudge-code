// =================================
//   author: memset0
//   date: 2019.07.11 08:55:22
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int (i) = (l), __lim = (r); (i) <= __lim; (i)++)
#define for_each(i, a) for (size_t i = 0, __lim = a.size(); i < __lim; ++i)
namespace ringo {

template <class T> inline void read(T &x) {
  x = 0; char c = getchar(); bool f = 0;
  while (!isdigit(c)) f ^= c == '-', c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  if (f) x = -x;
}
template <class T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) print(x / 10);
  putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline void print(T a, int l, int r, std::string s = "") {
  if (s != "") std::cout << s << ": ";
  for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e6 + 10;
bool vis[N];
ll n, sum, pcnt, ans[N];
int lim, pri[N], t[N], mu[N];

void main() {
  read(n), lim = sqrt(n);
  for (int i = 1; i <= lim; i++) {
    t[i] = i * 2 / (1 + sqrt(5));
  }
  mu[1] = 1;
  for (int i = 2; i <= lim; i++) {
    if (!vis[i]) {
      mu[i] = -1;
      pri[++pcnt] = i;
    }
    for (int j = 1; j <= pcnt && i * pri[j] <= lim; j++) {
      vis[i * pri[j]] = 1;
      if (i % pri[j]) mu[i * pri[j]] = mu[i] * -1;
      else { mu[i * pri[j]] = 0; break; }
    }
  }
  // for (int i = 1; i <= lim; i++) print(mu[i], " \n"[i == lim]);
  for (int i = 1; i <= lim; i++)
    for (int j = i; j <= lim; j += i) {
      ans[j] += 1ll * mu[i] * (j / i - t[j] / i);
    }
  for (int i = 1; i <= lim; i++) {
    sum += (n / i / i) * ans[i];
  }
  print(sum, '\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}
