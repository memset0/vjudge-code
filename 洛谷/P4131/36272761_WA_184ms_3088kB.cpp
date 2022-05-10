// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.06 09:19:01
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
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
int a[N][M], c[M];
bool tag[M];

struct status {
	int max, cos;
	inline bool operator < (const status &other) const {
		return max < other.max;
	}
} max[1 << 5];

struct answer {
	int max, x, y;
	inline bool operator < (const answer &other) const {
		return max < other.max;
	}
} ans;

void main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) read(c[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(a[i][j]), a[i][j] *= (j == m ? -1 : 1) * c[j];
	for (int x = 0; x < (1 << m); x++) {
		for (int i = 1; i <= m; i++) tag[i] = x & (1 << (i - 1)) ? 1 : 0;
		for (int i = 1; i <= n; i++) {
			sum = 0;
			for (int j = 1; j <= m; j++)
				sum += a[i][j] * (tag[j] ? 1 : -1);
			max[x] = std::max(max[x], (status){sum, i});
		}
	}
	for (int x = 0; x < (1 << m); x++) {
		int y = x ^ ((1 << m) - 1);
		for (int i = 1; i <= m; i++) tag[i] = x & (1 << (i - 1)) ? 1 : 0;
		for (int i = 1; i <= n; i++) {
			sum = 0;
			for (int j = 1; j <= m; j++)
				sum += a[i][j] & (tag[j] ? 1 : -1);
			ans = std::max(ans, (answer){sum + max[y].max, max[y].cos, i});
		}
	}
	print(ans.x, ' '), print(ans.y, '\n'), print(ans.max, '\n');
}

} signed main() { return ringo::main(), 0; }