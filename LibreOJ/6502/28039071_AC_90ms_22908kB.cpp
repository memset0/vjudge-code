// =================================
//   author: memset0
//   date: 2018.12.27 11:53:29
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)
namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 2010, p = 1e9 + 7;
int n, m, id;
int a[N], b[N], flag[N];
std::multiset <int> set;

struct info {
	int val, cnt;
	inline info operator + (const int &other) {
		return (info){val + other, cnt};
	}
} ans, f[N][N];

inline void merge(info &a, const info &b) {
	if (a.val > b.val) return;
	if (b.val > a.val) { a = b; return; }
	a.cnt = (a.cnt + b.cnt) % p;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(b[i]), set.insert(b[i]);
	id = n;
	while (set.size()) {
		if (*set.begin() + *--set.end() < m) {
			a[id] = *set.begin();
			flag[id] = 0;
			set.erase(set.begin());
		} else {
			a[id] = *--set.end();
			flag[id] = 1;
			set.erase(--set.end());
		}
		--id;
	}
	f[0][0] = {0, 1};
	for (int i = 1; i <= n; i++)
		if (flag[i]) {
			for (int j = 0; j <= i; j++) {
				if (j - 1 >= 0) merge(f[i][j], f[i - 1][j - 1] + (i - j));
				if (j <= i - 1) merge(f[i][j], f[i - 1][j] + j);
			}
		} else {
			for (int j = 0; j <= i; j++) {
				if (j - 1 >= 0) merge(f[i][j], f[i - 1][j - 1]);
				if (j <= i - 1) merge(f[i][j], f[i - 1][j]);
			}
		}
	ans = {0, 0};
	for (int i = 0; i <= n; i++) merge(ans, f[n][i]);
	print(ans.val, ' '), print(ans.cnt, '\n');
}

} signed main() { return ringo::main(), 0; }
