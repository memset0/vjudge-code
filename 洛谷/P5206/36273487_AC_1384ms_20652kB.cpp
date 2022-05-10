// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 07:22:47
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
inline char read() {
	static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
	static bool f; static char c;
	for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void print(T x, char c) { print(x), print(c); }

const int N = 1e5 + 10, mod = 998244353;
int n, m, opt;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

namespace sol1 {
int cnt;
std::unordered_set <int> set[N];

int main() {
    for (int i = 1, u, v; i < n; i++) read(u), read(v), set[u].insert(v);
    for (int i = 1, u, v; i < n; i++) read(u), read(v), cnt += set[u].count(v);
    return fpow(m, n - cnt);
}

} // end namespace sol1

namespace sol2 {
int k, f[N][2];
std::vector <int> G[N];

void dfs(int u, int fa = 0) {
    // printf("dfs %d %d | %d\n", u, fa, G[u].size());
    f[u][0] = 1, f[u][1] = k;
    for (auto v : G[u]) if (v != fa) {
        dfs(v, u);
        f[u][1] = sub(mul(f[u][0], f[v][1]), mul(f[u][1], sub(f[v][0], f[v][1])));
        f[u][0] = mul(f[u][0], sub(f[v][0], f[v][1]));
    }
}

int main() {
    if (m == 1) return fpow(n, n - 2);
    for (int i = 1, u, v; i < n; i++) read(u), read(v), G[u].push_back(v), G[v].push_back(u);
    k = mul(inv(dec(1, m)), mul(n, m)), dfs(1);
    // for (int i = 1; i <= n; i++) print(f[i][0], " \n"[i == n]);
    // for (int i = 1; i <= n; i++) print(f[i][1], " \n"[i == n]); 
    return mul(f[1][1], mul(inv(mul(n, n)), fpow(dec(1, m), n)));
}

} // end namespace sol2

namespace sol3 {
int tmp, fac[N], ifac[N], w[N << 2], rev[N << 2];

struct poly : std::vector <int> {
    using std::vector <int> ::vector;
    void in() { for (int i = 0; i < size(); i++) read(at(i)); }
    void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
} f, g;

inline int init(int len) {
    int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int wn, len = 1; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    } return lim;
}

void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
                a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
            }
}

inline poly operator * (const poly &f, const poly &g) {
    static int a[N << 2], b[N << 2]; poly h(f.size() + g.size() - 1);
    int lim = init(h.size()), inv_lim = inv(lim);
    for (int i = 0; i < lim; i++) a[i] = i < f.size() ? f[i] : 0;
    for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
    for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
    return h;
}

using ringo::inv;
inline poly inv(const poly &f) {
    static int a[N << 2], b[N << 2];
    poly g(1, inv(f[0]));
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        int lim = init(len << 1), inv_lim = inv(lim);
        for (int i = 0; i < lim; i++) a[i] = i < f.size() && i < len ? f[i] : 0;
        for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
        ntt(a, lim), ntt(b, lim);
        for (int i = 0; i < lim; i++) a[i] = mul(a[i], mul(b[i], b[i]));
        std::reverse(a + 1, a + lim), ntt(a, lim);
        for (int i = len >> 1; i < len; i++) g.push_back(dec(0, mul(a[i], inv_lim)));
    } g.resize(f.size()); return g;
}

inline poly ln(poly f) {
    poly g(f.size());
    for (int i = 1; i < f.size(); i++) g[i - 1] = mul(f[i], i);
    g = inv(f) * g, g.resize(f.size()), f[0] = 0;
    for (int i = 0; i < f.size() - 1; i++) f[i + 1] = mul(g[i], inv(i + 1));
    return f;
}

inline poly exp(const poly &f) {
    poly g(1, 1), h, t;
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        g.resize(len), h = ln(g), t.resize(len), h.resize(len);
        for (int i = 0; i < len; i++) h[i] = dec(i < f.size() ? f[i] : 0, h[i]);
        for (int i = 0; i < len; i++) t[i] = i < g.size() ? g[i] : 0;
        h[0] = sub(h[0], 1), h = h * t, g.resize(len);
        for (int i = len >> 1; i < len; i++) g[i] = h[i];
    } g.resize(f.size()); return g;
}

int main() {
    if (m == 1) return fpow(n, 2 * n - 4);
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
    g.resize(n + 1), tmp = mul(inv(dec(1, m)), mul(m, mul(n, n)));
    for (int i = 1; i <= n; i++) g[i] = mul(tmp, mul(ifac[i], fpow(i, i)));
    f = exp(g);
    return mul(inv(fpow(n, 4)), mul(fpow(dec(1, m), n), mul(fac[n], f[n])));
}

} // end namespace sol3

void main() {
    read(n), read(m), read(opt);
    if (opt == 0) print(sol1::main(), '\n');
    if (opt == 1) print(sol2::main(), '\n');
    if (opt == 2) print(sol3::main(), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), ringo::flush(), 0;
}