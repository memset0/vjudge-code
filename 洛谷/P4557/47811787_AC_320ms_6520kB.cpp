// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.13 11:07:58
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
int n, m, q;

struct node {
	int x, y;
	friend inline bool operator == (const node &a, const node &b) { return a.x == b.x && a.y == b.y; }
	friend inline ll operator * (const node &a, const node &b) { return (ll)a.x * b.y - (ll)a.y * b.x; }
	friend inline node operator + (const node &a, const node &b) { return (node){a.x + b.x, a.y + b.y}; }
	friend inline node operator - (const node &a, const node &b) { return (node){a.x - b.x, a.y - b.y}; }
	friend inline bool operator < (const node &a, const node &b) {
		ll t = a * b;
		return t == 0 ? (a.x == b.x ? abs(a.y) < abs(b.y) : abs(a.x) < abs(b.x)) : t > 0;
	}
} u, det;
inline bool cmp_x(const node &a, const node &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline bool cmp_y(const node &a, const node &b) { return a.y == b.y ? a.x < b.x : a.y < b.y; }
std::vector <node> a, b, c;

template <class T> T top(const std::vector <T> &a) { return *--a.end(); }
template <class T> T nxt(const std::vector <T> &a) { return *----a.end(); }
template <class T> std::vector <T> operator + (std::vector <T> a, const std::vector <T> &b) {
	for (const T &u : b) a.push_back(u); return a;
}

std::vector <node> clear(std::vector <node> a) {
	std::sort(a.begin(), a.end(), cmp_x); std::vector <node> b(1, a[0]);
	for (int i = 1; i < a.size(); i++) if (!(a[i] == a[i - 1])) b.push_back(a[i]);
	return b;
}

std::vector <node> build(std::vector <node> a) {
	std::vector <node> b; std::sort(a.begin(), a.end(), cmp_y);
	node det = *a.begin(); for (auto &u : a) u = u - det;
	std::sort(a.begin(), a.end());
	for (auto &u : a) {
		while (b.size() > 1 && (u - nxt(b)) * (top(b) - nxt(b)) >= 0) b.pop_back();
		b.push_back(u);
	}
	for (auto &u : b) u = u + det; return b;
}

std::vector <node> split(const std::vector <node> &a) {
	std::vector <node> b;
	for (int i = 1; i < a.size(); i++) b.push_back(a[i] - a[i - 1]);
	b.push_back(a[0] - *--a.end()); return b;
}

std::vector <node> merge(const std::vector <node> &a, const std::vector <node> &b) {
	int i = 0, j = 0; std::vector <node> c;
	while (i < a.size() && j < b.size()) c.push_back(a[i] * b[j] < 0 ? b[j++] : a[i++]);
	while (i < a.size()) c.push_back(a[i++]);
	while (j < b.size()) c.push_back(b[j++]);
	return c;
}

std::vector <node> build(const std::vector <node> &a, const node &pos) {
	std::vector <node> b(1, pos);
	for (int i = 0; i < a.size(); i++) b.push_back(*--b.end() + a[i]);
	return b;
}

inline bool search(const node &u, const std::vector <node> &a) {
	// printf("search %d %d\n", u.x, u.y);
	int l = 0, r = a.size() - 2, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (!(u < a[mid])) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return (u - a[ans]) * (a[ans + 1] - a[ans]) <= 0;
}

void main() {
	read(n), read(m), read(q);
	for (int i = 1, x, y; i <= n; i++) read(x), read(y), a.push_back((node){x, y});
	for (int i = 1, x, y; i <= m; i++) read(x), read(y), b.push_back((node){-x, -y});
	// printf("a => "); for (auto u : build(a)) printf("[%d %d] ", u.x, u.y); puts("");
	// printf("b => "); for (auto u : build(b)) printf("[%d %d] ", u.x, u.y); puts("");
	// printf("a => "); for (auto u : split(build(a))) printf("[%d %d] ", u.x, u.y); puts("");
	// printf("b => "); for (auto u : split(build(b))) printf("[%d %d] ", u.x, u.y); puts("");
	a = build(clear(a)), b = build(clear(b)), c = build(merge(split(a), split(b)), *a.begin() + *b.begin());
	det = *c.begin(); for (auto &u : c) u = u - det;
	// printf("c => "); for (auto u : c) printf("[%d %d] ", u.x, u.y); puts("");
	for (int i = 1, t; i <= q; i++) {
		read(u.x), read(u.y), u = u - det;
		putchar(search(u, c) ? '1' : '0'), putchar('\n');
	}
}

} signed main() { return ringo::main(), 0; }