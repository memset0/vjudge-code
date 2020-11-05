// =================================
//   author: memset0
//   date: 2019.07.08 10:19:05
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

const int N = 5e4 + 10;
int n, fa[N], tag[N];
std::vector<int> G[N];
std::bitset<N> ans[N], up[N];

void dfs1(int u) {
  ans[u][0] = tag[u];
  for (auto v : G[u]) if (v != fa[u]) {
    fa[v] = u, dfs1(v);
    ans[u] |= (ans[v] << 1);
  }
}

void dfs2(int u) {
  ans[u] |= up[u] << 1;
  std::bitset<N> sum;
  std::vector<int> son;
  for (auto v : G[u]) {
    if (v != fa[u]) son.push_back(v);
  }
  // if (!son.size()) return;
  // printf(">> %d\n", son.size());
  for (int i = 0; i < int(son.size()) - 1; i++) {
    // printf("> %d %d : %d %d\n", i, i < (son.size() - 1), son[i], son[i + 1]);
    sum |= ans[son[i]];
    up[son[i + 1]] |= sum << 1;
  }
  sum.reset();
  for (int i = int(son.size()) - 1; i > 0; i--) {
    // printf("> %d %d : %d %d\n", i, i > 0, son[i], son[i - 1]);
    sum |= ans[son[i]];
    up[son[i - 1]] |= sum << 1;
  }
  // printf("<<\n");
  up[u] <<= 1, up[u][0] = tag[u];
  for (auto v : son) {
    up[v] |= up[u], dfs2(v);
  }
}

void main() {
  read(n);
  for (int i = 1; i <= n; i++) read(tag[i]);
  for (int i = 1, u, v; i < n; i++) {
    read(u), read(v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs1(1), dfs2(1);
  for (int i = 1; i <= n; i++) {
    print(ans[i].count(), '\n');
  }
  // for (int i = 1; i <= n; i++) {
  //   printf("ans : ");
  //   for (int j = 0; j <= n; j++) putchar('0' + ans[i][j]);
  //   printf(" up : ");
  //   for (int j = 0; j <= n; j++) putchar('0' + up[i][j]);
  //   printf("\n");
  // }
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}
