#include <bits/stdc++.h>
using namespace std;
const int N = 510, M = 1 << 21;
int n, c, s, t, l, r, ans, cnt, nod, ind[N * N], q[M], pre[M], dis[M], minA[N], minB[N], id[N][N], num[N][N];
int tot = 2, hed[M], nxt[M], to[M], val[M], cst[M];
bool mrk[N][N], inq[M];
char a[N], b[N];
vector<int> G[N * N];
vector<pair<int, int>> seq(1), loc(1);
inline void add(int u, int v, int w) {
  nxt[tot] = hed[u], to[tot] = v, val[tot] = 1, cst[tot] = w, hed[u] = tot++;
  nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -w, hed[v] = tot++;
}
void way(char *a, int *min) {
  int x = 1, y = 1;
  for (int i = 1; i <= n; i++)
    if (a[i] == '1') {
      min[x] = y;
      for (int i = y; i < N; i++) mrk[x][i] ^= 1;
      ++x;
    } else {
      ++y;
    }
}
bool spfa() {
  memset(pre + 1, 0, nod << 2);
  memset(dis + 1, -63, nod << 2);
  dis[s] = pre[s] = 0;
  q[l = r = 1] = s, inq[s] = true;
  while (l <= r) {
    int u = q[(l++) % M];
    inq[u] = false;
    for (int i = hed[u]; i; i = nxt[i])
      if (val[i] && dis[to[i]] < dis[u] + cst[i]) {
        pre[to[i]] = i;
        dis[to[i]] = dis[u] + cst[i];
        if (!inq[to[i]]) q[(++r) % M] = to[i], inq[to[i]] = 1;
      }
  }
  return pre[t] && dis[t] > 0;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> c >> a >> b;
  a.insert(a.begin(), '\0');
  b.insert(b.begin(), '\0');
  way(a, minA);
  way(b, minB);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j]) {
        id[i][j] = ++nod;
        loc.push_back({i, j});
        ans += 3 + c;
      }
  s = ++nod, t = ++nod;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j]) {
        if ((i + j) & 1) {
          add(s, id[i][j], 0);
          for (int d = -1; d <= 1; d += 2) {
            if (mrk[i + d][j]) add(id[i][j], id[i + d][j], 2 + c);
            if (mrk[i][j + d]) add(id[i][j], id[i][j + d], 1 + c);
          }
        } else {
          add(id[i][j], t, 0);
        }
      }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j] && mrk[i + 1][j]) {
        auto connect = [&](int i, int j) {
          int u = id[i][j];
          for (int i = hed[u]; i; i = nxt[i]) {
            if (to[i] == s) return val[i];
            if (to[i] == t) return val[i ^ 1];
          }
          assert(0);
        };
        auto play = [&](int u, int v, int k) {
          for (int i = hed[u]; i; i = nxt[i])
            if (to[i] == v) {
              ans -= k * cst[i];
              val[i] -= k, val[i ^ 1] += k;
            }
        };
        if (!connect(i, j) && !connect(i + 1, j)) {
          int u = id[i][j], v = id[i + 1][j];
          if (!((i + j) & 1)) swap(u, v);
          play(u, s, -1);
          play(u, v, 1);
          play(v, t, 1);
        }
      }
  while (spfa()) {
    int sum = 0;
    for (int i = pre[t]; i; i = pre[to[i ^ 1]]) {
      sum += cst[i];
      val[i]--, val[i ^ 1]++;
    }
    ans -= sum;
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j] && ((i + j) & 1)) {
        int ii = 0, jj = 0;
        for (int k = hed[id[i][j]]; k; k = nxt[k])
          if (to[k] != s && val[k ^ 1]) {
            ii = loc[to[k]].first;
            jj = loc[to[k]].second;
          }
        if (ii && jj) {
          int k = min(i + j, ii + jj) - 1;
          num[i][j] = num[ii][jj] = ++cnt;
          seq.push_back({k, k + 2});
        }
      }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j] && !num[i][j]) {
        int k = i + j - 1;
        num[i][j] = ++cnt;
        seq.push_back({k, k + 1});
      }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (mrk[i][j]) {
        if (minA[i] < minB[i]) {
          if (mrk[i + 1][j] && num[i][j] != num[i + 1][j]) {
            G[num[i + 1][j]].push_back(num[i][j]);
            ++ind[num[i][j]];
          }
          if (mrk[i][j - 1] && num[i][j] != num[i][j - 1]) {
            G[num[i][j - 1]].push_back(num[i][j]);
            ++ind[num[i][j]];
          }
        } else {
          if (mrk[i - 1][j] && num[i][j] != num[i - 1][j]) {
            G[num[i - 1][j]].push_back(num[i][j]);
            ++ind[num[i][j]];
          }
          if (mrk[i][j + 1] && num[i][j] != num[i][j + 1]) {
            G[num[i][j + 1]].push_back(num[i][j]);
            ++ind[num[i][j]];
          }
        }
      }
  printf("%d\n", cnt);
  l = 1, r = 0;
  for (int i = 1; i <= cnt; i++)
    if (!ind[i]) q[++r] = i;
  while (l <= r) {
    int u = q[l++];
    printf("%d %d\n", seq[u].first, seq[u].second);
    for (int v : G[u]) {
      if (!--ind[v]) q[++r] = v;
    }
  }
}