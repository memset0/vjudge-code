// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.07 18:27:51
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

const int N = 71, K = 1 << 12, mod = 998244353;
int n, m, l, lim, a[N][N], ans[K], f[N][N][K];
char s[15];

inline int half(int x) { return x & 1 ? (x + mod) >> 1 : x >> 1; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

void fwt(int a[]) {
    for (int len = 1, k = 1; len < lim; len <<= 1, ++k)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++)
                if (s[k] == '&') a[i + j] = inc(a[i + j], a[i + j + len]);
                else if (s[k] == '|') a[i + j + len] = inc(a[i + j + len], a[i + j]);
                else { int x = a[i + j], y = a[i + j + len]; a[i + j] = inc(x, y); a[i + j + len] = dec(x, y); }
}

void ifwt(int a[]) {
    for (int len = 1, k = 1; len < lim; len <<= 1, ++k)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++)
                if (s[k] == '&') a[i + j] = dec(a[i + j], a[i + j + len]);
                else if (s[k] == '|') a[i + j + len] = dec(a[i + j + len], a[i + j]);
                else { int x = a[i + j], y = a[i + j + len]; a[i + j] = half(inc(x, y)); a[i + j + len] = half(dec(x, y)); }
}

int gauss(int a[N][N], int n) {
    int res = 1;
    for (int i = 1, j; i <= n; i++) {
        for (j = i; j <= n; j++) if (a[j][i]) break;
        if (j > n) return 0;
        if (i != j) res = mod - res, std::swap(a[i], a[j]);
        for (int j = i + 1; j <= n; j++) {
            int tmp = mul(a[j][i], inv(a[i][i]));
            for (int k = i; k <= n; k++) a[j][k] = dec(a[j][k], mul(tmp, a[i][k]));
        }
    }
    for (int i = 1; i <= n; i++) res = mul(res, a[i][i]);
    return res;
}

void main() {
    read(n), read(m), scanf("%s", s + 1);
    l = strlen(s + 1), lim = 1 << l;
    for (int i = 1, u, v, w; i <= m; i++) {
        read(u), read(v), read(w);
        --f[u][v][w], --f[v][u][w];
        ++f[u][u][w], ++f[v][v][w];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fwt(f[i][j]);
    for (int w = 0; w < (1 << l); w++) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                a[i][j] = f[i][j][w];
        ans[w] = gauss(a, n - 1);
    }
    ifwt(ans);
    for (int i = (1 << l) - 1; i >= 0; i--)
        if (ans[i]) { print(i, '\n'); return; }
    print(-1, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}