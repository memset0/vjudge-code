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

constexpr ld eps = 1e-11;
const int N = 4005;

struct Point {
  int x, y;
} p[N];

int n, ans, ls[N], rs[N];

int check(ld x, ld y) {
  int res = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    if (p[i].x < x && x <= p[j].x) {
      res += (y - p[i].y) * (p[j].x - p[i].x) >= (x - p[i].x) * (p[j].y - p[i].y);
    }
    if (p[j].x <= x && x < p[i].x) {
      res += (y - p[j].y) * (p[i].x - p[j].x) >= (x - p[j].x) * (p[i].y - p[j].y);
    }
  }
  return res;
}

void run() {
  in >> n;
  for (int i = 0; i < n; i++) {
    in >> p[i].x >> p[i].y;
    p[i].x *= 2;
    p[i].y *= 2;
    p[n + i] = p[i];
  }
  for (int i = 1, j = 0; i < n + n; i++) {
    if (p[i - 1].y != p[i].y) {
      j = i - 1;
    }
    if (i >= n) {
      ls[i - n] = j % n;
    }
  }
  for (int i = n + n - 2, j = 0; i >= 0; i--) {
    if (p[i + 1].y != p[i].y) {
      j = i + 1;
    }
    if (i < n) {
      rs[i] = j % n;
    }
  }
  std::map<std::pair<int, int>, int> map;
  for (int i = 0; i < n; i++) {
    map[{ls[i], rs[i]}] = i;
  }
  ans = 0;
  for (auto _ : map) {
    int u = _.second;
    if (p[ls[u]].y > p[u].y && p[u].y < p[rs[u]].y) {
      int l = (u - 1 + n) % n, r = (u + 1) % n;
      if ((p[l].x < p[u].x && p[u].x < p[r].x) || (p[l].x > p[u].x && p[u].x > p[r].x) || p[r].x == p[u].x) {
        if (p[l].x < p[u].x) {
          if (check((p[l].x + p[u].x) / 2 + eps, (p[l].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        } else {
          if (check((p[l].x + p[u].x) / 2 - eps, (p[l].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        }
      } else if (p[l].x == p[u].x) {
        if (p[r].x < p[u].x) {
          if (check((p[r].x + p[u].x) / 2 + eps, (p[r].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        } else {
          if (check((p[r].x + p[u].x) / 2 - eps, (p[r].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        }
      } else if (std::abs(1ll * (p[l].y - p[u].y) * (p[r].x - p[u].x)) < std::abs(1ll * (p[r].y - p[u].y) * (p[l].x - p[u].x))) {
        if (p[l].x < p[u].x) {
          if (check((p[l].x + p[u].x) / 2 + eps, (p[l].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        } else {
          if (check((p[l].x + p[u].x) / 2 - eps, (p[l].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        }
      } else {
        if (p[r].x < p[u].x) {
          if (check((p[r].x + p[u].x) / 2 + eps, (p[r].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        } else {
          if (check((p[r].x + p[u].x) / 2 - eps, (p[r].y + p[u].y) / 2 + eps) & 1) {
            ans++;
          }
        }
      }
    }
  }
  out << ans << "\n";
}

int main() {
#ifdef SULFOX
  freopen("#.in", "r", stdin);
  freopen("#.out", "w", stdout);
#endif
  int t = 1;
  // in >> t;
  for (int i = 0; i < t; i++) {
    run();
  }
  return 0;
}