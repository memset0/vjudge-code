// =================================
//   author: memset0
//   date: 2019.07.01 08:32:46
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

const int N = 1e6 + 1e5, mod = 998244353;
int n, lim = 1, a[N], f[N];

inline int half(int x) { return x & 1 ? (x + mod) >> 1 : x >> 1; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void fwt(int *a) {
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = a[i + j + len];
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

void ifwt(int *a) {
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = a[i + j + len];
                a[i + j] = half(inc(x, y)), a[i + j + len] = half(dec(x, y));
            }
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        ++f[0], f[a[i]] += 2;
        while (lim <= a[i]) lim <<= 1;
    }
    // print(f, 0, lim - 1);
    fwt(f);
    // print(f, 0, lim - 1);
    for (int i = 0; i < lim; i++) {
        int now = half(dec(f[i], n));
        f[i] = mul(fpow(3, half(inc(n, now))), fpow(mod - 1, half(dec(n, now))));
    }
    // print(f, 0, lim - 1);
    ifwt(f);
    // print(f, 0, lim - 1);
    print(dec(f[0], 1), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}