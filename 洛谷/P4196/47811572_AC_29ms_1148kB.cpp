// =================================
//   author: memset0
//   date: 2019.08.02 01:00:45
//   website: https://memset0.cn/
// =================================
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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

const int N = 2e4 + 10, L = 1e4;
double ans;
int k, n, m, l, r, q[N];
std::pair<double, double> t[N];

struct line {
	ll A, B, C;
	double atan;
	int x1, y1, x2, y2, dx, dy, id;
	inline line() {}
	inline line(int x, int y, int z, int w) {
		x1 = x, y1 = y, x2 = z, y2 = w;
		dx = x2 - x1, dy = y2 - y1, atan = atan2(dy, dx);
		A = y1 - y2, B = x2 - x1, C = (ll)x1 * y2 - (ll)x2 * y1;
	}
	inline void output(std::string name) const {
		printf("%s: %d %d %d %d : %lld %lld %lld : %.2lf\n", name.c_str(), x1, y1, x2, y2, A, B, C, atan);
	}
	inline double calc(double x, double y) const {
		return (x - x1) * (y - y2) - (x - x2) * (y - y1);
	}
	inline double calc(const std::pair<double, double> &it) const {
		return (it.first - x1) * (it.second - y2) - (it.first - x2) * (it.second - y1); 
	}
	inline std::pair<double, double> get_point() const {
		if (A) return std::make_pair(-C / double(A), double(0));
		if (B) return std::make_pair(double(0), -C / double(B));
		return std::make_pair(double(0), double(0));
	}
	inline std::pair<double, double> calc_point(double x) const {
		return std::make_pair(x, -(x * A + C) / double(B));
	}
	inline bool operator<(const line &other) const {
		return atan == other.atan ? other.calc(get_point()) >= 0 : atan < other.atan;
	}
} a[N];

inline std::pair<double, double> cross(const line &a, const line &b) {
	if (!a.B) return b.calc_point(-a.C / (double)a.A);
	if (!b.B) return a.calc_point(-b.C / (double)b.A);
	return a.calc_point((b.C / double(b.B) - a.C / double(a.B)) / (a.A / double(a.B) - b.A / double(b.B)));
}

inline double calc_triangle(const std::pair<double, double> &a, const std::pair<double, double> &b) {
	// printf("(%.1lf,%.1lf) (%.1lf,%.1lf) => %.2f\n", a.first, a.second, b.first, b.second, (a.first * b.second - a.second * b.first) / 2);
	return (a.first * b.second - a.second * b.first) / 2;
}

void main() {
	read(k);
	for (int i = 1; i <= k; i++) {
		static int x[60], y[60];
		read(m);
		for (int i = 1; i <= m; i++) read(x[i]), read(y[i]);
		for (int i = 1; i < m; i++) a[++n] = line(x[i], y[i], x[i + 1], y[i + 1]);
		a[++n] = line(x[m], y[m], x[1], y[1]);
	}
	a[++n] = line(-L, -L, L, -L);
	a[++n] = line(L, -L, L, L);
	a[++n] = line(L, L, -L, L);
	a[++n] = line(-L, L, -L, -L);
	std::sort(a + 1, a + n + 1);            
	// for (int i = 1; i <= n; i++) a[i].output("a[" + std::to_string(i) + "]");

	l = r = q[1] = 1;
	for (int i = 2; i <= n; i++) if (a[i].atan != a[i - 1].atan) {
		while (l != r && a[i].calc(t[r - 1]) <= 0) {
			// printf("AAA %d -> %d\n", i, q[r]);
			r--;
		}
		while (l != r && a[i].calc(t[l]) <= 0) {
			// printf("BBB %d -> %d\n", i, q[l]);
			l++;
		}
		q[++r] = i, t[r - 1] = cross(a[q[r]], a[q[r - 1]]);
	}
	// std::cout << l << " " << r << std::endl;
	while (l != r && a[q[l]].calc(t[r - 1]) <= 0) {
		// printf("CCC %d -> %d | %.2lf %.2lf => %.2lf\n", q[l], q[r], t[r - 1].first, t[r - 1].second, a[q[l]].calc(t[r - 1]));
		r--;
	}
	// std::cout << l << " " << r << std::endl;
	t[r] = cross(a[q[r]], a[q[l]]);
	// printf("%.2lf %.2lf [%.2lf %.2lf]\n", a[q[l]].atan, a[q[r]].atan, t[r].first, t[r].second);
	// for (int i = l; i <= r; i++)
	// 	a[q[i]].output("a[q[" + std::to_string(i) + "]=" + std::to_string(q[i]) + "]");
	// for (int i = l; i <= r; i++) printf("(%.2lf, %.2lf)\n", t[i].first, t[i].second);
	
	if (l != r) {
		ans = calc_triangle(t[r], t[l]);
		for (int i = l; i < r; i++)
			ans += calc_triangle(t[i], t[i + 1]);
	}
	printf("%.3lf\n", ans);
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}