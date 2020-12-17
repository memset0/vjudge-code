#include <bits/stdc++.h>
using namespace std;

inline int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (!isdigit(c))
    f = (c == '-') ? -1 : f, c = getchar();
  while (isdigit(c))
    x = x * 10 + c - '0', c = getchar();
  return x * f;
}

int n, s, t;
int hd[400005], nx[1000006], to[1000006], c[1000006], cnt;
void add(int f, int t, int cap) {
  nx[++cnt] = hd[f], hd[f] = cnt, to[cnt] = t, c[cnt] = cap;
}
void fadd(int f, int t, int c) { add(f, t, c), add(t, f, 0); }

int dep[400005];
queue<int> q;
bool bfs() {
  for (int i = 1; i <= t; ++i)
    dep[i] = 0;
  dep[s] = 1, q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = hd[u], v; i; i = nx[i]) {
      if (!c[i] || dep[v = to[i]])
        continue;
      dep[v] = dep[u] + 1, q.push(v);
    }
  }
  return dep[t];
}

int iter[400005];
int dfs(int u, int dist) {
  if (u == t)
    return dist;
  for (int &i = iter[u], v, d; i; i = nx[i]) {
    if (!c[i] || dep[v = to[i]] != dep[u] + 1)
      continue;
    if (d = dfs(v, min(dist, c[i])))
      return c[i] -= d, c[i ^ 1] += d, d;
  }
  return 0;
}
int Dinic() {
  int rt = 0, d;
  while (bfs()) {
    for (int i = 1; i <= t; ++i)
      iter[i] = hd[i];
    while (d = dfs(s, 10000000))
      rt += d;
  }
  return rt;
}

vector<int> e[400005];
int p[400005];
struct Res {
  int u, v;
} res[400005];
bool get_res() {
  for (int u = 1; u < n; ++u)
    for (int i = hd[u]; i; i = nx[i])
      if (to[i] != s && c[i] == 0)
        p[u] = to[i] - n + 1;

  int sum = 0;
  q.push(n);
  while (!q.empty()) {
    int u = q.front();
    ++sum, q.pop();
    for (int i = 0, v; i < e[u].size(); ++i)
      if (p[v = e[u][i]])
        res[v] = (Res){u, p[v]}, q.push(p[v]), p[v] = 0;
  }
  return sum == n;
}

int main() {
  n = read(), s = 2 * n - 1, t = 2 * n, cnt = 1;
  for (int i = 1; i < n; ++i)
    fadd(i + n - 1, t, 1);
  for (int i = 1, c, u; i < n; ++i) {
    c = read(), fadd(s, i, 1);
    while (c--) {
      if ((u = read()) != n)
        fadd(i, u + n - 1, 1);
      e[u].push_back(i);
    }
  }
  if (Dinic() < n - 1)
    return puts("-1"), 0;
  if (!get_res())
    return puts("-1"), 0;

  for (int i = 1; i < n; ++i)
    printf("%d %d\n", res[i].u, res[i].v);

  return 0;
}