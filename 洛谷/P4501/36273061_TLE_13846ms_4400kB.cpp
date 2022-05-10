// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.22 17:12:24
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

const int N = 2e5 + 10;
int n, m, k, lft, rit;
ll L, R, ans, s[N];
int d[N];

struct node {
	int a, l;
	inline bool operator < (const node &other) const {
		return a < other.a;
	}
} a[N];
inline ll dis(int a, int b) { return s[b] - s[a]; }

void main() {
	read(n), read(m);
	for (int i = 1; i < n; i++) read(d[i]), s[i + 1] = s[i] + d[i];
	// for (int i = 1; i < n; i++) print(d[i], " \n"[i == n - 1]);
	// for (int i = 1; i <= n; i++) print(s[i], " \n"[i == n]);
	for (int i = 1; i <= m; i++) {
		read(k), ans = 0;
		for (int i = 1; i <= k; i++) read(a[i].a), read(a[i].l);
		std::sort(a + 1, a + k + 1);
		for (int i = 1, p, ret; i <= k; i++) {
			lft = 1, rit = n;
			for (int j = 1; j < i; j++) {
				p = a[i].a - ((a[i].a - a[j].a - 1) >> 1), ret = -1;
				for (int l = a[j].a, r = p, mid; mid = l + r >> 1, l <= r; ) {
					L = dis(mid, a[i].a) + a[i].l;
					R = dis(a[j].a, mid) + a[j].l;
					if (L < R || (L == R && a[j].a - mid == mid - a[i].a))
						r = mid - 1, ret = mid;
					else l = mid + 1;
				}
				if (dis(a[j].a, a[i].a) + a[i].l < a[j].l) continue;
				// printf("i=%d j=%d p=%d ret=%d\n", i, j, p, ret);
				if (ret == -1) ret = p;
				lft = std::max(lft, ret);
			}
			for (int j = i + 1; j <= k; j++) {
				p = a[i].a + ((a[j].a - a[i].a - 1) >> 1), ret = -1;
				for (int l = p, r = a[j].a, mid; mid = l + r >> 1, l <= r; ) {
					L = dis(a[i].a, mid) + a[i].l;
					R = dis(mid, a[j].a) + a[j].l;
					if (L < R)
						l = mid + 1, ret = mid;
					else r = mid - 1;
				}
				// printf("i=%d j=%d p=%d ret=%d\n", i, j, p, ret);
				if (dis(a[i].a, a[j].a) + a[i].l < a[j].l) continue;
				if (ret == -1) ret = p;
				rit = std::min(rit, ret);
			}
			// printf("%d : [%d %d]\n", i, lft, rit);
			ans += std::max(rit - lft + 1, (int)0);
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }