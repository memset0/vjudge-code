// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.19 12:56:21
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

const int N = 3e5 + 10;
int n, m, fa[N], ch[N][2], rev[N], val[N], sum[N];

inline bool getson(int x) { return ch[fa[x]][1] == x; }
inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
inline void maintain(int x) { sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]]; }
inline void pushup(int x) { rev[x] ^= 1, std::swap(ch[x][0], ch[x][1]); }
inline void pushdown(int x) { if (rev[x]) pushup(ch[x][0]), pushup(ch[x][1]), rev[x] = 0; }

inline void rotate(int x) {
  if (!x || !fa[x]) return;
  int f = fa[x], ff = fa[f], fs = getson(x), ffs = getson(f), y = ch[x][fs ^ 1];
  if (!isroot(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
  fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
}

void clear(int x) { if (!isroot(x)) clear(fa[x]); pushdown(x); }
void splay(int x) {
  clear(x);
  for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x])
    if (!isroot(f)) rotate(getson(x) == getson(f) ? f : x);
}

void access(int x) {
  for (int y = 0; x; y = x, x = fa[x])
    splay(x), ch[x][1] = y, maintain(x);
}

void mroot(int x) { access(x), splay(x), pushup(x); }
void split(int x, int y) { mroot(x), access(y), splay(y); }
int getroot(int x) { access(x), splay(x); while (ch[x][0]) x = ch[x][0]; return x; }

void link(int x, int y) {
  if (getroot(x) != getroot(y)) {
    mroot(x), fa[x] = y;
  }
}

void cut(int x, int y) {
  if (getroot(x) == getroot(y)) {
    split(x, y);
    if (fa[x] == y && ch[y][0] == x && !ch[x][1])
      fa[x] = ch[y][0] = 0, maintain(y);
  }
}

void main() {
  read(n), read(m);
  for (int i = 1; i <= n; i++) read(val[i]);
  for (int i = 1, x, y, op; i <= m; i++) {
    read(op), read(x), read(y);
    if (!op) split(x, y), print(sum[y], '\n');
    else if (op == 1) link(x, y);
    else if (op == 2) cut(x, y);
    else mroot(x), val[x] = y, maintain(x);
  }
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}