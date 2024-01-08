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
std::vector<int> G[N];
std::multiset<int> set[N];
int n, mx1, mx2, a[N], fa[N];

inline void merge(std::multiset<int> &a, std::multiset<int> &b) {
    if (a.size() < b.size()) std::swap(a, b);
    std::vector<int> tmp(b.size());
    auto it = a.rbegin(), jt = b.rbegin();
    for (int i = 0; i < b.size(); i++) tmp[i] = *it++;
    for (int i = 0; i < b.size(); i++) a.erase(a.find(tmp[i]));
    for (int i = 0; i < b.size(); i++) a.insert(std::max(tmp[i], *jt++));
}

void dfs(int u) {
    for (auto v : G[u]) {
        dfs(v);
        merge(set[u], set[v]);
    }
    set[u].insert(a[u]);
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