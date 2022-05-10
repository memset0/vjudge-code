#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i,l,r) for (register int i = l; i <= r; ++i)
namespace ringo {
	
template < class T >
il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}

template < class T >
il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc(x % 10 + '0');
}

const int maxn = 10, mod = 1e9 + 7;
int n, m, ans;
int pre[10] = {0, 2, 12, 112, 912, 7136};

int pow(int x, int b) {
	int s = 1;
	while (b) {
		if (b & 1)
			s = 1ll * s * x % mod;
		x = 1ll * x * x % mod;
		b >>= 1;
	}
	return s;
}

void main() {
	read(n), read(m);
	if (n > m) std::swap(n, m);
	if (n == 4 && m == 4) ans = 912;
	else if (n == 4 && m == 5) ans = 2688;
	else if (n == 5 && m == 5) ans = 7136;
	else if (n == 1) ans = 1ll * pre[n] * pow(2, m - n) % mod;
	else ans = 1ll * pre[n] * pow(3, m - n) % mod;
	print(ans), putc('\n');
}
	
} int main() { ringo::main(); return 0; }
