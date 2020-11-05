// =================================
//   author: memset0
//   date: 2019.07.20 18:22:18
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 4e6 + 10, mod = 1004535809;
int n, l, tn, tm, ans = 1;
int a[N], f[N], g[N], h[N], w[N], rev[N], fac[N], ifac[N];

void setup(int *a, int &l, int n) { ++a[n], l = std::max(l, n); }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void init_fac(int n) {
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
}

void ntt(int *a, int l) {
    for (int i = 0; i < l; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < l; len <<= 1)
        for (int i = 0; i < l; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(a[i + j + len], w[j + len]);
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

void mul(int *a, int *b, int *c, int n, int m, int &l) {
    l = 1; int k = 0; while (l < n + m - 1) l <<= 1, ++k;
    for (int i = 0; i < l; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int wn, len = 1; len < l; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    } int inv_l = inv(l);
    ntt(a, l), ntt(b, l);
    for (int i = 0; i < l; i++) c[i] = mul(a[i], b[i]);
    std::reverse(c + 1, c + l), ntt(c, l);
    for (int i = 0; i < l; i++) c[i] = mul(c[i], inv_l);
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    init_fac(n + a[1]);
    for (int i = 1; i <= n; i++) {
        ans = mul(ans, mul(fac[a[i]], ifac[a[i] + n - i]));
        setup(f, tn, a[i] - i + n);
        setup(g, tm, -a[i] + i + a[1]);
        // printf("%d << %d %d : %d %d\n", ans, a[i], a[i] + n - i, fac[a[i]], mul(ifac[a[i] + n - i], fac[a[i] + n - i]));
    }
    mul(f, g, h, tn + 1, tm + 1, l);
    for (int i = 1, d = n + a[1]; i + d < l; i++) {
        // if (h[i + d]) printf("%d %d : %d\n", i, i + d, h[i + d]);
        ans = mul(ans, fpow(i, h[i + d]));
    }
    print(ans, '\n');
}

} signed main() {
#ifdef memset0
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}
