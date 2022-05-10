// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.22 17:17:41
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define poly std::vector <int>
#define for_each(i, a) for (int i = 0, __lim = a.size(); i < __lim; ++i)
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
inline void print(const poly &a) { for_each(i, a) print(a[i], " \n"[i == __lim - 1]); }
inline void read(poly &a, int n) { for (int i = 0, x; i < n; i++) read(x), a.push_back(x); }

const int N = 1e5 + 10, mod = 998244353;

namespace poly_namespace {
    const int M = N << 3, SIZE = sizeof(int);
    int w[M], rev[M];

    inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
    inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
	inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
    inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
    inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

    inline poly resize(poly f, int n) { return f.resize(n), f; }
    inline poly operator + (poly f, int a) { f[0] = sub(f[0], a); return f; }
    inline poly operator + (int a, poly f) { f[0] = sub(a, f[0]); return f; }
    inline poly operator - (poly f, int a) { f[0] = dec(f[0], a); return f; }
    inline poly operator - (int a, poly f) { for_each(i, f) f[i] = dec(0, f[i]); f[0] = sub(a, f[0]); return f; }
    inline poly operator * (poly f, int a) { for_each(i, f) f[i] = (ll)f[i] * a % mod; return f; }
    inline poly operator * (int a, poly f) { for_each(i, f) f[i] = (ll)f[i] * a % mod; return f; }

    inline poly operator + (poly f, const poly &g) {
        f.resize(std::max(f.size(), g.size()));
        for_each(i, f) f[i] = sub(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0);
        return f;
    }
    inline poly operator - (poly f, const poly &g) {
        f.resize(std::max(f.size(), g.size()));
        for_each(i, f) f[i] = dec(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0);
        return f;
    }

    namespace cipolla_namespace {
        int t, sqr_w;
        typedef std::pair <int, int> pair;
        inline pair operator * (const pair &a, const pair &b) {
            return std::make_pair(((ll)a.first * b.first + (ll)a.second * b.second % mod * sqr_w) % mod,
                ((ll)a.first * b.second + (ll)a.second * b.first) % mod);
        }
        int cipolla(int x) {
            do t = rand() % mod; while (fpow(sqr_w = dec((ll)t * t % mod, x), (mod - 1) >> 1) != mod - 1);
            pair s = std::make_pair(1, 0), a = std::make_pair(t, 1);
            for (int b = (mod + 1) >> 1; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
            return std::min(s.first, mod - s.first);
        }
    } using cipolla_namespace::cipolla;

    void ntt(int *a, int lim) {
        for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
        for (int len = 1; len < lim; len <<= 1)
            for (int i = 0; i < lim; i += (len << 1))
                for (int j = 0; j < len; j++) {
                    int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
                    a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
                }
    }

    int init(int len) {
        int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
        for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        return lim;
    }
    void main_init() {
        static int plen=1;
        for (int len = plen, wn; (len << 1) < M; len <<= 1,plen<<=1) {
            wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
            for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
        }
    }
	
    inline poly operator * (poly f, const poly &g) {
        static int a[M], b[M];
        int lim = init(f.size() + g.size() - 1), inv_lim = inv(lim);
        memset(&a[f.size()], 0, (lim - f.size()) * SIZE); for_each(i, f) a[i] = f[i];
        memset(&b[g.size()], 0, (lim - g.size()) * SIZE); for_each(i, g) b[i] = g[i];
        ntt(a, lim), ntt(b, lim);
        for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
        std::reverse(a + 1, a + lim), ntt(a, lim); f.resize(f.size() + g.size() - 1);
        for_each(i, f) f[i] = (ll)a[i] * inv_lim % mod; return f;
    }

    inline poly inv(const poly &f) {
        static int a[M], b[M];
        poly g(1, inv(f[0]));
        for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
            int lim = init(len << 1), inv_lim = inv(lim);
            memset(&a[len], 0, len * SIZE); for (int i = 0; i < len; i++) a[i] = i < f.size() ? f[i] : 0;
            memset(&b[len], 0, len * SIZE); for (int i = 0; i < len; i++) b[i] = i < g.size() ? g[i] : 0;
            ntt(a, lim), ntt(b, lim);
            for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
            std::reverse(a + 1, a + lim), ntt(a, lim), g.resize(len);
            for_each(i, g) g[i] = dec(sub(g[i], g[i]), (ll)a[i] * inv_lim % mod);
        } return g.resize(f.size()), g;
    }

    inline poly sqrt(const poly &f) {
        poly g(1, cipolla(f[0]));
        for (int len = 2; (len >> 1) < f.size(); len <<= 1)
            g = resize(resize(resize(g * g, len) + f, len) * inv(resize(2 * g, len)), len);
        return g.resize(f.size()), g;
    }

    inline poly deri(const poly &f) {
        poly g(f.size());
        for (int i = 0; i < f.size() - 1; i++) g[i] = (ll)(i + 1) * f[i + 1] % mod;
        return g;
    }

    inline poly inte(const poly &f) {
        poly g(f.size());
        for (int i = 0; i < f.size() - 1; i++) g[i + 1] = (ll)inv(i + 1) * f[i] % mod;
        return g;
    }

    inline poly ln(const poly &f) { return inte(resize(deri(f) * inv(f), f.size())); }
    inline poly exp(const poly &f) {
        poly g(1, 1);
        for (int len = 2; (len >> 1) < f.size(); len <<= 1)
            g = resize(g * (1 - ln(resize(g, len)) + resize(f, len)), len);
        return g.resize(f.size()), g;
    }

	inline poly rever(poly f) { std::reverse(f.begin(), f.end()); return f; }
	inline poly model(const poly &f, const poly &g) {
		int len = f.size() - g.size() + 1;
		poly q = rever(resize(resize(rever(f), len) * inv(resize(rever(g), len)), len));
		poly r = resize(f - q * g, g.size() - 1); return r;
	}

    inline poly fpow(poly a, int b) {
        int n = a.size(); poly s(1, 1);
        for (; b; b >>= 1, a = resize(a * a, n))
            if (b & 1) s = resize(s * a, n);
        return s;
    }
} using namespace poly_namespace;

int n, x[N], y[N], z[N];
poly V[N << 2];

void build(int u, int l, int r) {
	if (l == r) { V[u].push_back(dec(0, x[l])), V[u].push_back(1); return; }
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	V[u] = V[u << 1] * V[u << 1 | 1];
}

void MPE(int u, int l, int r, const poly &U) {
	if (l == r) { z[l] = (ll)y[l] * inv(U[0]) % mod; return; }
	int mid = (l + r) >> 1;
	MPE(u << 1, l, mid, model(U, V[u << 1]));
	MPE(u << 1 | 1, mid + 1, r, model(U, V[u << 1 | 1]));
}

poly FIP(int u, int l, int r) {
	if (l == r) { return poly(1, z[l]); }
	int mid = (l + r) >> 1;
	return FIP(u << 1, l, mid) * V[u << 1 | 1] + FIP(u << 1 | 1, mid + 1, r) * V[u << 1];
}

void main() {
	read(n);
	for (int i = 0; i < n; i++) read(x[i]), read(y[i]);
	build(1, 0, n - 1), MPE(1, 0, n - 1, deri(V[1])), print(FIP(1, 0, n - 1));
}

} signed main() { return ringo::main_init(), ringo::main(), 0; }