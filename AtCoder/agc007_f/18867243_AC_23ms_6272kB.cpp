// =================================
//   author: memset0
//   date: 2019.03.21 15:35:21
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

const int N = 1e6 + 10;
int n, m, ans, flag = 1;
char a[N], b[N];
std::queue <int> q;

void main() {
	read(n), scanf("%s%s", a + 1, b + 1);
	for (int i = 1; i <= n; i++) flag &= a[i] == b[i];
	if (flag) { puts("0"); return; }
	for (int i = n, j = n; i >= 1; i--) {
		if (b[i] == b[i - 1]) continue;
		while (j >= 1 && j > i) j--;
		while (j >= 1 && b[i] != a[j]) j--;
		if (j < 1) { puts("-1"); return; }
		while (q.size()) {
			// printf(">> %d %d %d\n", q.front(), q.size(), i);
			if (q.front() - q.size() >= i) q.pop();
			else break;
		}
		q.push(j);
		if (i != j) ans = std::max(ans, (int)q.size());
	}
	print(ans + 1, '\n');
}

} signed main() { return ringo::main(), 0; }