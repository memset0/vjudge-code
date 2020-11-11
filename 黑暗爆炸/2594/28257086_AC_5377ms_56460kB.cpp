#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct edge {
  int x, y, z;
  bool operator<(const edge &Y) const {
    if (x == Y.x)
      return y < Y.y;
    return x < Y.x;
  }
  bool operator<(const pair<int, int> &Y) const {
    if (x == Y.first)
      return y < Y.second;
    return x < Y.first;
  }
} edges[1001001];
struct abcd {
  abcd *ls, *rs, *fa;
  int e, max_e;
  bool rev_mark;
  abcd(int x);
  void Push_Up();
  void Push_Down();
  void Reverse();
} *null = new abcd(0), *tree[1100100];
struct query {
  int p, x, y;
} queries[100100];
struct _edge {
  int x, y, z, pos;
  bool operator<(const _edge &Y) const { return z < Y.z; }
  void operator=(const edge &Y) {
    x = Y.x;
    y = Y.y;
    z = Y.z;
    pos = (&Y) - edges;
  }
} _edges[1001001];
struct Complex {
  int to, z, next;
} table[200200];

int head[100100], tot;
int n, m, q;
bool v[1001001];
int fa[100100];
int stack[100100], top;

void Add(int x, int y, int z) {
  table[++tot].to = y;
  table[tot].z = z;
  table[tot].next = head[x];
  head[x] = tot;
}
int Find(int x) {
  if (!fa[x] || fa[x] == x)
    return fa[x] = x;
  return fa[x] = Find(fa[x]);
}
inline bool Compare(int x, int y) { return edges[x].z < edges[y].z; }
abcd ::abcd(int x) {
  ls = rs = fa = null;
  e = max_e = x;
  rev_mark = 0;
}
void abcd ::Push_Up() {
  max_e = max(ls->max_e, rs->max_e, Compare);
  max_e = max(max_e, e, Compare);
}
void abcd ::Push_Down() {
  if (fa->ls == this || fa->rs == this)
    fa->Push_Down();
  if (rev_mark) {
    ls->Reverse();
    rs->Reverse();
    rev_mark = 0;
  }
}
void abcd ::Reverse() {
  swap(ls, rs);
  rev_mark ^= 1;
}
void Zig(abcd *x) {
  abcd *y = x->fa;
  y->ls = x->rs;
  x->rs->fa = y;
  x->rs = y;
  x->fa = y->fa;
  if (y == y->fa->ls)
    y->fa->ls = x;
  else if (y == y->fa->rs)
    y->fa->rs = x;
  y->fa = x;
  y->Push_Up();
}
void Zag(abcd *x) {
  abcd *y = x->fa;
  y->rs = x->ls;
  x->ls->fa = y;
  x->ls = y;
  x->fa = y->fa;
  if (y == y->fa->ls)
    y->fa->ls = x;
  else if (y == y->fa->rs)
    y->fa->rs = x;
  y->fa = x;
  y->Push_Up();
}
void Splay(abcd *x) {
  x->Push_Down();
  while (x->fa->ls == x || x->fa->rs == x) {
    abcd *y = x->fa, *z = y->fa;
    if (x == y->ls) {
      if (y == z->ls)
        Zig(y);
      Zig(x);
    } else {
      if (y == z->rs)
        Zag(y);
      Zag(x);
    }
  }
  x->Push_Up();
}
inline void Access(abcd *x) {
  abcd *y = null;
  while (x != null) {
    Splay(x);
    x->rs = y;
    x->Push_Up();
    y = x;
    x = x->fa;
  }
}
inline void Move_To_Root(abcd *x) {
  Access(x);
  Splay(x);
  x->Reverse();
}
inline abcd *Find_Root(abcd *x) {
  while (x->fa != null)
    x = x->fa;
  return x;
}
inline void Link(abcd *x, abcd *y) {
  Move_To_Root(x);
  x->fa = y;
}
inline void Cut(abcd *x, abcd *y) {
  Move_To_Root(x);
  Access(y);
  Splay(y);
  y->ls = null;
  x->fa = null;
  y->Push_Up();
}

inline char Get_Char() {
  static const int len = 1 << 15;
  static char buffer[len];
  static char *S, *T;
  if (S == T) {
    T = (S = buffer) + fread(buffer, 1, len, stdin);
    if (S == T)
      return EOF;
  }
  return *S++;
}
inline int Get_Int() {
  char c = Get_Char();
  while (c < '0' || c > '9')
    c = Get_Char();
  int re = 0;
  while (c >= '0' && c <= '9')
    re = (re << 1) + (re << 3) + (c - '0'), c = Get_Char();
  return re;
}
void Kruskal() {
  int i, top = 0;
  for (i = 1; i <= m; i++)
    if (!v[i])
      _edges[++top] = edges[i];
  sort(_edges + 1, _edges + top + 1);
  for (i = 1; i <= top; i++) {
    int x = _edges[i].x, y = _edges[i].y;
    if (Find(x) == Find(y))
      continue;
    fa[Find(x)] = Find(y);
    Add(x, y, _edges[i].pos);
    Add(y, x, _edges[i].pos);
  }
}
void DFS(int x, int from, int from_e) {
  static bool v[100100];
  int i;
  if (v[x])
    return;
  v[x] = 1;
  tree[x] = new abcd(0);
  if (from) {
    tree[n + from_e] = new abcd(from_e);
    tree[n + from_e]->fa = tree[from];
    tree[x]->fa = tree[n + from_e];
  }
  for (i = head[x]; i; i = table[i].next)
    DFS(table[i].to, x, table[i].z);
}
inline int Query(abcd *x, abcd *y) {
  Move_To_Root(x);
  Access(y);
  Splay(y);
  return y->max_e;
}
void Insert(int pos) {
  abcd *x = tree[edges[pos].x];
  abcd *y = tree[edges[pos].y];
  if (Find_Root(x) == Find_Root(y)) {
    int temp = Query(x, y);
    if (edges[temp].z <= edges[pos].z)
      return;
    Cut(tree[n + temp], tree[edges[temp].x]);
    Cut(tree[n + temp], tree[edges[temp].y]);
  }
  tree[n + pos] = new abcd(pos);
  Link(x, tree[n + pos]);
  Link(y, tree[n + pos]);
}
int main() {

  // freopen("2594.in","r",stdin);
  // freopen("2594.out","w",stdout);

  int i, x, y, z;
  cin >> n >> m >> q;
  for (i = 1; i <= m; i++) {
    edges[i].x = Get_Int();
    edges[i].y = Get_Int();
    edges[i].z = Get_Int();
  }
  sort(edges + 1, edges + m + 1);
  for (i = 1; i <= q; i++) {
    queries[i].p = Get_Int();
    queries[i].x = Get_Int();
    queries[i].y = Get_Int();
    if (queries[i].p == 2) {
      int temp = lower_bound(edges + 1, edges + m + 1,
                             make_pair(queries[i].x, queries[i].y)) -
                 edges;
      queries[i].x = temp;
      v[temp] = 1;
    }
  }
  Kruskal();
  for (i = 1; i <= n; i++)
    DFS(i, 0, 0);
  for (i = q; i; i--) {
    if (queries[i].p == 1)
      stack[++top] = edges[Query(tree[queries[i].x], tree[queries[i].y])].z;
    else
      Insert(queries[i].x);
  }
  while (top)
    printf("%d\n", stack[top--]);
}