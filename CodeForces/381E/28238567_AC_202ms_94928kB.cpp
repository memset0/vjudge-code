// =================================
//   author: memset0
//   date: 2019.03.29 09:07:28
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

const int N = 1e6 + 10;
int n, m; char a[N];

struct info {
    int L, S, R;
    inline info() {}
    inline info(int l, int s, int r) { L = l, R = r, S = s; }
    inline info(char c) { c == '(' ? (L = 1, R = S = 0) : (R = 1, L = S = 0); }
    friend inline info operator + (const info &a, const info &b) {
        int min = std::min(a.L, b.R);
        return info(a.L + b.L - min, a.S + b.S + min, a.R + b.R - min);
    }
};

struct node {
    int l, r, mid;
    info x;
} p[N << 2];

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
    if (l == r) p[u].x = info(a[l]);
    else {
        build(u << 1, l, p[u].mid);
        build(u << 1 | 1, p[u].mid + 1, r);
        p[u].x = p[u << 1].x + p[u << 1 | 1].x;
    }
    // printf(">> %d[%d %d] => %d %d %d\n", u, l, r, p[u].x.L, p[u].x.S, p[u].x.R);
}

info query(int u, int l, int r) {
	if (l == p[u].l && r == p[u].r) return p[u].x;
	if (r <= p[u].mid) return query(u << 1, l, r);
	if (l > p[u].mid) return query(u << 1 | 1, l, r);
	return query(u << 1, l, p[u].mid) + query(u << 1 | 1, p[u].mid + 1, r);
}

void main() {
    scanf("%s", a + 1), n = strlen(a + 1), read(m);
    build(1, 1, n);
    for (int i = 1, l, r; i <= m; i++) {
		read(l), read(r);
		print(query(1, l, r).S << 1, '\n');
	}
}

} signed main() { return ringo::main(), 0; }