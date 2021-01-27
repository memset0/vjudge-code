// =================================
//   author: memset0
//   date: 2019.07.01 23:53:06
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

const int N = 1e6 + 10;
double e[N], sum[N];
int n, a[N], b[N], rev_id[N];

struct pair {
	int a, b, id;
	inline bool operator<(const pair &other) const {
		if (a != other.a) return a < other.a;
		if (b != other.b) return b > other.b;
		return id < other.id;
	}
} t[N];

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(t[i].a);
	for (int i = 1; i <= n; i++) read(t[i].b);
	for (int i = 1; i <= n; i++) t[i].id = i;
	std::sort(t + 1, t + n + 1);
	for (int i = 1; i <= n; i++) a[i] = t[i].a;
	for (int i = 1; i <= n; i++) b[i] = t[i].b;
	for (int i = 1; i <= n; i++) rev_id[t[i].id] = i;
	// print(a, 1, n), print(b, 1, n), print(rev_id, 1, n);
	for (int i = 1; i <= n; i++)
		if (b[i]) {
			int k = std::upper_bound(a + 1, a + n + 1, a[i] - b[i]) - a - 1;
			// printf(">> %d %d : %.2lf\n", i, k, sum[k]);
			e[i] = k ? sum[k] / k + 1 : 1;
			sum[i] = sum[i - 1] + e[i];
		} else {
			int k = 0;
			while (i + k <= n && a[i] == a[i + k] && !b[i + k]) k++;
			i = i + k - 1;
			// printf(">> %d %d\n", i, k);
			e[i] = i - k ? (i + sum[i - k]) / (i - k) : 1e30;
			for (int j = i - k + 1; j <= i; j++)
				e[j] = e[i], sum[j] = sum[j - 1] + e[j];
		}	
	// for (int i = 1; i <= n; i++) printf("%.5lf%c", e[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) printf("%.5lf%c", sum[i], " \n"[i == n]);
	for (int i = 1; i <= n; i++) printf("%.5lf%c", e[rev_id[i]] > 1e20 ? 0 : e[rev_id[i]], " \n"[i == n]);
}		

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}