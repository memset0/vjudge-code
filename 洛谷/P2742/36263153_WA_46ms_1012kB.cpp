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
int n;
double ans;

struct node {
	double x, y;
	friend inline double operator * (const node &a, const node &b) { return (ll)a.x * b.y - (ll)a.y * b.x; }
	friend inline node operator + (const node &a, const node &b) { return (node){a.x + b.x, a.y + b.y}; }
	friend inline node operator - (const node &a, const node &b) { return (node){a.x - b.x, a.y - b.y}; }
	friend inline bool operator < (const node &a, const node &b) {
		return a * b < 0;
	}
};
inline bool cmp_x(const node &a, const node &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline bool cmp_y(const node &a, const node &b) { return a.y == b.y ? a.x < b.x : a.y < b.y; }

template <class T> T top(const std::vector <T> &a) { return *--a.end(); }
template <class T> T nxt(const std::vector <T> &a) { return *----a.end(); }
template <class T> std::vector <T> operator + (std::vector <T> a, const std::vector <T> &b) {
	for (const T &u : b) a.push_back(u); return a;
}

std::vector <node> build(std::vector <node> a) {
	std::vector <node> b;
	std::sort(a.begin(), a.end(), cmp_y);
	node det = *a.begin();
	for (auto &u : a) u = u - det;
	std::sort(a.begin(), a.end());
	// for (auto &u : a) printf(">> %.2lf %.2lf\n", u.x, u.y);
	for (auto &u : a) {
		while (b.size() > 1 && (u - nxt(b)) * (top(b) - nxt(b)) >= 0) b.pop_back();
		b.push_back(u);
		// for (auto u : b) printf("[%.2lf %.2lf] ", u.x, u.y); puts("");
	}
	for (auto &u : b) u = u + det; return b;
}

inline double sqr(double a) { return a * a; }

void main() {
	read(n);
	std::vector <node> a;
	for (int i = 1; i <= n; i++) {
		double x, y; scanf("%lf%lf", &x, &y);
		a.push_back((node){x, y});
	}
	// for (auto u : a) printf("1 [%.2lf %.2lf]\n", u.x, u.y);
	a = build(a);
	// for (auto u : a) printf("2 [%.2lf %.2lf]\n", u.x, u.y);
	a.push_back(*a.begin());
	for (int i = 1; i < a.size(); i++)
		ans += sqrt(sqr(a[i].x - a[i - 1].x) + sqr(a[i].y - a[i - 1].y));
	printf("%.2lf\n", ans);
}

} signed main() { return ringo::main(), 0; }