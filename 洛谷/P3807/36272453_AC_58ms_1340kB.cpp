#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T > il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}

template < class T > il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc('0' + x % 10);
}

const int maxn = 100010;
int T, n, m, p, fac[maxn], inv[maxn];

int c(int n, int m) {
	if (n > m) return 0;
	// printf("C %d %d : %lld\n", n, m, 1ll * fac[m] * inv[m - n] % p * inv[n] % p);
	return 1ll * fac[m] * inv[m - n] % p * inv[n] % p;
}

int lucas(int n, int m) {
	if (m == 0) return 1;
	// printf("lucas %d %d : %d %d\n", n, m, c(n % p, m % p), lucas(n / p, m / p));
	return 1ll * c(n % p, m % p) * lucas(n / p, m / p) % p;
}

void main() {
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	for (read(T); T--; ) {
		read(n), read(m), read(p);
		fac[0] = fac[1] = inv[0] = inv[1] = 1;
		rep(i, 2, p - 1) fac[i] = 1ll * fac[i - 1] * i % p;
		rep(i, 2, p - 1) inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
		rep(i, 2, p - 1) inv[i] = 1ll * inv[i - 1] * inv[i] % p;
		print(lucas(m, n + m)), putc('\n');
	}
}

} int main() { return ringo::main(), 0; }
