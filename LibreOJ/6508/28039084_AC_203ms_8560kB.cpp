// =================================
//   author: memset0
//   date: 2018.12.28 17:18:27
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 1e5 + 10;
int n, A, B, C, m, q;
int place[N];
bool b[N];

struct info {
	int val, key;
	inline bool operator < (const info &other) const {
		return val < other.val;
	}
} a[N];

struct node {
	int l, r, mid, cnt[2], min, max;
} p[N << 2];

inline void maintain(int u) {
	p[u].min = p[u << 1].min, p[u].max = p[u << 1 | 1].max;
	p[u].cnt[0] = p[u << 1].cnt[0] + p[u << 1 | 1].cnt[0];
	p[u].cnt[1] = p[u << 1].cnt[1] + p[u << 1 | 1].cnt[1];
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].min = p[u].max = a[l].val, p[u].cnt[b[a[l].key]]++; return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
	maintain(u);
}

void modify(int u, int k, int v) {
	if (p[u].l == p[u].r) { p[u].cnt[v] = 1, p[u].cnt[v ^ 1] = 0; return; }
	modify(k <= p[u].mid ? u << 1 : u << 1 | 1, k, v);
	maintain(u);
}

int query(int u, int w) {
	int f1 = (p[u].min + w) % n, f2 = (p[u].max + w) % n;
	if (((f1 >= C) ^ (f2 >= C)) == 0 && (f1 <= f2)) return p[u].cnt[f1 < C];
	return query(u << 1, w) + query(u << 1 | 1, w);
}

void main() {
	read(n), read(A), read(B), read(C), read(m);
	for (int i = 0, c; i < m; i++) {
		a[i + 1].val = ((ll)A * i + B) % n;
		a[i + 1].key = i;
		while (c = getchar(), c != '0' && c != '1');
		b[i] = c - '0';
	}
	std::sort(a + 1, a + m + 1), build(1, 1, m);
	for (int i = 1; i <= m; i++) place[a[i].key] = i;
	read(q);
	for (int i = 1, op, k; i <= q; i++) {
		read(op), read(k);
		if (op == 1) print(query(1, A * k % n), '\n');
		else modify(1, place[k], b[k] ^= 1);
	}
}

} signed main() { return ringo::main(), 0; }
