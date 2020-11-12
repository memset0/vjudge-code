#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)

using namespace std;

typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef long long ll;

template <typename _T> inline void read(_T &f) {
  f = 0;
  _T fu = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') {
      fu = -1;
    }
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    f = (f << 3) + (f << 1) + (c & 15);
    c = getchar();
  }
  f *= fu;
}

template <typename T> void print(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x < 10)
    putchar(x + 48);
  else
    print(x / 10), putchar(x % 10 + 48);
}

template <typename T> void print(T x, char t) {
  print(x);
  putchar(t);
}

const int N = 6e5 + 5, INF = 0x7fffffff;

struct ele {
  int u, v;
} p[N];

int fa[N], ch[N][2], rev[N], minn[N], val[N], wz[N], st[N], f[N], ST[N][20],
    lg[N], n, m, q, len, cnt;

int isroot(int u) { return ch[fa[u]][0] != u && ch[fa[u]][1] != u; }
int get(int u) { return ch[fa[u]][1] == u; }

void update(int u) {
  minn[u] = val[u];
  wz[u] = u;
  if (minn[ch[u][0]] < minn[u] && ch[u][0])
    minn[u] = minn[ch[u][0]], wz[u] = wz[ch[u][0]];
  if (minn[ch[u][1]] < minn[u] && ch[u][1])
    minn[u] = minn[ch[u][1]], wz[u] = wz[ch[u][1]];
}

void pushdown(int u) {
  if (rev[u]) {
    swap(ch[u][0], ch[u][1]);
    rev[ch[u][0]] ^= 1;
    rev[ch[u][1]] ^= 1;
    rev[u] ^= 1;
  }
}

void rotate(int u) {
  int old = fa[u], oldd = fa[old], k = get(u);
  if (!isroot(old)) {
    ch[oldd][get(old)] = u;
  }
  fa[u] = oldd;
  ch[old][k] = ch[u][k ^ 1];
  fa[ch[u][k ^ 1]] = old;
  fa[old] = u;
  ch[u][k ^ 1] = old;
  update(old);
  update(u);
}

void splay(int u) {
  st[len = 1] = u;
  for (int i = u; !isroot(i); i = fa[i])
    st[++len] = fa[i];
  for (int i = len; i >= 1; i--)
    pushdown(st[i]);
  for (; !isroot(u); rotate(u))
    if (!isroot(fa[u]))
      rotate(get(u) == get(fa[u]) ? fa[u] : u);
}

void access(int u) {
  for (int i = 0; u; i = u, u = fa[u]) {
    splay(u);
    ch[u][1] = i;
    update(u);
  }
}

void makeroot(int u) {
  access(u);
  splay(u);
  rev[u] ^= 1;
}

void link(int u, int v) {
  makeroot(u);
  fa[u] = v;
}

void cut(int u, int v) {
  makeroot(u);
  access(v);
  splay(v);
  fa[u] = ch[v][0] = 0;
  update(v);
}

int query(int u, int v) {
  makeroot(u);
  access(v);
  splay(v);
  return wz[v];
}

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int QUERY(int l, int r) {
  int k = lg[r - l + 1];
  return max(ST[l][k], ST[r - (1 << k) + 1][k]);
}

int main() {
  int T;
  read(T);
  while (T--) {
    read(n);
    read(m);
    read(q);
    for (int i = 1; i <= n + m; i++)
      fa[i] = ch[i][0] = ch[i][1] = rev[i] = minn[i] = wz[i] = 0, ST[i][0] = 0;
    for (int i = 1; i <= n; i++)
      f[i] = i, val[i] = INF;
    for (int i = 1; i <= m; i++) {
      read(p[i].u);
      read(p[i].v);
    }
    for (int i = 1; i <= m; i++) {
      int x = p[i].u, y = p[i].v;
      if (find(x) != find(y)) {
        f[find(x)] = find(y);
        val[i + n] = i;
        link(i + n, x);
        link(i + n, y);
      } else {
        if (x == y)
          continue;
        int wz = query(x, y);
        ST[i][0] = wz - n;
        val[i + n] = i;
        cut(wz, p[wz - n].u);
        cut(wz, p[wz - n].v);
        link(i + n, x);
        link(i + n, y);
      }
    }
    for (int j = 1; j <= 19; j++) {
      for (int i = 1; i <= m - (1 << j) + 1; i++) {
        ST[i][j] = max(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
      }
    }
    lg[0] = -1;
    for (int i = 1; i <= m; i++)
      lg[i] = lg[i >> 1] + 1;
    int lastans = 0;
    for (int i = 1; i <= q; i++) {
      int l, r;
      read(l);
      read(r);
      l = (l ^ lastans) % m + 1;
      r = (r ^ lastans) % m + 1;
      if (l > r)
        swap(l, r);
      if (QUERY(l, r) >= l)
        printf("Yes\n"), lastans = 1;
      else
        printf("No\n"), lastans = 0;
    }
  }
  return 0;
}