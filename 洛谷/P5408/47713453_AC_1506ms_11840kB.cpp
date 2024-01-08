// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.17 23:58:22
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

const int N = 262144 << 2, mod = 167772161;
int n, w[N], rev[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct poly : std::vector<int> {
    using std::vector<int>::vector;
};

inline void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(a[i + j + len], w[j + len]);
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

inline poly operator*(const poly &f, const poly &g) {
    if ((ll)f.size() * g.size() < 1000) {
        poly h(f.size() + g.size() - 1);
        for (int i = 0; i < f.size(); i++)
            for (int j = 0; j < g.size(); j++)
                h[i + j] = (h[i + j] + (ll)f[i] * g[j]) % mod;
        return h;
    }
    static int a[N], b[N];
    static poly h; h.resize(f.size() + g.size() - 1);
    int lim = 1, inv_lim = 1, k = 0;
    while (lim < h.size()) lim <<= 1, ++k, inv_lim = inv_lim & 1 ? (inv_lim + mod) >> 1 : inv_lim >> 1;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    memcpy(a, &f[0], f.size() << 2), memset(a + f.size(), 0, (lim - f.size()) << 2);
    memcpy(b, &g[0], g.size() << 2), memset(b + g.size(), 0, (lim - g.size()) << 2);
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
    for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
    return h;
}

inline poly calc(int l, int r) {
    if (l == r) return poly{l, 1};
    int mid = (l + r) >> 1;
    return calc(l, mid) * calc(mid + 1, r);
}

void main() {
    read(n);
    int lim = 1, inv_lim = 1, k = 0;    
    while (lim < ((n << 1) + 1)) lim <<= 1, ++k, inv_lim = inv_lim & 1 ? (inv_lim + mod) >> 1 : inv_lim >> 1;
    for (int wn, len = 1; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    }
    poly ans = calc(0,  n - 1); print(ans, 0, ans.size() - 1);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}