// =================================
//   author: memset0
//   date: 2019.04.17 11:00:40
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

const int M = 1e3, K = 24, mod = 998244353;
int T, n, a[K][K];
std::vector<int> key;
std::map<int, std::pair<int, int>> map;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

struct Graph {
	int ans;
	std::vector<std::pair<int, int>> e;
	int gauss(int a[K][K]) {
		int ans = 1;
		for (int i = 1, j; i < K; i++) {
			for (j = i; j < K; j++) if (a[j][i]) break;
			if (j == K) return 0;
			if (i != j) ans = mod - ans, std::swap(a[i], a[j]);
			for (int j = i + 1; j < K; j++) {
				int tmp = mul(a[j][i], inv(a[i][i]));
				for (int k = i; k < K; k++)
					a[j][k] = dec(a[j][k], mul(a[i][k], tmp));
			}
		}
		for (int i = 1; i < K; i++) ans = mul(ans, a[i][i]);
		return ans;
	}
	void init() {
		while (!ans) {
			e.clear(), memset(a, 0, sizeof(a));
			for (int i = 0; i < K; i++)
				for (int j = i + 1; j < K; j++)
					if (rand() & 1) {
						e.push_back(std::make_pair(i, j));
						a[i][j] = a[j][i] = 1, a[i][i] = dec(a[i][i], 1), a[j][j] = dec(a[j][j], 1);
					}
			ans = gauss(a);
		}
	}
	void output(int base) {
		for (auto it : e)
			print(it.first + base, ' '), print(it.second + base, '\n');
	}
} graph[M];

void make_ans(int a, int b, int c, int d) {
	printf("%d %d\n", K << 2, 3 + int(graph[a].e.size() + graph[b].e.size() + graph[c].e.size() + graph[d].e.size()));
	graph[a].output(1);
	graph[b].output(1 + K);
	graph[c].output(1 + K * 2);
	graph[d].output(1 + K * 3);
	printf("%d %d\n%d %d\n%d %d\n", 1, 1 + K, 1 + K, 1 + K * 2, 1 + K * 2, 1 + K * 3);
}

void main() {
	srand(20040725);
	for (int i = 0; i < M; i++) graph[i].init();
	for (int i = 0; i < M; i++)
		for (int j = i; j < M; j++)
			map[mul(graph[i].ans, graph[j].ans)] = std::make_pair(i, j);
	// printf("%d %d\n", K, graph[1].e.size()), graph[1].output(1);
	// printf(">> %d\n", graph[1].ans);
	for (auto it = map.begin(); it != map.end(); it++) {
		key.push_back(it->first);
	}
	for (read(T); T--; ) {
		read(n);
		if (!n) { puts("4 0"); continue; }
		bool flag = false;
		for (auto u : key) {
			int v = mul(inv(u), n);
			auto it = map.find(v);
			if (it != map.end()) {
				auto jt = map.find(u);
				make_ans(it->second.first, it->second.second, jt->second.first, jt->second.second);
				flag = true; break;
			}
		}
		if (!flag) puts("QwQ");
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
	freopen("2.in", "w", stdout);
#endif
	return ringo::main(), 0;
}