
#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;

namespace fox {
template <class T> constexpr T pow(T x, ll y) {
  T r = 1;
  for (; y > 0; y /= 2, x = x * x)
    if (y % 2 == 1) r = x * r;
  return r;
}
} // namespace fox

struct Scanner {
  FILE *stream;
  Scanner(FILE *s) : stream(s) {}
  char buf[1 << 20], *l = buf, *r = buf;
  bool flush() {
    l = buf;
    r = l + fread(buf, 1, 1 << 20, stream);
    return l == r;
  }
  void get(char &c) { c = l == r && flush() ? ' ' : *l++; }
  friend Scanner &operator>>(Scanner &in, char &c) { return in.get(c), in; }
  friend Scanner &operator>>(Scanner &in, char *s) {
    for (in.get(s[0]); isspace(s[0]); in.get(s[0]))
      ;
    for (int i = 0; !isspace(s[i]) || (s[i] = '\0'); i++) in.get(s[i + 1]);
    return in;
  }
  friend Scanner &operator>>(Scanner &in, std::string &s) {
    char c;
    for (in.get(c); isspace(c); in.get(c))
      ;
    for (s = ""; !isspace(c); in.get(c)) s += c;
    return in;
  }
  template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0> friend Scanner &operator>>(Scanner &in, T &x) {
    char c, f = '+';
    for (in.get(c); !isdigit(c); in.get(c))
      if constexpr (std::is_signed_v<T>) f = c;
    for (x = 0; isdigit(c); in.get(c)) x = x * 10 + c - '0';
    if constexpr (std::is_signed_v<T>) x = f == '-' ? -x : x;
    return in;
  }
  template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0> friend Scanner &operator>>(Scanner &in, T &x) {
    std::string s;
    in >> s;
    x = std::stod(s);
    return in;
  }
  template <class T, class U> friend Scanner &operator>>(Scanner &in, std::pair<T, U> &a) { return in >> a.first >> a.second; }
  template <class T, size_t S> friend Scanner &operator>>(Scanner &in, std::array<T, S> &a) {
    for (int i = 0, n = S; i < n; i++) in >> a[i];
    return in;
  }
  template <class T> friend Scanner &operator>>(Scanner &in, std::vector<T> &a) {
    for (int i = 0, n = a.size(); i < n; i++) in >> a[i];
    return in;
  }
};

struct Printer {
  FILE *stream;
  Printer(FILE *s) : stream(s) {}
  char buf[1 << 20], *l = buf, *r = buf + (1 << 20) - 1;
  int format = 0, precision = 15;
  ~Printer() { flush(); }
  void flush() {
    fwrite(buf, 1, l - buf, stream);
    l = buf;
  }
  void put(const char &c) {
    *l++ = c;
    if (l == r) flush();
  }
  friend Printer &operator<<(Printer &out, const char &c) { return out.put(c), out; }
  friend Printer &operator<<(Printer &out, const char *s) {
    for (int i = 0; s[i] != '\0'; i++) out.put(s[i]);
    return out;
  }
  friend Printer &operator<<(Printer &out, const std::string &s) {
    for (int i = 0, n = s.size(); i < n; i++) out.put(s[i]);
    return out;
  }
  template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0> friend Printer &operator<<(Printer &out, T x) {
    static char s[40];
    static int i = 0;
    if (x == 0) {
      out.put('0');
      return out;
    }
    if constexpr (std::is_signed_v<T>) x = x < 0 ? out.put('-'), -x : x;
    while (x > 0) s[++i] = x % 10 + '0', x /= 10;
    while (i > 0) out.put(s[i--]);
    return out;
  }
  template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0> friend Printer &operator<<(Printer &out, T x) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(out.precision) << x;
    return out << oss.str();
  }
  template <class T, class U> friend Printer &operator<<(Printer &out, const std::pair<T, U> &a) { return out << a.first << " \n"[out.format > 1] << a.second; }
  template <class T, size_t S> friend Printer &operator<<(Printer &out, const std::array<T, S> &a) {
    out << a[0];
    for (int i = 1, n = S; i < n; i++) out << " \n"[out.format > 1] << a[i];
    return out;
  }
  template <class T> friend Printer &operator<<(Printer &out, const std::vector<T> &a) {
    if (!a.empty()) out << a[0];
    for (int i = 1, n = a.size(); i < n; i++) out << " \n"[out.format > 0] << a[i];
    return out;
  }
};

Scanner in(stdin);
Printer out(stdout), err(stderr);

const int N = 2e5 + 9, M = 1e6 + 9;

#define fclear(x) memset(x, 0, ((n << 1) + 5) << 2)

int n, m, q, anc[N], anc0[N], id[N];
int num, tms, vol, dfn[N], low[N], stc[N], f[N], g[N];
bool ins[N];
std::vector<int> ed[N];
std::map<std::pair<int, int>, int> map, cnt;

void force_clear() {
  fclear(anc);
  fclear(anc0);
  fclear(id);
  fclear(dfn);
  fclear(low);
  fclear(stc);
  fclear(f);
  fclear(g);
  tms = vol = 0;
  memset(ins, 0, (n << 1) + 5);
	map.clear();
	cnt.clear();
  for (int i = 0; i <= (n << 1) + 3; i++) {
    ed[i].clear();
  }
}

struct List {
  int tot, fst[N], nxt[M], to[M], val[M];

  void init(int n) {
    tot = 0;
    memset(fst, -1, (n + 1) * 4);
  }
  inline void insert(int u, int v, int w) {
    nxt[tot] = fst[u];
    to[tot] = v;
    val[tot] = w;
    fst[u] = tot++;
  }
  inline void link(int u, int v, int w) {
    insert(u, v, w);
    insert(v, u, w);
  }
} e, ie;

void tarjan(int u, int fa) {
  dfn[u] = low[u] = ++tms;
  stc[++vol] = u;
  ins[u] = true;
  for (int i = e.fst[u], v, w; ~i; i = e.nxt[i]) {
    v = e.to[i], w = e.val[i];
    if (!dfn[v]) {
      id[v] = i ^ 1;
      tarjan(v, u);
      low[u] = std::min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        std::vector<int> vec;
        ie.link(u, ++num, 0);
        f[num] = 0;
        vec.push_back(u);
        for (; stc[vol + 1] != v; vol--) {
          for (auto j : ed[stc[vol]]) {
            f[num] |= e.val[j];
          }
          ins[stc[vol]] = false;
          ie.link(stc[vol], num, 0);
          vec.push_back(stc[vol]);
          f[num] |= e.val[id[stc[vol]]];
        }
      }
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  for (int i = e.fst[u], v, w; ~i; i = e.nxt[i]) {
    v = e.to[i];
    w = e.val[i];
    if (ins[v] && v != fa) {
      ed[u].push_back(i);
    }
  }
}

int find(int u) { return anc[u] == u ? u : anc[u] = find(anc[u]); }
int find0(int u) { return anc0[u] == u ? u : anc0[u] = find0(anc0[u]); }

void run() {
  in >> n >> m >> q;
  map.clear();
  cnt.clear();
	force_clear();
  for (int u = 1; u <= num; u++) {
    f[u] = 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    in >> u >> v >> w;
    if (u == v) {
      f[u] |= w;
      continue;
    }
    if (u > v) {
      std::swap(u, v);
    }
    map[{u, v}] |= w;
    cnt[{u, v}]++;
  }
  for (int u = 1; u <= n; u++) {
    dfn[u] = 0;
    ed[u].clear();
  }
  e.init(n * 2);
  ie.init(n * 2);
  num = n;
  for (auto i : map) {
    auto [u, v] = i.first;
    e.link(u, v, i.second);
  }
  for (int u = 1; u <= n; u++) {
    if (dfn[u] == 0) {
      tarjan(u, 0);
    }
  }
  for (int u = 1; u <= num; u++) {
    anc[u] = u;
    g[u] = 0;
  }
  for (int u = n + 1; u <= num; u++) {
    std::vector<int> vec;
    for (int i = ie.fst[u], v; ~i; i = ie.nxt[i]) {
      v = ie.to[i];
      vec.push_back(v);
    }
    bool ok = false;
    if (vec.size() == 2) {
      int x = vec[0], y = vec[1];
      if (cnt[{x, y}] > 1 || cnt[{y, x}] > 1) {
        ok = true;
      }
    } else {
      ok = true;
    }
    if (ok) {
      for (int i = ie.fst[u], v; ~i; i = ie.nxt[i]) {
        v = ie.to[i];
        if (find(u) != find(v)) {
          anc[find(u)] = find(v);
        }
      }
    }
  }
  for (int u = 1; u <= num; u++) {
    g[find(u)] |= f[u];
  }
  for (int u = 1; u <= num; u++) {
    anc0[u] = anc[u];
  }
  for (int u = n + 1; u <= num; u++) {
    if (g[find(u)] == 0) {
      for (int i = ie.fst[u], v; ~i; i = ie.nxt[i]) {
        v = ie.to[i];
        if (find0(u) != find0(v) && g[find(v)] == 0) {
          anc0[find0(u)] = find0(v);
        }
      }
    }
  }
  for (; q; q--) {
    int u, v;
    in >> u >> v;
    out << (find0(u) == find0(v) && g[find(u)] == 0 && g[find(v)] == 0 ? "awsl!" : "wow!golden legendary!") << "\n";
  }
}

int main() {
#ifdef SULFOX
  freopen("#.in", "r", stdin);
  freopen("#.out", "w", stdout);
#endif
  int t = 1;
  in >> t;
  for (int i = 0; i < t; i++) {
    run();
  }
  return 0;
}