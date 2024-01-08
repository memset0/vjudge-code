// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.12 08:39:22
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

const int N = 1e4 + 10;
int n, m, k, sqn, cnt, nod;
int vis[N], pri[N], mu[N], f[N], g[N], h[N], a[N], s[N];

inline int gcd(int n, int m) { return !m ? n : gcd(m, n % m); }
inline int id(int x) { return x <= sqn ? x : nod - n / x + 1; }
inline int G(int n) { return n <= k ? f[n] : (n / k) * f[k] + G(n % k); }

inline int calc(int n) {
	int res = 0;
	for (int i = 2; i <= n; i++) res += mu[i];
	return res;
}

inline int S(int n, int k) {
	if (k == 1) {
		// printf("%d : %d\n", n, id(n));
		return s[id(n)] + 1;
	}
	int res = 0;
	for (int i = 1; i <= n && i <= k; i++) {
		if (k % i == 0 && mu[i]) res += S(n / i, i);
	}
	return res;
}

void main() {
	read(n), read(m), read(k);
	mu[1] = -1;
	for (int i = 1; i <= k; i++) f[i] = f[i - 1] + (gcd(i, k) == 1);
	for (int i = 2; i <= std::max(n, m); i++) {
		if (!vis[i]) { pri[++cnt] = i, mu[i] = -1; }
		for (int j = 1; j <= cnt && i * pri[j] <= std::max(n, m); j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
			else mu[i * pri[j]] = mu[i] * -1;
		}
	}
	sqn = sqrt(n), cnt = 0;
	for (int i = 1; i <= n; i = a[nod] + 1) a[++nod] = n / (n / i);
	for (int i = 1; i <= nod; i++) g[i] = a[i] - 1;
	for (int i = 2; i <= sqn; i++) if (g[i] != g[i - 1]) {
		pri[++cnt] = i;
		for (int j = nod; a[j] >= i * i; j--) g[j] -= g[id(a[j] / i)] - cnt + 1;
	}
	for (int i = 1; i <= nod; i++) s[i] = -g[i];
	for (int i = cnt; i; i--)
		for (int j = nod; a[j] >= pri[i] * pri[i]; j--) {
			// printf("%d[%d] %d[%d] %d[%d] : %d => %d\n", i, pri[i], j, a[j], id(a[j] / pri[i]), a[j] / pri[i], s[j], s[id(a[j] / pri[i])] - i);
			s[j] -= s[id(a[j] / pri[i])] + i;
		}
	ll ans = 0;
	// for (int i = 1; i <= nod; i++) printf("> %d %d\n", s[i], calc(a[i]));
	for (int l = 1, r; l <= n && l <= m; l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ans += (ll)(n / l) * G(m / l) * (S(r, k) - S(l - 1, k));
	}
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