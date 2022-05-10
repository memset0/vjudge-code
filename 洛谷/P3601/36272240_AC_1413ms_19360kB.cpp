// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.04 20:59:09
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

const int N = 1e6 + 10;
ll L, R, ans, pow[N], phi[N], lst[N];
int c_pri, pri[N];
bool vis[N];

void main() {
	read(L), read(R);
	for (int i = 2, lim = sqrt(R); i <= lim; i++) {
		if (!vis[i]) pri[++c_pri] = i;
		for (int j = 1; j <= c_pri && i * pri[j] <= lim; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) continue;
		}
	}
	for (ll i = L; i <= R; i++) phi[i - L] = 1, lst[i - L] = i;
	pow[0] = 1;
	for (int i = 1, x, cnt; i <= c_pri; i++) {
		x = pri[i];
		for (int i = 1; pow[i - 1] <= R; i++)
			pow[i] = pow[i - 1] * x;
		for (ll t, j = L % x ? (L / x + 1) * x : L; j <= R; j += x) {
			for (cnt = 0; lst[j - L] % x == 0; lst[j - L] /= x, ++cnt);
			if (cnt == 1) phi[j - L] *= (x - 1);
			else phi[j - L] *= (x - 1) * pow[cnt - 1];
		}
	}
	for (int i = 0; i <= R - L; i++) if (lst[i] != 1) phi[i] *= lst[i] - 1;
	// ans = (R - L + 1) * (L + R) / 2;
	// for (int i = 0; i <= R - L; i++) print(phi[i], " \n"[i == R - L]);
	for (int i = 0; i <= R - L; i++) ans += i + L - phi[i];
	print(ans % 666623333, '\n');
}

} signed main() { return ringo::main(), 0; }