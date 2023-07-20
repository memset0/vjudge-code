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

template <int mod> struct ModInt {
  int x;
  constexpr ModInt() : x(0) {}
  template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0> constexpr ModInt(T x) : x((x % mod + mod) % mod) {}
  constexpr ModInt inv() const {
    assert(x > 0);
    return fox::pow(*this, mod - 2);
  }
  constexpr ModInt operator-() const {
    if (x == 0) return 0;
    return mod - x;
  }
  constexpr ModInt &operator++() {
    if ((++x) == mod) x = 0;
    return *this;
  }
  constexpr ModInt &operator--() {
    if ((--x) == -1) x = mod - 1;
    return *this;
  }
  constexpr ModInt operator++(int) {
    ModInt n(*this);
    ++*this;
    return n;
  }
  constexpr ModInt operator--(int) {
    ModInt n(*this);
    --*this;
    return n;
  }
  constexpr ModInt &operator+=(const ModInt &rhs) {
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt &operator-=(const ModInt &rhs) {
    if ((x -= rhs.x) < 0) x += mod;
    return *this;
  }
  constexpr ModInt &operator*=(const ModInt &rhs) {
    x = (ll)x * rhs.x % mod;
    return *this;
  }
  constexpr ModInt &operator/=(const ModInt &rhs) {
    x = (ll)x * rhs.inv().x % mod;
    return *this;
  }
  constexpr friend bool operator<(const ModInt &lhs, const ModInt &rhs) { return lhs.x < rhs.x; }
  constexpr friend bool operator==(const ModInt &lhs, const ModInt &rhs) { return lhs.x == rhs.x; }
  constexpr friend bool operator!=(const ModInt &lhs, const ModInt &rhs) { return lhs.x != rhs.x; }
  constexpr friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) += rhs; }
  constexpr friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) -= rhs; }
  constexpr friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) *= rhs; }
  constexpr friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) /= rhs; }
  friend Scanner &operator>>(Scanner &in, ModInt &n) {
    ll x;
    in >> x;
    n = ModInt(x);
    return in;
  }
  friend Printer &operator<<(Printer &out, const ModInt &n) { return out << n.x; }
};

constexpr int mod = 1e9 + 7;
using Z = ModInt<mod>;

int N;
Z ans, now;
std::unordered_map<int, Z> f;

void dfs1(int n) {
  if (f.count(n)) {
    return;
  }
  if (n <= 1) {
    f[n] = 1;
    return;
  }
  int l, r;
  for (int i = 1; i <= 30; i++) {
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i - 1) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i) - 1)) {
      l = (1 << i) - 1;
      r = (n - 1) - ((1 << i) - 1);
    }
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i + 1) - 1)) {
      l = (n - 1) - ((1 << i) - 1);
      r = (1 << i) - 1;
    }
  }
  dfs1(l);
  dfs1(r);
  f[n] = f[l] * f[r] / n;
}
void dfs3(int n, int m, int d, std::string s) {
  if (d == s.size()) {
    now *= f[m] * m;
    return;
  }
  int l, r;
  for (int i = 1; i <= 30; i++) {
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i - 1) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i) - 1)) {
      l = (1 << i) - 1;
      r = (n - 1) - ((1 << i) - 1);
    }
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i + 1) - 1)) {
      l = (n - 1) - ((1 << i) - 1);
      r = (1 << i) - 1;
    }
  }
  if (s[d] == 'L') {
    now *= f[r] / (n - m);
    dfs3(l, m, d + 1, s);
  } else {
    now *= f[l] / (n - m);
    dfs3(r, m, d + 1, s);
  }
}
void dfs2(int n, std::string s, Z &res) {
  if (n == 0) {
    return;
  }
  int l, r;
  for (int i = 1; i <= 30; i++) {
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i - 1) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i) - 1)) {
      l = (1 << i) - 1;
      r = (n - 1) - ((1 << i) - 1);
    }
    if ((n - 1) - ((1 << i) - 1) >= ((1 << i) - 1) && (n - 1) - ((1 << i) - 1) < ((1 << i + 1) - 1)) {
      l = (n - 1) - ((1 << i) - 1);
      r = (1 << i) - 1;
    }
  }
  now = 1;
  dfs3(N, n, 0, s);
  if (l != r) {
    ans += now;
  }
  Z tmp = now;
  if (n == 1) {
    res = tmp;
    return;
  }
  Z resl = 0, resr = 0;
  dfs2(l, s + "L", resl);
  if (l != r) {
    dfs2(r, s + "R", resr);
  } else {
    resr = resl;
  }
  res = resl + resr + tmp;
}

void run() {
  in >> N;
  ans = 0;
  dfs1(N);
  dfs2(N, "", ans);
  ans /= N;
  out << ans << "\n";
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