// =================================
//   author: memset0
//   date: 2019.08.15 18:30:49
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 155;
int n, ans = 2e9, a[N][N], b[N][N], f[N][N];

struct edge {
	int u, v, w;
	inline bool operator<(const edge &other) const {
		return w < other.w;
	}
};
std::vector<edge> e;

void main() {
	read(n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = 2e9;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			read(a[i][j]);
			e.push_back((edge){i, j, a[i][j]});
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			read(b[i][j]);
	std::sort(e.begin(), e.end());
	for (int i = 1; i <= n; i++) f[i][i] = 0;
	for (auto it = e.begin(); it != e.end(); it++) {
		int u = it->u, v = it->v;
		f[u][v] = std::min(f[u][v], b[u][v]);
		for (int p = 0, k = u; p < 2; p++, k = v)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					f[i][j] = std::min(f[i][j], std::max(f[i][k], f[k][j]));
		int max = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (f[i][j] > max) max = f[i][j];
		// printf(">> %d %d : %d %d\n", it->u, it->v, it->w, max);
		// for (int i = 1; i <= n; i++) print(f[i], 1, n);
		ans = std::min((ll)ans, (ll)max + it->w);
	}
	print(ans, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}
