// =================================
//   author: memset0
//   date: 2019.08.08 08:27:06
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 70, M = 2e4 + 10, Q = 8e4 + 10, mod = 998244353;
int n, m, sum, out, lim;
int y[Q], p[Q], P[Q], V[Q], F[Q], G[Q], T[Q], rev[Q], w[Q], a[N][N], ans[N][M];

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int finv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * finv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

struct matrix {
    int a[N][N];
    void reset() { memset(a, 0, sizeof(a)); }
    matrix operator*(const matrix &rhs) const {
        matrix res; res.reset();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res.a[i][j] = (res.a[i][j] + (ll)a[i][k] * rhs.a[k][j]) % mod;
        return res;
    }
    int det() {
        int res = 1;
        for (int i = 0, j; i < n; i++) {
            for (j = i; j < n; j++) if (a[j][i]) break;
            if (j == n) return 0;
            if (i != j) res = dec(0, res), std::swap(a[i], a[j]);
            res = (ll)res * a[i][i] % mod;
            for (int d, j = i + 1; j < n; j++) {
                d = (ll)a[j][i] * finv(a[i][i]) % mod;
                for (int k = i; k < n; k++) sub(a[j][k], (ll)a[i][k] * d % mod);
            }
        }
        return res;
    }
} C, A[N];

void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

void polyinv(int *F, int *G, int len) {
    if (len == 1) { G[0] = finv(F[0]); return; }
    polyinv(F, G, len >> 1);
    int lim = len << 1, inv_lim = finv(lim), k = __builtin_ctz(lim);
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    memcpy(T, F, len << 2), memset(T + len, 0, len << 2), memset(G + len, 0, len << 2);;
    ntt(T, lim), ntt(G, lim);
    for (int i = 0; i < lim; i++) G[i] = (ll)G[i] * dec(2, (ll)G[i] * T[i] % mod) % mod;
    std::reverse(G + 1, G + lim), ntt(G, lim);
    for (int i = 0; i < lim; i++) G[i] = (ll)G[i] * inv_lim % mod;
    memset(G + len, 0, len << 2);
}

void lagrange(int *y, int *f) {
    static int g[N];
    for (int i = 0, d; i <= n; i++) {
        memset(g, 0, (n + 1) << 2), g[0] = d = 1;
        for (int j = 0; j <= n; j++) if (i != j) {
            d = (ll)d * (i - j + mod) % mod;
            for (int k = n; k; k--)
                g[k] = dec(g[k - 1], (ll)j * g[k] % mod);
            g[0] = (ll)g[0] * (mod - j) % mod;
        }
        d = finv(d);
        for (int j = 0; j <= n; j++) add(f[j], (ll)y[i] * g[j] % mod * d % mod);
    }
}

void main() {
    read(n), read(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            read(a[i][j]), A[1].a[j][i] = a[i][j];
        }
    for (int i = 0; i < n; i++) A[0].a[i][i] = 1;
    for (int i = 2; i < n; i++) A[i] = A[i - 1] * A[1];
    // for (int k = 0; k < n; k++) {
    //     for (int i = 0; i < n; i++) print(A[k].a[i], 0, n - 1);
    //     puts("");
    // }

    lim = 1; while (lim <= m) lim <<= 1;;
    for (int len = 1, wn; len <= lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i =  1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
    }
    for (int r = 0; r <= n; r++) {
        C.reset();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) C.a[i][j] = dec(0, A[1].a[i][j]);
            add(C.a[i][i], r);
        }
        // for (int i = 0; i < n; i++) print(C.a[i], 0, n - 1); puts("");
        y[r] = C.det();
    }
    // print(y, 0, n - 1);
    lagrange(y, p);
    // print(p, 0, n);

    for (int x = 0; x < n; x++) {
        memset(P, 0, lim << 2), P[0] = 1;
        memset(F, 0, (m + 1) << 2), memset(V, 0, n << 2);
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if ((i & x) == x && (j & x) == x) {
                        add(V[k], A[k].a[i][j]);
                    }
        }
        // printf("V: "), print(V, 0, n - 1);
        for (int k = 1; k <= m; k++) {
            for (int i = n; i; i--) P[i] = P[i - 1];
            P[0] = 0; ll d = P[n] * finv(p[n]) % mod;
            for (int i = 0; i <= n; i++) sub(P[i], d * p[i] % mod);
            for (int i = 0; i < n; i++) sub(F[k], (ll)P[i] * V[i] % mod);
            // printf("P[%d]: ", k), print(P, 0, n);
        }
        F[0] = 1, polyinv(F, G, lim);
        // printf(">>> %d\n", x), print(F, 1, m), print(G, 1, m), puts("");
        for (int k = 1; k <= m; k++)
            for (int y = 0; y < n; y++) 
                if ((x & y) == y) {
                    if ((__builtin_popcount(x) ^ __builtin_popcount(y)) & 1)
                        sub(ans[y][k], G[k]);
                    else
                        add(ans[y][k], G[k]);
                }
    }
    // for (int i = 0; i < n; i++) print(ans[i], 1, m);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) out ^= ans[i][j];
    }
    print(out, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}