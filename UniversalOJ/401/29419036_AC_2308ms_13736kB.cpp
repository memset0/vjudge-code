// =================================
//   author: memset0
//   date: 2019.03.19 10:06:14
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

const int N = 5e4 + 10, mod = 998244353;
int T, n, m, ans, error_flag;
int a[N], f[N], g[N], L[N], R[N], w[N << 2], rev[N << 2];
std::vector <int> vet, G[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

int init(int len) {
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

struct poly : std::vector <int> {
    using std::vector <int> :: vector;
    void out() { for (size_t i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
    friend inline poly operator * (const poly &f, const poly &g) {
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
};

void solve(int l, int r) {
    if (l == r) {
        if (l == 1 || l == 2) { f[l] = 2; return; }
        // printf("%d => %d * %d | %d * %d | %d * %d | %d : %d * %d\n", l,
        // 	f[l], l - 2,
        // 	(l << 1) - 4, f[l - 1],
        // 	l - 1, f[l - 1],
        // 	l & 1 ^ 1, (l >> 1) - 1, mul(f[l >> 1], f[l >> 1])
        // );
        f[l] = dec(mul(f[l], l - 2), mul((l << 1) - 4, f[l - 1]));
        f[l] = sub(f[l], mul(l - 1, f[l - 1]));
        if (l & 1 ^ 1) f[l] = dec(f[l], mul((l >> 1) - 1, mul(f[l >> 1], f[l >> 1])));
        return;
    }
    int mid = (l + r) >> 1, len = mid - l + 1;
    solve(l, mid);
    poly a, b;
    for (int i = 1; i <= (len << 1); i++) a.push_back(f[i]);
    for (int i = l; i <= mid; i++) b.push_back(f[i]);
    poly c = a * b;
    // printf("solve %d %d -> %d | %d %d %d\n", l, r, mid, c.size(), (len << 1) - 1, len);
    // for (int i = 0; i < a.size(); i++) print(a[i], ' '); puts("");
    // for (int i = 0; i < b.size(); i++) print(b[i], ' '); puts("");
    // for (int i = 0; i < c.size(); i++) print(c[i], ' '); puts("");
    if (l == 1) {
        int tmp = (mod + 1) >> 1;
        for (int i = 1; i <= len; i++) c[(i << 1) - 2] = sub(c[(i << 1) - 2], mul(f[i], f[i]));
        for (int i = 0; i < len; i++) c[i + len - 1] = mul(c[i + len - 1], tmp);
    }
    // for (int i = 0; i < c.size(); i++) print(c[i], ' '); puts("");
    // for (int i = 0; i <= m; i++) print(f[i], " \n"[i == m]);
    for (int i = 0; i < len; i++) f[i + mid + 1] = sub(c[i + len - 1], f[i + mid + 1]);
    // for (int i = 0; i <= m; i++) print(f[i], " \n"[i == m]);
    // for (int i = 0; i < len; i++) printf("[%d %d %d] ", i + len - 1, i + mid + 1, c[i + len - 1]); puts("");
    solve(mid + 1, r);
}

void main() {
    read(T), read(n);
    for (m = 1; m < n; m <<= 1);
    f[0] = 1;
    solve(1, m);
    // g[0] = 1, g[1] = 2;
    // for (int i = 2; i <= m; i++) {
    // 	g[i] = mul(i - 1, g[i - 1]);
    // 	for (int j = 2; j <= i - 2; j++) g[i] = sub(g[i], mul(mul(g[j], g[i - j]), i - j - 1));
    // }
    // for (int i = 0; i <= m; i++) print(f[i], " \n"[i == m]);
    // for (int i = 0; i <= m; i++) print(g[i], " \n"[i == m]);
    while (T--) {
        error_flag = false, vet.clear(), ans = 1;
        for (int i = 1; i <= n; i++) read(a[i]), G[i].clear();
        if (a[n] != n) error_flag = 1;
        for (int i = 1; i <= n && !error_flag; i++) {
            L[i] = i - a[i] + 1, R[i] = i;
            for (int j = vet.size() - 1; j >= 0 && !error_flag; j--) {
                if (L[i] <= R[vet[j]]) {
                    if (L[i] <= L[vet[j]]) {
                        G[i].push_back(vet[j]);
                        vet.pop_back();
                    } else error_flag = true;
                } else break;
            }
            vet.push_back(i);
        }
        if (error_flag) puts("0");
        else {
            for (int i = 1; i <= n; i++) ans = mul(ans, f[G[i].size()]);
            print(ans, '\n');
        }
    }
}

} signed main() { return ringo::main(), 0; }