// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.11 09:41:34
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

const int N = 2e5 + 10;
ll ans;
int n, a[N], fa[N];
std::vector<int> G[N];
std::multiset<int> set[N];

void dfs(int u) {
    std::vector<int> max;
    set[u].insert(a[u]);
    for (auto v : G[u]) {
        dfs(v);
        if (set[v].size() > max.size()) max.resize(set[v].size());
        int tmp = 0;
        for (std::set<int>::reverse_iterator it = set[v].rbegin(); it != set[v].rend(); ++it)
            max[tmp] = std::max(max[tmp], *it), tmp++;
        set[v].clear();
    }
    for (auto i : max) set[u].insert(i);
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 2; i <= n; i++) read(fa[i]), G[fa[i]].push_back(i);
    dfs(1);
    ans = 0;
    for (auto i : set[1]) ans += i;
    print(ans, '\n');
    // for (int i = 1; i <= n; i++) {
    //     printf("set[%d] = ", i);
    //     for (auto j : set[i]) print(j, ' ');
    //     putchar('\n');
    // }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}