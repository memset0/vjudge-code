// =================================
//   author: memset0
//   date: 2019.07.16 08:30:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 4e5 + 10;
ll ans, dis[N];
std::vector<int> G[N];
int n, m, cnt, A, B, C;
std::map<int, int> map[N];
int ind[N], rnk[N], tag[N];
std::vector<std::pair<int, int> > v_map[N];

struct info_s {
  int u, x, id;
  inline bool operator<(const info_s &other) const {
    return x > other.x;
  }
} info[N];
std::priority_queue<info_s> q;

struct edge_s {
  int u, v, x, y;
} edge[N];

inline ll super_min(ll x, ll y) {
  if (x == -1) return y;
  if (y == -1) return x;
  if (x < y) return x;
  return y;
}

inline int calc(int x) {
  return A * x * x + B * x + C;
}

inline int get_id(int u, int x) {
  std::map<int, int>::iterator it = map[u].find(x);
  if (it != map[u].end()) return it->second;
  map[u][x] = ++cnt;
  info[cnt] = (info_s){u, x, cnt};
  return cnt;
}

inline int get_dis(const info_s &node) {
  int res = -1;
  for (int i = 0; i <= rnk[node.id]; i++) {
    std::pair<int, int> it = v_map[node.u][i];
    if (~dis[it.second])
      res = super_min(res, dis[it.second] + calc(node.x - it.first));
  }
  return res;
}

void main() {
  memset(dis, -1, sizeof(dis));
  read(n), read(m), read(A), read(B), read(C);
  map[1][0] = cnt = 1, info[1] = (info_s){1, 0, 1};
  for (int i = 1, u, v, x, y; i <= m; i++) {
    read(u), read(v), read(x), read(y);
    edge[i] = (edge_s){u, v, x, y};
    int U = get_id(u, x), V = get_id(v, y);
    G[U].push_back(V), ++ind[V];
    // printf("edge: %d %d %d %d [%d %d]\n", u, v, x, y, U, V);
  }
  for (int i = 1; i <= n; i++) {
    for (std::map<int, int>::iterator it = map[i].begin(); it != map[i].end(); it++) {
      rnk[it->second] = v_map[i].size();
      v_map[i].push_back(std::make_pair(it->first, it->second));
    }
  }
  for (int i = 1; i <= cnt; i++)
    if (!ind[i]) q.push(info[i]);
  dis[1] = 0;
  while (q.size()) {
    info_s it = q.top(); q.pop();
    // printf("> %d %d %d\n", it.u, it.x, it.id);
    int u = it.id, base = get_dis(it);
    tag[u] = 1;
    for (std::vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
      int v = *it;
      if (~base);
        dis[v] = super_min(base, dis[v]);
      if (!--ind[v])
        q.push(info[v]);
    }
  }
  ans = -1;
  for (std::map<int, int>::iterator it = map[n].begin(); it != map[n].end(); it++)
    if (~dis[it->second])
      ans = super_min(ans, dis[it->second] + it->first);
  print(ans, '\n');
  // print(dis, 1, cnt);
  // for (int i = 1; i <= cnt; i++)
  //   printf("info[%d] => {%d, %d} => %d\n", i, info[i].u, info[i].x, ind[i]);
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#else
  freopen("route.in", "r", stdin);
  freopen("route.out", "w", stdout);
#endif
  ringo::main();
  // std::cerr << "clock: " << clock() / (double)CLOCKS_PER_SEC << std::endl;
  return 0;
}