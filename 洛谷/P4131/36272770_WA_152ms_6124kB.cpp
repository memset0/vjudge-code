// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.06 09:54:22
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
#define ll long long
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

const int N = 1e5 + 10, M = 6;
int n, m, sum;
int c[M];

struct status {
	int min, id;
	inline bool operator < (const status &other) const {
		return min < other.min;
	}
} min[1 << 5];

struct answer {
	int max, x, y;
	inline bool operator < (const answer &other) const {
		return max < other.max;
	}
} ans;

struct node {
	int b[6], id;
	inline bool operator < (const node &other) const {
		return b[m] < other.b[m];
	}
} a[N];

void main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) read(c[i]);
	for (int i = 1; i <= n; i++) {
		a[i].id = i;
		for (int j = 1; j <= m; j++) {
			read(a[i].b[j]);
			a[i].b[j] *= c[j];
		}
	}
	std::sort(a + 1, a + n + 1);
	// for (int i = 1; i <= n; i++) {
	// 	printf("[%d] ", a[i].id);
	// 	for (int j = 1; j <= m; j++)
	// 		print(a[i].b[j], " \n"[j == m]);
	// }
	for (int i = 1; i <= n; i++) {
		for (int x = 0, lim = 1 << (m - 1); x < lim; x++) {
			sum = 0;
			for (int j = 1; j < m; j++)
				sum += (x & (1 << (j - 1)) ? 1 : -1) * a[i].b[j];
			ans = std::max(ans, (answer){sum - min[x].min - a[i].b[m], a[i].id, min[x].id});
			min[x] = std::min(min[x], (status){sum - a[i].b[m], a[i].id});
		}
	}
	print(ans.x, ' '), print(ans.y, '\n'), print(ans.max, '\n');
}

} signed main() { return ringo::main(), 0; }