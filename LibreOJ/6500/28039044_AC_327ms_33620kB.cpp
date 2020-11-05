// =================================
//   author: memset0
//   date: 2018.12.26 12:54:19
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
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

const int N = 2e6 + 10;
int n, m, k, l, r, dta, _hsh, _ans;
int key[N], hsh[N], pre[N], aft[N], sum[N], ans[N];
char a[N];

void main() {
	srand(20040725);
	read(n), read(k), read(m), scanf("%s", a + 1);
	for (int i = 1; i <= n; i++) a[i] -= '0';
	for (int i = 0; i < k; i++) key[i] = rand();
	for (int i = 1; i <= n + 1; i++) {
		pre[i] = sum[i % k];
		if (a[i] != a[i - 1]) {
			dta = (i - 1) / k + 1 - (sum[i % k] << 1);
			hsh[i] = hsh[i - 1] ^ key[i % k];
			ans[i] = ans[i - 1] + dta, sum[i % k] = (i - 1) / k + 1 - sum[i % k];
			// printf(">>> %d %d %d : %d %d\n", i, (i - 1) / k + 1, dta, ans[i], sum[i % k]);
		} else {
			hsh[i] = hsh[i - 1];
			ans[i] = ans[i - 1];
		}
		aft[i] = sum[i % k];
	}
	// for (int i = 1; i <= n; i++) print((int)a[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(hsh[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(ans[i], " \n"[i == n]);
	for (int i = 1; i <= m; i++) {
		read(l), read(r);
		_hsh = hsh[r] ^ hsh[l];
		_ans = ans[r] - ans[l];
		// printf(">> %d %d : %d %d\n", l, r, _hsh, _ans);
		if (a[l]) {
			_hsh ^= key[l % k];
			_ans -= (l - 1) / k + 1 - (aft[l] << 1);
			// printf("=> %d %d : %d %d\n", key[i % k], (l - 1) / k + 1 - (pre[l] << 1), _hsh, _ans);
		}
		if (a[r]) {
			_hsh ^= key[(r + 1) % k];
			_ans += r / k + 1 - (pre[r + 1] << 1);
			// printf("=> %d %d : %d %d\n", key[(r + 1) % k], r / k + 1 - (pre[r + 1] << 1), _hsh, _ans);
		}
		print(_hsh ? -1 : _ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }
