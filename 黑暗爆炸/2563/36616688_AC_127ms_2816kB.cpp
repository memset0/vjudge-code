// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.08 13:14:31
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

const int N = 1e5 + 10;
ll ans;
int n, m, id[N], key[N], val[N];

inline bool cmp(int x, int y) {
  return key[x] > key[y];
}

void main() {
  read(n), read(m);
  for (int i = 1; i <= n; i++) {
    read(val[i]);
    id[i] = i;
    key[i] = val[i] << 1;
  }
  for (int i = 1, u, v, w; i <= m; i++) {
    read(u), read(v), read(w);
    key[u] += w, key[v] += w;
  }
  std::sort(id + 1, id + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    ans += (i & 1 ? 1 : -1) * key[id[i]];
  }
  print(ans >> 1, '\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}