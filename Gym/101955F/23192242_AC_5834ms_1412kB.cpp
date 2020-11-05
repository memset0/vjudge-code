// =================================
//   author: memset0
//   date: 2019.08.05 13:28:53
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e4 + 10, W = 1e4 + 10, mod = 1e9 + 7;
std::vector<int> G[N];
int n, m, w, l, r, lim;
int a[N], q[N], ind[N], lst[N], sum1[N], sum2[N], sum3[N];
int pow1[W], pow2[W], pow3[W], src[W], vet[W], val[W], ans[W];

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline int finv(int x) {
	if (x < 2) return 1;
	return (ll)(mod - mod / x) * finv(mod % x) % mod;
}

inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

void main(int CASE) {
	read(n), read(m), read(w);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, u, v; i <= m; i++) {
		read(v), read(u);
		G[u].push_back(v), ind[v]++;
	}
	pow1[0] = pow2[0] = pow3[0] = 1;
	lim = 3 * w + 1;
	for (int f = 1, move; f <= lim; f++) {
		l = r = 0;
		for (int i = 1; i <= n; i++) {
			lst[i] = ind[i];
			if (!ind[i]) q[r++] = i;
		}
		for (int i = 1; i <= lim; i++) pow1[i] = (ll)pow1[i - 1] * f % mod;
		for (int i = 1; i <= lim; i++) pow2[i] = (ll)pow1[i] * pow1[i] % mod;
		for (int i = 1; i <= lim; i++) pow3[i] = (ll)pow1[i] * pow2[i] % mod;
		for (int i = 1; i <= n; i++) {
			sum1[i] = pow1[a[i]];
			sum2[i] = pow2[a[i]];
			sum3[i] = pow3[a[i]];
		}
		while (l < r) {
			int u = q[l++];
			for (auto v : G[u]) {
				add(sum1[v], sum1[u]);
				add(sum2[v], sum2[u]);
				add(sum3[v], sum3[u]);
				if (!--lst[v]) q[r++] = v;
			}
		}
		for (int i = 1; i <= n; i++) {
			int s1 = sum1[i], s2 = sum2[i], s3 = sum3[i];
			move = ((ll)s1 * s1 % mod * s1- 3ll * s1 * s2 % mod + 2 * s3) % mod;
			add(val[f], move < 0 ? move + mod : move);
		}
	}
	src[0] = 1;
	for (int i = 1; i <= lim; i++) {
		for (int j = 0; j < i; j++) vet[j] = src[j];
		src[0] = (ll)src[0] * (mod - i) % mod, vet[i] = 0;
		for (int j = 1; j <= i; j++) src[j] = (vet[j - 1] + (ll)vet[j] * (mod - i)) % mod;
	}
	for (int i = 1, v, iv; i <= lim; i++) {
		iv = finv(v = mod - i);
		for (int j = 0; j <= lim; j++) vet[j] = src[j];
		for (int j = lim - 1; j >= 0; j--) sub(vet[j], (ll)vet[j + 1] * v % mod);
		for (int j = 0; j < lim; j++) vet[j] = vet[j + 1];
		vet[lim] = 0; ll d = 1;
		for (int j = 1; j <= lim; j++) if (i != j) (d *= (i - j + mod)) %= mod;
		d = (ll)finv(d) * val[i] % mod;
		for (int i = 0; i < lim; i++) add(ans[i], d * vet[i] % mod);
	}
	printf("Case #%d: ", CASE);
	for (int i = 1, d = finv(6); i < lim; i++)
		print((ll)d * ans[i] % mod, " \n"[i == lim - 1]);
}

void clear() {
	for (int i = 1; i <= n; i++) G[i].clear();
#define clear(x) memset((x), 0, sizeof((x)))
	clear(ind), clear(src), clear(ans), clear(val), clear(sum1), clear(sum2), clear(sum3);
#undef clear
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	int T; ringo::read(T);
	for (int i = 1; i <= T; i++) ringo::main(i), ringo::clear();
}