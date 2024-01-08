// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.12 21:07:47
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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

const int N = 1e6 + 10, K = 150;
int n, m, a[N], b[N], p[N];
ll sum[N];

void main() {
  srand(20040725);
  read(n), read(m);
  for (int i = m + 1; i <= n; i++) read(a[i]), read(b[i]);
  for (int _K = K; _K--; ) {
    for (int i = 1; i <= m; i++) p[i] = rand();
    for (int i = m + 1; i <= n; i++) {
      p[i] = std::min(p[a[i]], p[b[i]]);
    }
    for (int i = 1; i <= n; i++) {
      sum[i] += p[i];
    }
    // print(p, 1, n);
  }
  for (int i = m + 1; i <= n; i++) {
    // std::cout << int(RAND_MAX / (sum[i] / double(K)) - 0.5) << std::endl;
    print(int(RAND_MAX / (sum[i] / double(K)) - 0.5), '\n');
  }
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}