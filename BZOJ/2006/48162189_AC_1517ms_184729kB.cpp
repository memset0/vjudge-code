// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.07 14:18:20
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 5e5 + 10;
ll ans;
int n, m, L, R;
int a[N], s[N], l[N], r[N], rt[N];
int max = -1234, min = 1234;

struct info {
	int val, i, k;
	inline bool operator<(const info &other) const {
		return val < other.val;
	}
};
std::priority_queue<info> q;

namespace seg {
	const int M = N * 40;
	int nod, ch[M][2], sum[M];
	void modify(int &u, int v, int k, int l, int r) {
		u = ++nod, ch[u][0] = ch[v][0], ch[u][1] = ch[v][1], sum[u] = sum[v] + 1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (k <= mid) modify(ch[u][0], ch[v][0], k, l, mid);
		else modify(ch[u][1], ch[v][1], k, mid + 1, r);
	}
	int query(int u, int v, int k, int l, int r) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (k <= sum[ch[u][0]] - sum[ch[v][0]]) return query(ch[u][0], ch[v][0], k, l, mid);
		else return query(ch[u][1], ch[v][1], k - sum[ch[u][0]] + sum[ch[v][0]], mid + 1, r);
	}
	void init() {
		modify(rt[1], 0, 0, min, max);
		for (int i = 1; i <= n; i++) modify(rt[i + 1], rt[i], s[i], min, max);
	}
}
inline int query(int i, int k)  { return seg::query(rt[r[i] + 1], rt[l[i]], k, min, max); }

void main() {
	read(n), read(m), read(L), read(R);
	for (int i = 1; i <= n; i++) {
		read(a[i]), s[i] = s[i - 1] + a[i];
		min = std::min(min, s[i]), max = std::max(max, s[i]);
	}
	// print(a, 1, n, "a"), print(s, 1, n, "s");
	seg::init();
	for (int i = 1; i <= n; i++) {
		l[i] = std::max(0, i - R), r[i] = std::max(-1, i - L);
		// printf("%d > L : %d > R : %d | %d %d => %d\n", i, l[i], r[i], s[i], query(i, 1), s[i] - query(i, 1));
		if (r[i] - l[i] + 1) q.push((info){s[i] - query(i, 1), i, 1});
	}
	for (int i = 1; i <= m; i++) {
		info u = q.top(); q.pop(), ans += u.val;
		// printf(">> %d %d %d | %d\n", u.val, u.i, u.k);
		if (u.k + 1 <= r[u.i] - l[u.i] + 1) q.push((info){s[u.i] - query(u.i, u.k + 1), u.i, u.k + 1});
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}