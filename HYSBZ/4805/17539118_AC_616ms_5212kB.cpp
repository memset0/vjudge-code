// =================================
//   author: memset0
//   date: 2018.12.23 09:19:16
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
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

const int N = 1e5 + 10;
int T, n, sqn, cnt;
int a[N], h[N], sum[N], prime[N];
int g[N];

inline int id(int x) { 
	return x <= sqn ? x : cnt - n / x + 1;
}

int solve_phi(int a, int b) {
	if (a < prime[b]) return 0;
	int ans = (g[id(a)] - h[id(a)]) - (sum[b - 1] - (b - 1));
	for (int i = b; i <= prime[0] && prime[i] * prime[i] <= a; i++)
		for (int j = 1, x = prime[i], f = x - 1; (ll)x * prime[i] <= a; j++, x *= prime[i], f *= prime[i])
			ans += solve_phi(a / x, i + 1) * f + (ll)f * prime[i];
	return ans;
}

int solve_mu(int a, int b) {
	if (a < prime[b]) return 0;
	int ans = -h[id(a)] + b - 1;
	for (int i = b; i <= prime[0] && prime[i] * prime[i] <= a; i++)
		ans -= solve_mu(a / prime[i], i + 1);
	return ans;
}

void main() {
	cnt = prime[0] = 0;
	read(n), sqn = sqrt(n);
	for (int i = 1; i <= n; i = a[cnt] + 1) {
		a[++cnt] = n / (n / i);
		g[cnt] = (ll)(a[cnt] - 1) * (a[cnt] + 2) / 2;
		h[cnt] = a[cnt] - 1;
	}
	for (int i = 2; i <= sqn; i++)
		if (g[i] != g[i - 1]) {
			prime[++prime[0]] = i, sum[prime[0]] = sum[prime[0] - 1] + i;
			for (int j = cnt, lim = i * i; a[j] >= lim; j--) {
				g[j] -= i * (g[id(a[j] / i)] - sum[prime[0] - 1]);
				h[j] -= (h[id(a[j] / i)] - (prime[0] - 1));
			}
		}
	print(solve_phi(n, 1) + 1, '\n');
}

} signed main() { return ringo::main(), 0; }