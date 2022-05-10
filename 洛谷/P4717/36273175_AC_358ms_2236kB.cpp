// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.24 08:51:38
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
	x = 0; register char c = getchar(); register bool f = 0;
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

const int N = (1 << 17), mod = 998244353;
int n, lim, inv2, a[N], b[N], c[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int fpow(int a,int b) { int s = 1; for(; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline void _or(int &a, int &b) { b = sub(a, b); }
inline void i_or(int &a, int &b) { b = dec(b, a); }
inline void _and(int &a, int &b) { a = sub(a, b); }
inline void i_and(int &a, int &b) { a = dec(a, b); }
inline void _xor(int &a, int &b) { int x = a, y = b; a = sub(x, y), b = dec(x, y); }
inline void i_xor(int &a, int &b) { int x = a, y = b; a = mul(sub(x, y), inv2), b = mul(dec(x, y), inv2); }

void fwt(int *a, void func(int&, int&)) {
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++)
                func(a[i + j], a[i + j + len]);
}

void main() {
    read(n), lim = 1 << n; inv2 = (mod + 1) >> 1;
    for (int i = 0; i < lim; i++) read(a[i]);
    for (int i = 0; i < lim; i++) read(b[i]);
    fwt(a, _or), fwt(b, _or);
    for (int i = 0; i < lim; i++) c[i] = mul(a[i], b[i]);
    fwt(a, i_or), fwt(b, i_or), fwt(c, i_or);
    for (int i = 0; i < lim; i++) print(c[i], " \n"[i == lim - 1]);
    fwt(a, _and), fwt(b, _and);
    for (int i = 0; i < lim; i++) c[i] = mul(a[i], b[i]);
    fwt(a, i_and), fwt(b, i_and), fwt(c, i_and);
    for (int i = 0; i < lim; i++) print(c[i], " \n"[i == lim - 1]);
    fwt(a, _xor), fwt(b, _xor);
    for (int i = 0; i < lim; i++) c[i] = mul(a[i], b[i]);
    fwt(a, i_xor), fwt(b, i_xor), fwt(c, _xor);
    int tmp = fpow(lim, mod - 2);
    for (int i = 0; i < lim; i++) c[i] = mul(c[i], tmp);
    for (int i = 0; i < lim; i++) print(c[i], " \n"[i == lim - 1]);
}

} signed main() { return ringo::main(), 0; }