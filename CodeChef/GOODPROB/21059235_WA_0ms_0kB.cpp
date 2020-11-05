// =================================
//   author: memset0
//   date: 2019.08.04 14:02:19
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

const int N = 2e5 + 10, A = 1 << 6, B = 1 << 8;
ll ans, sum;
std::map<int, int> count;
int n, cur, a[N], f[A][B], g[A][B];

struct query {
	int x, w, r;
	inline bool operator<(const query &other) const {
		return r < other.r;
	}
};
std::vector<query> q;

struct node {
	int l, r, mid, max;
	inline static int merge(int x, int y) {
		return a[x] < a[y] ? y : x;
	}
} p[N << 3];

void build_seg(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].max = l; return; }
	build_seg(u << 1, l, p[u].mid);
	build_seg(u << 1 | 1, p[u].mid + 1, r);
	p[u].max = node::merge(p[u << 1].max, p[u << 1 | 1].max);
}

int query_max(int u, int l, int r) {
	if (p[u].l == p[u].r) return p[u].max;
	if (r <= p[u].mid) return query_max(u << 1, l, r);
	if (l > p[u].mid) return query_max(u << 1 | 1, l, r);
	return node::merge(query_max(u << 1, l, p[u].mid), query_max(u << 1 | 1, p[u].mid + 1, r));
}

inline void add_query(int x, int w, int l, int r) {
	// printf("add query %d %d [%d %d]\n", x, w, l, r);
	q.push_back({x, w, r});
	if (l > 1) q.push_back({x, -w, l - 1});
}

std::pair<int, int> split(int x) {
	return std::make_pair(x >> 8, x & ((1 << 8) - 1));
}

int cnt = 0;
void solve(int l, int r) {
	if (l > r) return;
	int mid = query_max(1, l, r);
	if (++cnt >= 6) exit(0);
	if (l < mid && mid < r) {
		if (mid - l < r - mid) {
			// for (int i = l; i <= mid - 1; i++) add_query(a[i], a[mid], mid + 1, r);
		} else {
			// for (int i = mid + 1; i <= r; i++) add_query(a[i], a[mid], l, mid - 1);
		}
	}
	// add_query(a[mid], a[mid], l, r);
	solve(l, mid - 1), solve(mid + 1, r);
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	build_seg(1, 1, n);
	solve(1, n);
	std::sort(q.begin(), q.end());
	ans = 0;
	for (auto it : q) {
		while (cur < it.r) {
			++cur, ++count[a[cur]];
			auto num = split(a[cur]);
			for (int x = 0; x < (1 << 8); x++) {
				if ((num.second & x) == x) g[num.first][x]++;
				if ((num.second & x) == num.second) f[num.first][x]++;
			}
		}
		auto num = split(it.x);
		for (int x = 0; x < (1 << 6); x++) {
			if ((num.first & x) == x) ans += (ll)it.w * f[x][num.second];
			if ((num.first & x) == num.first) ans += (ll)it.w * g[x][num.second];
		}
		ans -= (ll)it.w * count[it.x];
		// printf("%d %d %d >> %lld | %d\n", it.x, it.w, it.r, ans);
	}
	for (int i = 1; i <= n; i++) ans -= a[i];
	print(ans, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}