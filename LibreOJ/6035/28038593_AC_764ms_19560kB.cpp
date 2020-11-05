// =================================
//   author: memset0
//   date: 2019.07.22 18:31:19
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
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

const int N = 1e6 + 10;
ll ans, f[N], g[N];
int l, n, m, w[N], d[N];

struct info {
	ll time; int cost;
	inline bool operator<(const info &other) const {
		return time > other.time;
	}
};
std::priority_queue<info> W, D;

void main() {
	read(l), read(n), read(m);
	for (int i = 1; i <= n; i++) read(w[i]), W.push((info){w[i], w[i]});
	for (int i = 1; i <= m; i++) read(d[i]), D.push((info){d[i], d[i]});
	for (int i = 1; i <= l; i++) {
		auto it = W.top(); W.pop();
		f[i] = it.time, it.time += it.cost, W.push(it);
		it = D.top(); D.pop();
		g[i] = it.time, it.time += it.cost, D.push(it);
	}
	for (int i = 1; i <= l; i++)
		ans = std::max(ans, f[i] + g[l - i + 1]);
	print(ans, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
