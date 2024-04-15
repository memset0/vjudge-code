// Author: 23forever
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
#define rg register
const int MAXN = 200000;
const int MAXM = 200000;
const int MAXL = 20;
const int MAXC = 6e6;
using namespace std;

struct FastIO {
  char c[MAXC + 5], *now_read, *now_write;

  FastIO() : now_read(c - 1), now_write(c - 1) {
   	fread(c, 1, MAXC, stdin);
  }
  inline int read() {
    while (*++now_read < '0' || *now_read > '9') continue;
    register int x = *now_read ^ 48;
    while (*++now_read >= '0' && *now_read <= '9') {
      x = (x << 1) + (x << 3) + (*now_read ^ 48);
    }
    return x;
  }
  inline void write(int x) {
    static char st[20]; static int top;
    if (x < 0) *++now_write = '-', x *= -1;
    while (st[++top] = x % 10 ^ 48, x /= 10) continue;
    while (*++now_write = st[top], --top) continue;
    *++now_write = '\n';
  }
  void out() {
    fwrite(c, 1, now_write - c, stdout);
  }
} IO;

#define read IO.read
#define write IO.write

namespace tree {

int tot, head[MAXN + 5], rt;
int in[MAXN + 5], out[MAXN + 5], idx, depth[MAXN + 5];

struct Edge {
  int to, nxt;
  Edge() {}
  Edge(int _to, int _nxt) : to(_to), nxt(_nxt) {}
} edge[MAXM + 5];

void addEdge(int u, int v) {
  edge[tot] = Edge(v, head[u]), head[u] = tot++;
  edge[tot] = Edge(u, head[v]), head[v] = tot++;
}
void init() {
  rt = 1;
  tot = 0, memset(head, -1, sizeof(head));
}

namespace rmq {

int st[MAXN + 5][MAXL], lg2[MAXN + 5], dep[MAXN + 5], bel[MAXN + 5];
int cnt, dfn[MAXN + 5];

void dfs(int u, int fa) {
  in[u] = ++idx;
  dfn[u] = ++cnt;
  dep[cnt] = depth[u], bel[cnt] = u;

  for (int i = head[u]; ~i; i = edge[i].nxt) {
    int v = edge[i].to;
    if (v == fa) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
    bel[++cnt] = u, dep[cnt] = depth[u];
  }

  out[u] = idx;
}

void init() {
  dfs(rt, 0);
  for (int i = 1; i <= cnt; ++i) {
    lg2[i] = lg2[i - 1] + ((1 << lg2[i - 1]) == i);
  }
  for (int i = 1; i <= cnt; ++i) st[i][0] = i;

  for (int j = 1; (1 << j) <= cnt; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= cnt; ++i) {
      int x = st[i][j - 1], y = st[i + (1 << (j - 1))][j - 1];
      st[i][j] = dep[x] <= dep[y] ? x : y;
    }
  }
}

inline int query(int u, int v) {
  int l = dfn[u], r = dfn[v];
  if (l > r) swap(l, r);
  int k = lg2[r - l + 1] - 1;
  int x = st[l][k], y = st[r - (1 << k) + 1][k];
  return dep[x] <= dep[y] ? bel[x] : bel[y];
}

}

inline bool isInSubtree(int v, int u) {
  //is v in the subtree of u?
  return in[v] >= in[u] && in[v] <= out[u]; 
}

inline int LCA(int u, int v) {
  return rmq::query(u, v);
}

}

struct Chain {
  int u, v, lca;
#define phi Chain(0, 0, -1);
  Chain() {}
  Chain(int _u, int _v, int _lca) : u(_u), v(_v), lca(_lca) {}
  
  bool isIncluded(int x) {
    using namespace tree;
    if (!lca) return true; // ???
    if (lca > 0) return isInSubtree(x, lca) && (isInSubtree(u, x) || isInSubtree(v, x));
    return false;
  }

  Chain operator + (Chain rhs) const {
    if (!lca) return rhs;
    if (!rhs.lca) return *this;
    if (lca == -1 || rhs.lca == -1) return phi; //!!
    // if (*this == phi && rhs == phi) return phi;

    using namespace tree;
    Chain ret = *this;
    if (depth[ret.lca] < depth[rhs.lca]) swap(ret, rhs);
    if (!rhs.isIncluded(ret.lca)) return phi;

    int lu = LCA(ret.u, rhs.u), lv = LCA(ret.v, rhs.v);
    ret.u = depth[lu] > depth[ret.lca] ? lu : ret.lca;
    ret.v = depth[lv] > depth[ret.lca] ? lv : ret.lca;
    return ret;
  } 
};

struct Edge {
  Chain c; int w, id;
  Edge() {}
  Edge(int _u, int _v, int _w, int _id) {
    int _lca = tree::LCA(_u, _v);
    c = Chain(_u, _v, _lca);
    w = _w, id = _id;
  }
  bool operator < (const Edge &rhs) const {
    return w < rhs.w;
  }
} e[MAXM + 5];

int tot;

struct SegmentTree {
  Chain s[MAXN * 4 + 5]; int sz;
#define lson p << 1 
#define rson p << 1 | 1
  SegmentTree() {}

  inline void upd(int p) {
    s[p] = s[lson] + s[rson];
  }
  void modify(int p, int l, int r, int x, Chain c) {
    if (l == r) {
      s[p] = c;
      return;
    }

    int mid = (l + r) >> 1;
    if (x <= mid) {
      modify(lson, l, mid, x, c);
    } else {
      modify(rson, mid + 1, r, x, c);
    }
    upd(p);
  }

  inline void insert(int x, Chain c) {
    ++sz;
    modify(1, 1, tot, x, c);
  }
  inline void del(int x){
    --sz;
    modify(1, 1, tot, x, Chain(0, 0, 0));
  }

  int getAns(int p, int l, int r, int u) {
    if (l == r) return e[l].w;

    int mid = (l + r) >> 1;
    if (s[rson].isIncluded(u)) {
      return getAns(lson, l, mid, u);
    } else {
      return getAns(rson, mid + 1, r, u);
    }
  }
  int query(int u) {
    if (!sz) return -1;
    if (s[1].isIncluded(u)) {
      return -1;
    } else {
      return getAns(1, 1, tot, u); 
    }
  }

#undef lson
#undef rson
} Sgt;

int n, m;

void init() {
  n = read(), m = read();
  tree::init();

  for (rg int i = 1; i < n; ++i) {
    int u = read(), v = read();
    tree::addEdge(u, v);
  }
  tree::rmq::init();
}

struct Node {
  int opt, t, u, id;
} q[MAXM + 5];

int main() {
  init();

  for (rg int i = 1; i <= m; ++i) {
    q[i].opt = read();

    if (q[i].opt == 0) {
      int u = read(), v = read(), w = read();
      e[++tot] = Edge(u, v, w, i);
    } else if(q[i].opt == 1) {
      q[i].t = read();
    } else {
      q[i].u = read();
    }
  }

  sort(e + 1, e + 1 + tot);
  for (rg int i = 1; i <= tot; ++i) {
    q[e[i].id].id = i;
  }

  for (rg int i = 1; i <= m; ++i) {
    int opt = q[i].opt;
    if (!opt) {
      Sgt.insert(q[i].id, e[q[i].id].c);
    } else if (opt == 1) {
      Sgt.del(q[q[i].t].id);
    } else {
      write(Sgt.query(q[i].u));
    }
  }

  IO.out();

#ifdef forever23
	printf("Running Time = %d ms\n", int(clock() * 1000.0 / CLOCKS_PER_SEC));
#endif
  return 0;
}
