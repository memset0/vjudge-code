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

const int N = 1e5 + 10;
int n, m, k, sqn, sqm, cnt, nod1, nod2;
int vis[N], pri[N], mu[N], f[N], a1[N], g1[N], s1[N], a2[N], g2[N], s2[N];

inline int gcd(int n, int m) { return !m ? n : gcd(m, n % m); }
inline int id1(int x) { return x <= sqn ? x : nod1 - n / x + 1; }
inline int id2(int x) { return x <= sqm ? x : nod2 - m / x + 1; }
inline int G(int n) { return n <= k ? f[n] : (n / k) * f[k] + G(n % k); }

inline int calc(int n) {
	int res = 0;
	for (int i = 2; i <= n; i++) res += mu[i];
	return res;
}

inline int S(int n, int k) {
	if (k == 1) {
		return (m / (m / n) == n ? s2[id2(n)] : s1[id1(n)]) + 1;
	}
	int res = 0;
	for (int i = 1; i * i <= k; i++)
		if (k % i == 0) {
		if (i <= n && mu[i]) res += S(n / i, i);
		if (i * i != k && k / i <= n && mu[k / i]) res += S(n / (k / i), k / i);
	}
	return res;
}

void main() {
	read(n), read(m), read(k);
	mu[1] = -1;
	for (int i = 1; i <= k; i++) f[i] = f[i - 1] + (gcd(i, k) == 1);
	for (int i = 2; i <= k; i++) {
		if (!vis[i]) { pri[++cnt] = i, mu[i] = -1; }
		for (int j = 1; j <= cnt && i * pri[j] <= k; j++) {
			vis[i * pri[j]] = 1;			if (i % pri[j] == 0) break;
			else mu[i * pri[j]] = mu[i] * -1;
		}
	}
	sqn = sqrt(n), sqm = sqrt(m);
	for (int i = 1; i <= n; i = a1[nod1] + 1) a1[++nod1] = n / (n / i);
	for (int i = 1; i <= m; i = a2[nod2] + 1) a2[++nod2] = m / (m / i);
	cnt = 0;
	for (int i = 1; i <= nod1; i++) g1[i] = a1[i] - 1;
	for (int i = 2; i <= sqn; i++) if (g1[i] != g1[i - 1]) {
		pri[++cnt] = i;
		for (int j = nod1; a1[j] >= i * i; j--) g1[j] -= g1[id1(a1[j] / i)] - cnt + 1;
	}
	for (int i = 1; i <= nod1; i++) s1[i] = -g1[i];
	for (int i = cnt; i; i--)
		for (int j = nod1; a1[j] >= pri[i] * pri[i]; j--) {
			s1[j] -= s1[id1(a1[j] / pri[i])] + i;
		}
	cnt = 0;
	for (int i = 1; i <= nod2; i++) g2[i] = a2[i] - 1;
	for (int i = 2; i <= sqm; i++) if (g2[i] != g2[i - 1]) {
		pri[++cnt] = i;
		for (int j = nod2; a2[j] >= i * i; j--) g2[j] -= g2[id2(a2[j] / i)] - cnt + 1;
	}
	for (int i = 1; i <= nod2; i++) s2[i] = -g2[i];
	for (int i = cnt; i; i--)
		for (int j = nod2; a2[j] >= pri[i] * pri[i]; j--) {
			s2[j] -= s2[id2(a2[j] / pri[i])] + i;
		}
	// for (int i = 1; i <= nod1; i++) printf("AAA %d %d %d\n", a1[i], s1[i], calc(a1[i]));
	// for (int i = 1; i <= nod2; i++) printf("BBB %d %d %d\n", a2[i], s2[i], calc(a2[i]));
	ll ans = 0;
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