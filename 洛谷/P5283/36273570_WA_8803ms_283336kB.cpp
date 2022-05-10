// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.10 09:31:01
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define uint unsigned int
#define ull unsigned long long
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

const int N = 5e5 + 10, M = N * 80;
int n, k, cnt, rt[N];
ull ans;
uint a[N], s[N];
int ch[M][2], siz[M];

struct status {
    int value, key;
    inline bool operator < (const status &other) const {
        return value == other.value ? key < other.key : value < other.value;
    }
};
std::priority_queue <status> q;

void modify(int &u, int v, uint value, int delta, int h = 31) {
    u = ++cnt, ch[u][0] = ch[v][0], ch[u][1] = ch[v][1], siz[u] = siz[v] + delta;
    if (!~h) return;
    int side = (value >> h) & 1;
    modify(ch[u][side], ch[v][side], value, delta, h - 1);
}

uint query(int u, uint value, int h = 31) {
    if (!~h) return 0;
    int side = (value >> h) & 1 ^ 1;
    if (siz[ch[u][side]])
        return query(ch[u][side], value, h - 1) + (1u << h);
    else
        return query(ch[u][side ^ 1], value, h - 1);
}

void main() {
    read(n), read(k);
    for (int i = 1; i <= n; i++) read(a[i]), s[i] = s[i - 1] ^ a[i];
    modify(rt[0], 0, 0, 1);
    for (int i = 1; i <= n; i++) modify(rt[i], rt[i - 1], s[i], 1);
    for (int i = 1; i <= n; i++) q.push((status){query(rt[i - 1], s[i]), i});
    for (int i = 1; i <= k; i++) {
        auto it = q.top(); q.pop();
        ans += it.value, modify(rt[i], rt[i], s[i] ^ it.value, -1);
        q.push((status){query(rt[i - 1], s[i]), i});
    }
    print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}