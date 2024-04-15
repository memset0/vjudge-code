#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define il inline
#define MAXN 501000
#define to(k) E[k].to
#define val(k) E[k].val
#define next(k) E[k].next

using namespace std;

int ans, res;
bool vis[MAXN];
struct Edge {
  int to, next, val;
} E[MAXN << 1];
int head[MAXN], cnt;
int N, S, pre[MAXN], base[MAXN], d[MAXN], s[MAXN], tot;

#define ch_top 24000001
char ch[ch_top], *now_r = ch - 1, *now_w = ch - 1;

il int read() {
  while (*++now_r < 48)
    ;
  register int x = *now_r - 48;
  while (*++now_r >= 48)
    x = (x << 1) + (x << 3) + *now_r - 48;
  return x;
}

il void write(int x) {
  static char st[7];
  static int top;
  while (st[++top] = 48 + x % 10, x /= 10)
    ;
  while (*++now_w = st[top], --top)
    ;
  *++now_w = '\n';
}
il void add(int u, int v, int w) {
  to(++cnt) = v, val(cnt) = w, next(cnt) = head[u], head[u] = cnt;
  to(++cnt) = u, val(cnt) = w, next(cnt) = head[v], head[v] = cnt;
}
void dfs(int n, int fa) {
  d[n] = 0, pre[n] = 0;
  for (int k = head[n]; k; k = next(k)) {
    if (to(k) == fa)
      continue;
    dfs(to(k), n);
    if (d[to(k)] + val(k) > d[n])
      d[n] = d[to(k)] + val(k), pre[n] = to(k);
  }
}
void do_do(int u, int fa) {
  for (int k = head[u]; k; k = next(k)) {
    if (to(k) == fa)
      continue;
    do_do(to(k), u);
    if (vis[to(k)])
      continue;
    d[u] = max(d[to(k)] + val(k), d[u]);
  }
}

int main() {
  int u, v, w, n;
  fread(ch, 1, ch_top, stdin);
  N = read(), S = read();
  for (int i = 1; i < N; ++i)
    u = read(), v = read(), w = read(), add(u, v, w);
  dfs(1, 0), n = 1;
  while (pre[n])
    n = pre[n];
  dfs(n, 0);
  while (pre[n])
    vis[n] = 1, s[++tot] = n, n = pre[n];
  s[++tot] = n, vis[n] = 1;
  memset(d, 0, sizeof(d)), do_do(n, 0);
  for (int i = 1; i < tot; ++i)
    for (int j = head[s[i]]; j; j = next(j))
      if (to(j) == s[i + 1])
        base[i + 1] = val(j) + base[i];
  for (int i = 1; i <= tot; ++i)
    ans = std::max(ans, d[s[i]]);
  res = ans;
  for (int r = 1, l = 1; r <= tot; ++r) {
    while (base[r] - base[l] > S)
      ++l;
    res = std::min(res, std::max(std::max(base[l], base[tot] - base[r]), ans));
  }
  write(res);
  fwrite(ch, 1, now_w - ch, stdout);
  return 0;
}