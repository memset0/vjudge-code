#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 9, M = 5e5 + 9;
int n, p[N], cnt, nxt[N], d[M][2], len, c[10], temp, now;
bool flag, used[N];
vector<int> fac;
void init() {
  for (int i = 2; i < N; i++) {
    if (!used[i]) p[++cnt] = i, nxt[i] = p[cnt];
    for (int j = 1; j <= cnt && 1LL * i * p[j] < N; j++) {
      used[i * p[j]] = true, nxt[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}
void dfs(int u) {
  if (u > len) {
    int lef = 1, rig = 1;
    for (int i = 1; i <= len; i++) {
      if (c[i] == 1) lef *= fac[i - 1];
      if (c[i] == 2) rig *= fac[i - 1];
    }
    if (lef == 1 || rig == 1) return;
    if (__gcd(lef + rig, temp) == 1) d[now][0] = lef, d[now][1] = rig, flag = true;
    return;
  }
  c[u] = 0;
  dfs(u + 1);
  if (flag) return;
  c[u] = 1;
  dfs(u + 1);
  if (flag) return;
  c[u] = 2;
  dfs(u + 1);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  init();
  cin >> n;
  map<int, int> pre;
  for (int i = 1, v; i <= n; i++) {
    now = i, flag = false;
    fac.clear();
    unordered_map<int, int> r;
    cin >> v;
    temp = v;
    while (v > 1) {
      if (r[nxt[v]] == 0) fac.push_back(nxt[v]);
      r[nxt[v]]++, v /= nxt[v];
    }
    d[i][0] = d[i][1] = -1;
    len = (int)fac.size();
    // assert(len <= 8);
    auto it = pre.find(temp);
    if (it == pre.end()) {
      dfs(1);
      pre[temp] = i;
    } else {
      d[i][0] = d[it->second][0];
      d[i][1] = d[it->second][1];
    }
  }
  for (int i = 1; i <= n; i++) cout << d[i][0] << " \n"[i == n];
  for (int i = 1; i <= n; i++) cout << d[i][1] << " \n"[i == n];
}