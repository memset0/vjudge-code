// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.19 17:43:34
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

const int N = 2e5 + 10, mod = 1e9 + 7;
int T, A, B, C, N;

inline int mul3(int a, int b, int c) { return (ll)a * b * c % mod; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

void sieve(int n) {
	for (int i = 2; i <= n; i++) {
		if (vis[i]) pri[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i & pri[j] <= n; j++) {
			if (i % pri[j] == 0) break;
		}
	}
}

inline void add_edge(int u, int v, int w) {
	G[u].push_back(std::make_pair(v, w));
	G[v].push_back(std::make_pair(u, w));
}

void main() {
	read(T);
	sieve(2e5);
	while (T--) {
		read(A), read(B), read(C);	
		N = std::max(A, std::max(B, C));
		for (int i = 1; i <= N; i++)
			for (int x = 1; (ll)x * x * i <= N; x++)
				for (int y = x; (ll)x * y * i <= N; y++)
					if (mu[x * i] && mu[y * i])
						add_edge(x * i, y * i, x * y * i);
		for (int u = 1; u <= n; u++)
			for (const auto &it : G[u])
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);	
#endif
	return ringo::main(), 0;
}