#include <bits/stdc++.h>
using namespace std;

// begin MEM_IO_H

// forked from mcfx's code
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double llf;

#define RX                                        \
  x = 0;                                          \
  char t = P();                                   \
  while ((t < 48 || t > 57) && t != '-') t = P(); \
  bool f = 0;                                     \
  if (t == '-') t = P(), f = 1;                   \
  x = t - 48;                                     \
  for (t = P(); t >= 48 && t <= 57; t = P()) x = x * 10 + t - 48

#define RL                                                                  \
  if (t == '.') {                                                           \
    lf u = .1;                                                              \
    for (t = P(); t >= 48 && t <= 57; t = P(), u *= 0.1) x += u * (t - 48); \
  }                                                                         \
  if (f) x = -x

#define RU                          \
  x = 0;                            \
  char t = P();                     \
  while (t < 48 || t > 57) t = P(); \
  x = t - 48;                       \
  for (t = P(); t >= 48 && t <= 57; t = P()) x = x * 10 + t - 48

#define WI(S, T)                             \
  if (x) {                                   \
    if (x < 0) {                             \
      P('-'), x = -x;                        \
      if (x < 0) {                           \
        *this, (T)x;                         \
        return *this;                        \
      }                                      \
    }                                        \
    unsigned char s[S], c = 0;               \
    while (x) s[c++] = x % 10 + 48, x /= 10; \
    while (c--) P(s[c]);                     \
  } else                                     \
    P(48)

#define WL                          \
  if (y) {                          \
    lf t = 0.5;                     \
    for (int i = y; i--;) t *= 0.1; \
    if (x >= 0) x += t;             \
    else                            \
      x -= t, P('-');               \
    *this, (ll)(abs(x));            \
    P('.');                         \
    if (x < 0) x = -x;              \
    while (y--) {                   \
      x *= 10;                      \
      x -= floor(x * 0.1) * 10;     \
      P(((int)x) % 10 + 48);        \
    }                               \
  } else if (x >= 0)                \
    *this, (ll)(x + 0.5);           \
  else                              \
    *this, (ll)(x - 0.5);

#define WU(S)                                \
  if (x) {                                   \
    char s[S], c = 0;                        \
    while (x) s[c++] = x % 10 + 48, x /= 10; \
    while (c--) P(s[c]);                     \
  } else                                     \
    P(48)

constexpr bool IS(char x) { return x == 10 || x == 13 || x == ' '; }

template <typename T> struct FastRead {
  T P;
  inline FastRead &operator,(int &x) {
    RX;
    if (f) x = -x;
    return *this;
  }
  inline operator int() {
    int x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(ll &x) {
    RX;
    if (f) x = -x;
    return *this;
  }
  inline operator ll() {
    ll x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(char &x) {
    for (x = P(); IS(x); x = P())
      ;
    return *this;
  }
  inline operator char() {
    char x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(char *x) {
    char t = P();
    for (; IS(t) && ~t; t = P())
      ;
    if (~t) {
      for (; !IS(t); t = P()) *x++ = t;
    }
    *x++ = 0;
    return *this;
  }
  inline FastRead &operator,(std::string &x) {
    char t = P();
    for (; IS(t) && ~t; t = P())
      ;
    if (~t) {
      for (; !IS(t); t = P()) x += t;
    }
    return *this;
  }
  inline FastRead &operator,(lf &x) {
    RX;
    RL;
    return *this;
  }
  inline operator lf() {
    lf x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(llf &x) {
    RX;
    RL;
    return *this;
  }
  inline operator llf() {
    llf x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(unsigned &x) {
    RU;
    return *this;
  }
  inline operator unsigned() {
    unsigned x;
    *this, x;
    return x;
  }
  inline FastRead &operator,(ull &x) {
    RU;
    return *this;
  }
  inline operator ull() {
    ull x;
    *this, x;
    return x;
  }
  void file(const char *x) { P.file(x); }
};
struct Fwp {
  int p;
};
Fwp prec(int x) { return (Fwp){x}; }
template <typename T> struct FastWrite {
  T P;
  int p;
  inline FastWrite &operator,(int x) {
    WI(10, unsigned);
    return *this;
  }
  inline FastWrite &operator,(unsigned x) {
    WU(10);
    return *this;
  }
  inline FastWrite &operator,(ll x) {
    WI(19, ull);
    return *this;
  }
  inline FastWrite &operator,(ull x) {
    WU(20);
    return *this;
  }
  inline FastWrite &operator,(char x) {
    P(x);
    return *this;
  }
  inline FastWrite &operator,(const char *x) {
    while (*x) P(*x++);
    return *this;
  }
  inline FastWrite &operator,(const Fwp &x) {
    p = x.p;
    return *this;
  }
  inline FastWrite &operator,(lf x) {
    int y = p;
    WL;
    return *this;
  }
  inline FastWrite &operator()(lf x, int y) {
    WL;
    return *this;
  }
  inline FastWrite &operator,(llf x) {
    int y = p;
    WL;
    return *this;
  }
  inline FastWrite &operator()(llf x, int y) {
    WL;
    return *this;
  }
  void file(const char *x) { P.file(x); }
  void flush() { P.flush(); }
};
#ifdef LOCAL
struct Cg {
  inline char operator()() { return getchar(); }
  void file(const char *f) { freopen(f, "r", stdin); }
};
struct Cp {
  inline void operator()(char x) { putchar(x); }
  void file(const char *f) { freopen(f, "w", stdout); }
  void flush() { fflush(stdout); }
};
struct Cpr {
  inline void operator()(char x) { fputc(x, stderr); }
  void file(const char *f) { freopen(f, "w", stderr); }
  void flush() { fflush(stderr); }
};
template <typename T> struct Fd {
  FastWrite<T> *o;
  template <typename P> inline Fd &operator,(P x) {
    (*o), x, ' ';
    return *this;
    ;
  }
  ~Fd() { (*o), '\n'; }
};
template <typename T> struct Fds {
  FastWrite<T> *o;
  template <typename P> inline Fd<T> operator,(P x) {
    (*o), x, ' ';
    return (Fd<T>){o};
  }
};
FastWrite<Cpr> err;
Fds<Cpr> dbg{&err};
#else
#define BSZ 131072
struct Cg {
  char t[BSZ + 1], *o, *e;
  Cg() { e = o = t + BSZ; }
  inline char operator()() {
    if (o == e) t[fread(o = t, 1, BSZ, stdin)] = 0;
    return *o++;
  }
  void file(const char *f) { freopen(f, "r", stdin); }
};
struct Cp {
  char t[BSZ + 1], *o, *e;
  Cp() { e = (o = t) + BSZ; }
  inline void operator()(char p) {
    if (o == e) fwrite(o = t, 1, BSZ, stdout);
    *o++ = p;
  }
  void file(const char *f) { freopen(f, "w", stdout); }
  void flush() { fwrite(t, 1, o - t, stdout), o = t, fflush(stdout); }
  ~Cp() { fwrite(t, 1, o - t, stdout); }
};
#endif

FastRead<Cg> in;
FastWrite<Cp> out;
const char dl = '\n';
// end MEM_IO_H

const int N = 2e5 + 9;
int T, n, q, a[N], s[N], l, r, ans[N];
pair<int, int> que[N];
string str;
vector<tuple<int, int, int, int>> qry;
inline void add(int k) {
  for (; k <= n; k += k & -k) s[k] += 1;
}
inline int ask(int k) {
  int ans = 0;
  for (; k; k -= k & -k) ans += s[k];
  return ans;
}
int main() {
#ifdef memset0
  in.file("C.in");
#endif
  in, T;
  while (T--) {
		str = "";
    in, str, q;
    n = str.length();
    qry.clear();
    for (int i = 1; i <= n; i++) a[i] = str[i - 1] - '0';
    for (int d, l, r, i = 1; i <= q; i++) {
      in, d, l, r;
      qry.emplace_back(d, l, r, i);
    }
    l = 1, r = 0;
    for (int i = 1; i <= n; i++)
      if (a[i]) {
        que[++r] = make_pair(i, 1);
      }
    // cerr << l << " " << r << endl;
    if (r == 0) {
      for (int i = 1; i <= q; i++) {
        out, 0, dl;
      }
      continue;
    }
    while (l <= r) {
      auto [i, k] = que[l++];
      // cerr << ">> " << i << " " << k << endl;
      if (i - 1 >= 1 && !a[i - 1]) {
        que[++r] = make_pair(i - 1, k + 1);
        a[i - 1] = 1;
      }
      if (i + 1 <= n && !a[i + 1]) {
        que[++r] = make_pair(i + 1, k + 1);
        a[i + 1] = 1;
      }
    }
    sort(qry.begin(), qry.end());
    int p = 0;
    l = 1, r = n;
    fill(s, s + n + 5, 0);
    // cerr << "!!!!" << endl;
    for (int d = 1; d <= n; d++) {
      // cerr << "d = " << d << endl;
      while (l <= r && que[l].second == d) {
        add(que[l].first);
        l++;
      }
      while (p < qry.size() && get<0>(qry[p]) == d) {
        auto [d, l, r, i] = qry[p];
        ans[i] = ask(r) - ask(l - 1);
        p++;
      }
    }
    while (p < qry.size()) {
      auto [d, l, r, i] = qry[p];
      ans[i] = ask(r) - ask(l - 1);
      p++;
    }
    for (int i = 1; i <= q; i++) {
      out, ans[i], dl;
    }
  }
}