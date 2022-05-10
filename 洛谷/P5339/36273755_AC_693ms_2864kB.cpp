// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.12 18:34:48
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

const int N = 1e5 + 10, mod = 998244353;
int rev[N], w[N], fac[N], ifac[N];
int n, m, k, a, b, c, d, ans, lim = 1, inv_lim;
int A[N], B[N], C[N], D[N], F[N], G[N], T1[N], T2[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int binom(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

inline void mul(int *a, int *b, int *c) {
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
    for (int i = 0; i < lim; i++) c[i] = mul(a[i], inv_lim);
}

void main() {
    read(n), read(a), read(b), read(c), read(d);
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    while (lim <= (a + b + c + d + 4)) lim <<= 1, ++k; inv_lim = inv(lim);
    for (int i = 2; i < lim; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i < lim; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i < lim; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int len = 1, wn; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    }
    
    for (int k = 0; k <= (n >> 2) && k <= a && k <= b && k <= c && k <= d; k++) {
        for (int i = 0; i < lim; i++) {
            A[i] = i <= a - k ? ifac[i] : 0;
            B[i] = i <= b - k ? ifac[i] : 0;
            C[i] = i <= c - k ? ifac[i] : 0;
            D[i] = i <= d - k ? ifac[i] : 0;
        }
        mul(A, B, F), mul(F, C, F), mul(F, D, F);
        G[k] = mul(mul(F[n - (k << 2)], fac[n - (k << 2)]), binom(n - k * 3, k));
        ans = inc(ans, mul(G[k], k & 1 ? mod - 1 : 1));
        // printf("%d f=%d g=%d\n", k, mul(F[n - (k << 2)], fac[n - (k << 2)]), G[k]);
    }
    print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
#endif
    return ringo::main(), 0;
}