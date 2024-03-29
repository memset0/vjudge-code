// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
    while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
    static int buf[40];
    if (x == 0) { putc('0'); putc(c); return; }
    if (x < 0) putc('-'), x = -x;
    for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
    while (buf[0]) putc((char) buf[buf[0]--]);
    putc(c);
}

const int maxn = 500010, maxm = 200010;
int n, m, tn, ans = 1e9, b[maxn << 1];

struct edge {
    int l, r, len;
} a[maxn];
bool cmp(edge a, edge b) {
    return a.len < b.len;
}

struct node {
    int l, r, mid;
    int max, tag;
} p[maxn << 4];

void pushup(int u, int x) {
    p[u].tag += x;
    p[u].max += x;
}

void pushdown(int u) {
    if (p[u].tag) {
        if (p[u].l == p[u].r)
            return;
        pushup(u << 1, p[u].tag);
        pushup(u << 1 | 1, p[u].tag);
        p[u].tag = 0;
    }
}

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
    if (l == r) return;
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
}

void update(int u, int l, int r, int x) {
//	printf("update %d %d %d %d %d %d\n", u, x, l, r, p[u].l, p[u].r);
    pushdown(u);
    if (p[u].l == l && p[u].r == r) {
        pushup(u, x);
        return;
    }
    if (r <= p[u].mid) update(u << 1, l, r, x);
    else if (l > p[u].mid) update(u << 1 | 1, l, r, x);
    else {
        update(u << 1, l, p[u].mid, x);
        update(u << 1 | 1, p[u].mid + 1, r, x);
    }
    p[u].max = std::max(p[u << 1].max, p[u << 1 | 1].max);
}

int main() {
//	freopen("INPUT", "r", stdin);
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        read(a[i].l), read(a[i].r), a[i].len = a[i].r - a[i].l + 1;
    for (int i = 1; i <= n; i++)
        b[++tn] = a[i].l, b[++tn] = a[i].r;
    std::sort(b + 1, b + tn + 1);
    tn = std::unique(b + 1, b + tn + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i].l = std::lower_bound(b + 1, b + tn + 1, a[i].l) - b;
        a[i].r = std::lower_bound(b + 1, b + tn + 1, a[i].r) - b;
    }
    std::sort(a + 1, a + n + 1, cmp);
    build(1, 1, tn);
    int j = 1;
    for (int i = 1; i <= n; i++) {
        update(1, a[i].l, a[i].r, 1);
        while (j <= n && p[1].max >= m) {
            ans = std::min(ans, a[i].len - a[j].len);
//			printf("%d %d %d\n", i, j, n);
            update(1, a[j].l, a[j].r, -1);
            j++;
        }
    }
    print(ans == 1e9 ? -1 : ans, '\n');
    return 0;
}