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
int n, cur, a[N], log[N], fa[N][20], f[A][B], g[A][B];

struct query {
	int x, w, r;
	inline bool operator<(const query &other) const {
		return r < other.r;
	}
};
std::vector<query> q;

inline int merge(int x, int y) { return a[x] < a[y] ? y : x; }
inline std::pair<int, int> split(int x) { return std::make_pair(x >> 8, x & ((1 << 8) - 1)); }
inline int query_max(int l, int r) { int t = log[r - l + 1]; return merge(fa[l][t], fa[r - (1 << t) + 1][t]); }
inline void add_query(int x, int w, int l, int r) { q.push_back({x, w, r}); if (l > 1) q.push_back({x, -w, l - 1}); }

int cnt = 0;
void solve(int l, int r) {
	if (l > r) return;
	int mid = query_max(l, r);
	if (l < mid && mid < r) {
		if (mid - l < r - mid) {
			for (int i = l; i <= mid - 1; i++) add_query(a[i], a[mid], mid + 1, r);
		} else {
			for (int i = mid + 1; i <= r; i++) add_query(a[i], a[mid], l, mid - 1);
		}
	}
	add_query(a[mid], a[mid], l, r);
	solve(l, mid - 1), solve(mid + 1, r);
}

void main() {
	read(n), log[0] = -1;
	for (int i = 1; i <= n; i++) {
		read(a[i]), fa[i][0] = i;
		log[i] = log[i >> 1] + 1;
	}
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			fa[i][j] = merge(fa[i][j - 1], fa[i + (1 << (j - 1))][j - 1]);
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