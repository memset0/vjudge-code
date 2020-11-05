// =================================
//   author: memset0
//   date: 2019.02.08 23:58:06
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
int tpc, tpr;
inline char testchar() { return ~tpc ? tpc : tpc = ::getchar(); }
inline char getchar() { if (~tpc){ tpr = tpc, tpc = -1; return tpr; } else return ::getchar(); }
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

const int N = 1e4 + 10;
int n, u, v, w, ans, tmp, dp[N];
int tot = 2, hed[N], to[N << 1], nxt[N << 1], val[N << 1];

inline void update(int key, int &mx1, int &mx2) {
    if (key > mx1) mx2 = mx1, mx1 = key;
    else if (key > mx2) mx2 = key;
}

void dfs(int u, int father) {
    int mx1 = 0, mx2 = 0;
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != father) {
            dfs(v, u);
            update(val[i] + dp[v], mx1, mx2);
        }
    dp[u] = mx1, ans = std::max(ans, mx1 + mx2);
}

void main() {
    while (~testchar()) {
        tot = 2, ans = n = 0;
        while (tmp = testchar(), tmp != '\n' && (~tmp)) {
            read(u), read(v), read(w), n = std::max(n, std::max(u, v));
            nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
            nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
            // printf(">> %d %d %d\n", u, v, w);
        } getchar();
        dfs(1, 1), print(ans, '\n');
        memset(hed, 0, (n + 1) << 2);
    }
}

} signed main() { return ringo::main(), 0; }