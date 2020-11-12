#include <bits/stdc++.h>
#define maxn 100010
#define mp(x, y) make_pair(x, y)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch - '0' < 0 || ch - '0' > 9) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch - '0' >= 0 && ch - '0' <= 9) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int n, Q, A, B;
int head[maxn], nxt[maxn * 2], to[maxn * 2], c[maxn * 2], tot;
void add(int u, int v, int x) {
  tot++;
  nxt[tot] = head[u];
  head[u] = tot;
  to[tot] = v;
  c[tot] = x;
}
int mx, pos;
void dfs(int x, int las, int d) {
  if (d > mx)
    mx = d, pos = x;
  for (int i = head[x]; i; i = nxt[i]) {
    if (to[i] == las)
      continue;
    dfs(to[i], x, d + c[i]);
  }
}
void Find() {
  mx = pos = 0;
  dfs(1, 0, 0);
  A = pos;
  mx = pos = 0;
  dfs(A, 0, 0);
  B = pos;
}
struct Tree {
  int up[maxn][22], dep[maxn], mx[maxn], ans[maxn];
  int s[maxn], top, p[maxn], up_dis[maxn], size[maxn];
  void dfs(int x, int las) {
    p[++top] = x;
    s[x] = top;
    size[x] = 1;
    mx[x] = dep[x];
    for (int i = 1; i <= 20; i++)
      up[x][i] = up[up[x][i - 1]][i - 1];
    for (int i = head[x]; i; i = nxt[i]) {
      if (to[i] == las)
        continue;
      dep[to[i]] = dep[x] + c[i];
      up[to[i]][0] = x;
      up_dis[to[i]] = c[i];
      dfs(to[i], x);
      mx[x] = max(mx[x], mx[to[i]]);
      size[x] += size[to[i]];
    }
  }
  pii t[maxn * 4];
  int vis[maxn], tag[maxn * 4];
  void update(int k) { t[k] = max(t[k * 2], t[k * 2 + 1]); }
  void build(int k, int l, int r) {
    if (l == r) {
      t[k] = mp(dep[p[l]], p[l]);
      return;
    }
    int mid = (l + r) / 2;
    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);
    update(k);
  }
  void pushdown(int k) {
    if (!tag[k])
      return;
    tag[k * 2] += tag[k];
    tag[k * 2 + 1] += tag[k];
    t[k * 2].fi += tag[k];
    t[k * 2 + 1].fi += tag[k];
    tag[k] = 0;
  }
  void modi(int k, int l, int r, int x, int y, int z) {
    if (l >= x && r <= y) {
      tag[k] += z;
      t[k].fi += z;
      return;
    }
    pushdown(k);
    int mid = (l + r) / 2;
    if (mid >= x)
      modi(k * 2, l, mid, x, y, z);
    if (mid < y)
      modi(k * 2 + 1, mid + 1, r, x, y, z);
    update(k);
  }
  void pre() {
    for (int i = 1; i <= n; i++) {
      int x = t[1].se;
      ans[i] = ans[i - 1] + t[1].fi;
      while (!vis[x] && x) {
        modi(1, 1, n, s[x], s[x] + size[x] - 1, -up_dis[x]);
        vis[x] = i;
        x = up[x][0];
      }
    }
  }
  int query(int x, int y) {
    y = min(y, n);
    if (vis[x] <= y)
      return ans[y];
    int now = x;
    for (int i = 20; i >= 0; i--)
      if (vis[up[now][i]] >= y)
        now = up[now][i];
    now = up[now][0];
    int res = mx[x] - dep[now] + ans[y - 1];
    now = x;
    for (int i = 20; i >= 0; i--)
      if (vis[up[now][i]] > y)
        now = up[now][i];
    now = up[now][0];
    res = max(res, ans[y] - mx[now] + mx[x]);
    return res;
  }
} T1, T2;
int main() {
  n = read();
  Q = read();
  for (int i = 1; i < n; i++) {
    int q = read(), w = read(), e = read();
    add(q, w, e);
    add(w, q, e);
  }
  Find();
  T1.dfs(A, 0);
  T1.build(1, 1, n);
  T1.pre();
  T2.dfs(B, 0);
  T2.build(1, 1, n);
  T2.pre();
  int las = 0;
  while (Q--) {
    int x = (read() + las - 1) % n + 1, y = (read() + las - 1) % n + 1;
    printf("%d\n", las = max(T1.query(x, 2 * y - 1), T2.query(x, 2 * y - 1)));
  }
  return 0;
}