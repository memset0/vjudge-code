// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.10 12:56:28
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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
inline void read(double &x) { scanf("%lf", &x); }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 510;
int n;
double alpha, multi;
double a[N], k[N], b[N], r[N], h[N], _a[N], _b[N], _c[N];

inline double f(double x) {
    double A, B, C, X, y = 0;
    for (int i = 1; i <= n; i++) y = std::max(y, r[i] * r[i] - a[i] * a[i] - x * x + 2 * a[i] * x);
    for (int i = 1; i < n; i++) {
        A = _a[i], B = _b[i] + 2 * x, C = _c[i] - x * x, X = -B / A / 2;
        if (a[i] <= X && X <= a[i + 1]) y = std::max(y, (4 * A * C - B * B) / A / 4);
    } return sqrt(y);
}

inline double simpson(double l, double r) {
    return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2)) / 6;
}

double asr(double l, double r, double eps, double ans) {
    double mid = (l + r) / 2, L = simpson(l, mid), R = simpson(mid, r);
    if (fabs(L + R - ans) < 15 * eps) return L + R + (L + R - ans) / 15;
    return asr(l, mid, eps / 2, L) + asr(mid, r, eps / 2, R);
}

void main() {
    read(n), read(alpha), multi = 1 / tan(alpha), ++n, r[n] = 0;
    for (int i = 1; i <= n; i++) read(h[i]);
    for (int i = 1; i < n; i++) read(r[i]);
    for (int i = 1; i <= n; i++) a[i] = a[i - 1] + h[i];
    for (int i = 1; i <= n; i++) a[i] *= multi;
    double L = a[1] - r[1], R = a[1] + r[1];
    for (int i = 2; i <= n; i++) L = std::min(L, a[i] - r[i]), R = std::max(R, a[i] + r[i]);
    for (int i = 1; i < n; i++) {
        k[i] = (r[i] - r[i + 1]) / (a[i] - a[i + 1]);
        b[i] = (a[i] * r[i + 1] - a[i + 1] * r[i]) / (a[i] - a[i + 1]);
		_a[i] = k[i] * k[i] - 1, _b[i] = 2 * k[i] * b[i], _c[i] = b[i] * b[i];
    }
    printf("%.2lf\n", asr(L, R, 1e-3, simpson(L, R)) * 2);
}

} signed main() { return ringo::main(), 0; }