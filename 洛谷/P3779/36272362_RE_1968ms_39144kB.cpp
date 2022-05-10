// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.23 19:15:25
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

const int N = 2e5 + 10, M = 21;
int T, n, m;

namespace fft_solution {

const int L = 8e5 + 10;
const double pi = acos(-1);
int rev[L];
double f[L], g[L];

struct complex {
    double x, y;
    inline complex operator+(const complex &o) { return { x + o.x, y + o.y }; }
    inline complex operator-(const complex &o) { return { x - o.x, y - o.y }; }
    inline complex operator*(const complex &o) { return { x * o.x - y * o.y, x * o.y + y * o.x }; }
} w1[L], w2[L];

inline void fft(complex *a, int lim, complex *w) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                complex x = a[i + j], y = w[j + len] * a[i + j + len];
                a[i + j] = x + y, a[i + j + len] = x - y;
            }
}

inline void mul(double *f, double *g, double *h, int n, int m) {
    static complex a[L], b[L];
    int len = n + m - 1, lim = 1, k = 0;
    while (lim < len) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int len = 1; len < lim; len <<= 1) {
        w1[len] = w2[len] = { 1, 0 };
        complex wn1 = { cos(pi / len),  sin(pi / len) };
        complex wn2 = { cos(pi / len), -sin(pi / len) };
        for (int i = 1; i < len; i++) {
            w1[i + len] = w1[i + len - 1] * wn1;
            w2[i + len] = w2[i + len - 1] * wn2;
        }
    }
    // printf(">> mul n=%d m=%d len=%d lim=%d k=%d\n", n, m, len, lim, k);
    // for (int i = 0; i < n; i++) printf("%.2lf ", f[i]); putchar('\n');
    // for (int i = 0; i < m; i++) printf("%.2lf ", g[i]); putchar('\n');
    for (int i = 0; i < lim; i++) {
        a[i] = { i < n ? f[i] : 0, 0 };
        b[i] = { i < m ? g[i] : 0, 0 };
    }
    fft(a, lim, w1), fft(b, lim, w1);
    for (int i = 0; i < lim; i++) a[i] = a[i] * b[i];
    fft(a, lim, w2);
    for (int i = 0; i < len; i++) h[i] = a[i].x / lim;
    // for (int i = 0; i < len; i++) printf("%.2lf ", h[i]); putchar('\n');
}

inline void fpow(double *a, int b, int n, double *s) {
    int m = 1; s[0] = 1;
    for (; b; b >>= 1, mul(a, a, a, n, n), n = (n << 1) - 1)
        if (b & 1) mul(s, a, s, m, n), m = n + m - 1;
}

void main(int n, int m) {
    for (int i = 0; i < n; i++) f[i] = 1.0 / n;
    fpow(f, m, n, g);
    // printf(">> %d\n", (n - 1) * m);
    for (int i = 1; i <= (n - 1) * m; i++) g[i] += g[i - 1];
    for (int i = 1, a, b; i <= 10; i++) read(a), read(b), printf("%.6lf\n", g[b] - (a == 0 ? 0 : g[a - 1]));
}

} // fft_solution

namespace simpson_solution {

void main(int n, int m) {

}

} // simpson_solution

void main() {
    for (read(T); T--; ) {
        read(n), read(m);
        fft_solution::main(n, m);
    }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}