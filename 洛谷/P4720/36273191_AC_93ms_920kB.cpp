// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.04 11:23:52
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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
int n, m, p;

namespace ExLucas {
void exgcd(int a, int b, int &x, int &y) {
	if (b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, x, y);
	int tmp = y; y = x - y * (a / b), x = tmp;
}
inline int inv(int a, int p) {
	int x, y; exgcd(a, p, x, y);
	return (x % p + p) % p;
}
inline int fmul(int a, int b, int p) {
	int s = 0;
	for (; b; b >>= 1, a <<= 1, a = a >= p ? a - p : a)
		if (b & 1) s += a, s = s >= p ? s - p : s;
	return s;
}
inline int fpow(int a, int b, int p) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % p)
		if (b & 1) s = (ll)s * a % p;
	return s;
}
inline int ex_fac(int n, int pi, int pk) {
	if (n < 1) return 1; int ans = 1;
    for (int i = 2; i <= pk; i++)
        if (i % pi) (ans *= i) %= pk;
	ans = fpow(ans, n / pk, pk);
    for (int i = 2; i <= n % pk; i++)
        if (i % pi) (ans *= i) %= pk;
    return ans * ex_fac(n / pi, pi, pk) % pk;
}
inline int ex_fac_k(int n, int pi, int pk) {
	int sum = 0;
	for (int tmp = n; tmp; tmp /= pi) sum += tmp / pi;
	return sum;
}
inline int ex_binom(int n, int m, int pi, int pk) {
	// printf(">> ex_binom %d %d %d %d\n", n, m, pi, pk);
	int d0 = ex_fac(n, pi, pk), d1 = ex_fac(m, pi, pk), d2 = ex_fac(n - m, pi, pk);
	int k = ex_fac_k(n, pi, pk) - ex_fac_k(m, pi, pk) - ex_fac_k(n - m, pi, pk);
	// printf(">> %d %d %d %d | %d %d\n", d0, d1, d2, k, inv(d1, pk), inv(d2, pk));
	return (ll)fpow(pi, k, pk) * d0 % pk * inv(d1, pk) % pk * inv(d2, pk) % pk;
}
inline int crt(const std::vector <std::pair <int, int> > &vet, int p) {
	int sum = 0, res, mod;
	if (vet.size() == 1) return vet.begin()->first;
	// for (std::vector <std::pair <int, int> > ::const_iterator it = vet.begin(); it != vet.end(); it++)
	// 	printf("%d %d\n", it->first, it->second);
	for (std::vector <std::pair <int, int> > ::const_iterator i = vet.begin(); i != vet.end(); i++) {
		res = i->first, mod = 1;
		for (std::vector <std::pair <int, int> > ::const_iterator j = vet.begin(); j != vet.end(); j++) if (i != j)
			res = (ll)res * j->second % p, mod = (ll)mod * j->second % i->second;
		sum = (sum + (ll)res * inv(mod, i->second)) % p;
	} return sum;
}
inline int ex_lucas(int n, int m, int p) {
	int tmp = p; std::vector <std::pair <int, int> > vet;
	for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
		int k = 1; while (tmp % i == 0) tmp /= i, k *= i;
		vet.push_back(std::make_pair(ex_binom(n, m, i, k), k));
	}
	if (tmp != 1) vet.push_back(std::make_pair(ex_binom(n, m, tmp, tmp), tmp));
	return crt(vet, p);
}
} // end namespace ExLucas
using ExLucas::ex_lucas;

void main() {
	read(n), read(m), read(p);
	print(ex_lucas(n, m, p), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}