#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define DB double
#define MAXN 250000
#define MOD 1000000007
#define Pr pair<int, int>
#define X first
#define Y second
#define INF 1000000000000000000
#define mem(x, v) memset(x, v, sizeof(x))

LL read() {
  LL x = 0, F = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      F = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * F;
}

int n, lim, du[MAXN + 5], vis[MAXN + 5];
vector<Pr> G[MAXN + 5], T;
LL ans, dp[MAXN + 5][2];
bool cmp(Pr s1, Pr s2) { return du[s1.X] > du[s2.X]; }

struct Queue {
  LL tot;
  int siz;
  priority_queue<LL> Q, pQ;
  void push(LL x) { Q.push(x), tot += x, siz++; }
  void del(LL x) { pQ.push(x), tot -= x, siz--; }
  LL top() {
    while (!Q.empty() && !pQ.empty() && Q.top() == pQ.top())
      Q.pop(), pQ.pop();
    return Q.top();
  }
  void pop() { tot -= top(), Q.pop(), siz--; }
} H[MAXN + 5];

void dfs(int x, int fa) {
  vis[x] = lim;
  int num = du[x] - lim; //该删除的边数
  dp[x][0] = dp[x][1] = 0;
  while (H[x].siz > num)
    H[x].pop();
  vector<LL> tmp1, tmp2;
  for (int i = 0; i < G[x].size(); i++) {
    int v = G[x][i].X, w = G[x][i].Y;
    if (du[v] <= lim)
      break;
    if (v == fa)
      continue;
    dfs(v, x);
    LL val = dp[v][1] + w - dp[v][0];
    if (val <= 0) {
      dp[x][1] += dp[v][1] + w;
      dp[x][0] += dp[v][1] + w;
      num--;
    } else {
      dp[x][1] += dp[v][0];
      dp[x][0] += dp[v][0];
      H[x].push(val);
      tmp2.push_back(val);
    }
  }
  if (num > 0) {
    while (H[x].siz > num)
      tmp1.push_back(H[x].top()), H[x].pop();
    dp[x][0] += H[x].tot;
    while (H[x].siz > num - 1)
      tmp1.push_back(H[x].top()), H[x].pop();
    dp[x][1] += H[x].tot;
  }
  for (int i = 0; i < tmp1.size(); i++)
    H[x].push(tmp1[i]);
  for (int i = 0; i < tmp2.size(); i++)
    H[x].del(tmp2[i]);
}

int main() {
  n = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read(), w = read();
    du[u]++, du[v]++;
    G[u].push_back(Pr(v, w));
    G[v].push_back(Pr(u, w));
    ans += w;
  }
  for (int i = 1; i <= n; i++) {
    T.push_back(Pr(du[i], i));
    sort(G[i].begin(), G[i].end(), cmp);
  }
  sort(T.begin(), T.end());
  printf("%lld", ans);
  lim = 1;
  int j = 0;
  while (lim < n) {
    while (j < n && T[j].X == lim) {
      int x = T[j].Y;
      for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i].X, w = G[x][i].Y;
        if (du[v] <= lim)
          break;
        H[v].push(w);
      }
      j++;
    }
    ans = 0;
    for (int i = j; i < n; i++) {
      int x = T[i].Y;
      if (vis[x] != lim)
        dfs(x, 0), ans += dp[x][0];
    }
    printf(" %lld", ans);
    lim++;
  }
}