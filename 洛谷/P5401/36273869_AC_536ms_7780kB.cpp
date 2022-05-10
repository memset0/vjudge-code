// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.15 10:39:33
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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

const int N = 4e5 + 10, mod =  998244353;
int n, m, d, k, ans, lim = 1, inv_lim;
int a[N], b[N], c[N], w[N], rev[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int C(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline void ntt(int *a) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

inline int F(int d) {
    if (d == 0) return 1;
    return mul((n - 2 * m) & 1 ? mod - 1 : 1, C(d - 1, n - m * 2));
}

void main() {
    read(d), read(n), read(m);
    if (n < (m << 1)) { puts("0"); return; }
    if (d <= (n - (m << 1) + 1)) { print(fpow(d, n), '\n'); return; }
    while (lim <= (d << 1)) lim <<= 1, ++k; inv_lim = inv(lim);
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i < lim; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i < lim; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i < lim; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int wn, len = 1; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    }
    for (int i = 0; i <= d; i++) a[i] = mul(fpow(dec(inc(i, i), d), n), ifac[d - i]);
    for (int i = 0; i <= d; i++) b[i] = mul(fpow(2, d - i), mul(ifac[d - i], F(i)));
    // print(a, 0, d, "a"), print(b, 0, d, "b");
    ntt(a), ntt(b);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a);
    for (int i = 0; i <= (d << 1); i++) c[i] = mul(a[i], inv_lim);
    for (int i = d; i <= (d << 1); i++) ans = inc(ans, mul(c[i], mul(ifac[i - d], i & 1 ? mod - 1 : 1)));
    // print(c, 0, d << 1, "c");
    print(mul(ans, mul(mul(fac[d], d & 1 ? mod - 1 : 1), inv(fpow(2, d)))), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}