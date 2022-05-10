// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.22 12:38:19
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

const int N = 2e5 + 10, mod = 1e9 + 9;
int n, m, ans, f[N], g[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int C(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }

void main() {
    read(n), read(m);
    f[0] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
    for (int k = 0, p = m - (m >> 1); (1 << (k + 1)) <= n - m; k++) {
        for (int i = 0; i <= n - m; i++) g[i] = f[i];
        for (int u = 1, delta; (delta = (u << 1) * (1 << k)) <= n - m && (u << 1) <= p; u++) {
            // printf("k=%d u=%d delta=%d\n", k, u, delta);
            for (int i = n - m; i >= delta; i--)
                f[i] = inc(f[i], mul(g[i - delta], C(p, u << 1)));
        }
    }
    // print(f, 0, n - m, "f");
    for (int i = 1; i <= n - m; i++) f[i] = inc(f[i], f[i - 1]);
    // print(f, 0, n - m, "f");
    for (int i = 0, p = (m >> 1); i <= n - m; i++) {
        ans = inc(ans, mul(f[n - m - i], C(i + p - 1, p - 1)));
        // printf("%d : %d %d\n", i, f[n - m - i], C(i + p - 1, p - 1));
    }
    // printf(">> %d %d\n", C(n, m), ans);
    print(dec(C(n, m), ans), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}