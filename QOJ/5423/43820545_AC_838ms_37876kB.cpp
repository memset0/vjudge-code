// code by Sooke

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

const int N = 2e5 + 5;

int n, num, tms, a[N], x[N], y[N], vis[N], f[N], dir[N];
std::vector<std::pair<int, int>> e[N];

void dfs(int u, int fa) {
  vis[u] = tms;
  for (auto [v, i] : e[u]) {
    if (v == fa || vis[v] == tms) {
      continue;
    }
    dfs(v, u);
    if (f[v] == 1) {
      f[v] ^= 1;
      f[u] ^= 1;
      dir[i] ^= 1;
    }
  }
}

void run() {
  in >> n;
  std::map<int, int> xmap, ymap;
  for (int i = 1; i <= n; i++) {
    in >> a[i];
    xmap[a[i] - i] = ymap[a[i] + i] = 0;
  }
  num = 0;
  for (auto &i : xmap) {
    i.second = ++num;
    f[num] = 0;
    e[num].clear();
  }
  for (auto &i : ymap) {
    i.second = ++num;
    f[num] = 0;
    e[num].clear();
  }
  std::vector<std::vector<int>> ans(num + 1);
  for (int i = 1; i <= n; i++) {
    x[i] = xmap[a[i] - i];
    y[i] = ymap[a[i] + i];
    dir[i] = 0;
    f[x[i]] ^= 1;
    e[x[i]].push_back({y[i], i});
    e[y[i]].push_back({x[i], i});
  }
  tms++;
  for (int u = 1; u <= num; u++) {
    if (vis[u] == tms) {
      continue;
    }
    dfs(u, 0);
    if (f[u] == 1) {
      out << "No\n";
      return;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (dir[i] == 0) {
      ans[x[i]].push_back(i);
    }
    if (dir[i] == 1) {
      ans[y[i]].push_back(i);
    }
  }
  out << "Yes\n";
  for (int u = 1; u <= num; u++) {
    for (int i = 1; i < ans[u].size(); i += 2) {
      out << ans[u][i - 1] << " " << ans[u][i] << "\n";
    }
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