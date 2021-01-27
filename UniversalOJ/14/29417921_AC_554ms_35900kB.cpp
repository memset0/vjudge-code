// =================================
//   author: memset0
//   date: 2019.06.23 16:00:36
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 5e5 + 10;
std::vector<int> edge;
std::pair<int, int> did[N];
int n, m, cnt, now, ins[N], fa[N], siz[N], ans[N];

struct query {
    int c, x, y;
} qry[N];

inline int get() { return cnt == n - 1 ? now : 0; }
inline int find(int x) { return fa[x] == x ? x : find(fa[x]); }

inline void link(int u, int v) {
    // printf("   link %d %d\n", u, v);
    if (siz[u] > siz[v]) std::swap(u, v);
    fa[u] = v;
    for (int t = v; ; t = fa[t]) { siz[t] += siz[u]; if (t == fa[t]) break; }
}

inline void cut(int u, int v) {
    // printf("   cut %d %d\n", u, v);
    if (fa[v] == u) std::swap(u, v);
    fa[u] = u;
    for (int t = v; ; t = fa[t]) { siz[t] -= siz[u]; if (t == fa[t]) break; }
}

inline void append(int i, int u, int v) {
    // printf(">> append %d => %d %d\n", i, u, v);
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        link(fu, fv), did[i] = std::make_pair(fu, fv);
        ins[i] = 1, ++cnt, now += i;
    }
    edge.push_back(i);
}

inline void remove() {
    int i = *edge.rbegin();
    // printf(">> remove %d => %d %d\n", u, qry[u].x, qry[u].y);
    if (ins[i]) {
        cut(did[i].first, did[i].second);
        ins[i] = 0, --cnt, now -= i;
    }
    edge.pop_back();
}

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; i++) {
        while (qry[i].c = getchar(), !isupper(qry[i].c));
        if (qry[i].c == 'A') read(qry[i].x), read(qry[i].y);
        else if (qry[i].c == 'D') read(qry[i].x);
    }
    for (int i = 1; i <= m; i++) {
        query &it = qry[i];
        if (it.c == 'A') {
            append(i, it.x, it.y), ans[i] = get();
            if (i < m && qry[i + 1].c == 'R')
                remove(), ans[i + 1] = get();
        } else if (it.c == 'D') {
            if (i < m && qry[i + 1].c == 'R') {
                ans[i] = it.x < edge.size() ? ans[edge[edge.size() - it.x - 1]] : 0;
                ans[i + 1] = ans[i - 1];
            } else {
                while (it.x--) remove();
                ans[i] = get();
            }
        }
        // printf("[cnt=%d now=%d]\n", cnt, now);
    }
    for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}