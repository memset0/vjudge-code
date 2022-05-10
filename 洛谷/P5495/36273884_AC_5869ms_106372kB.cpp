// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.09 16:54:35
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

const int N = 2e7 + 10;
unsigned int n, ans, cnt, seed, a[N], pri[N >> 3];
bool vis[N];

inline unsigned int getnext() {
	seed ^= seed << 13, seed ^= seed >> 17, seed ^= seed << 5;
	return seed;
}

void main() {
	read(n), read(seed);
	for (int i = 1; i <= n; i++) a[i] = getnext();
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) { pri[++cnt] = i; }
		for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt; i++) {
		int c = pri[i];
		for (int j = 1, k = c; k <= n; j++, k += c)
			a[k] += a[j];
	}
	for (int i = 1; i <= n; i++) ans ^= a[i];
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