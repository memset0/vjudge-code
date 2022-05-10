// luogu-judger-enable-o2
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

const int maxn = 400010, p = 998244353, g = 3;
const double pi = acos(-1.0);
int n, m, k, rev[maxn];
long double q[maxn], ans[maxn];

struct complex {
	long double x, y;
	il complex(double a = 0, double b = 0) { x = a, y = b; }
	il complex operator + (const complex &b) const { return complex(x + b.x, y + b.y); }
	il complex operator - (const complex &b) const { return complex(x - b.x, y - b.y); }
	il complex operator * (const complex &b) const { return complex(x * b.x - y * b.y, x * b.y + y * b.x); }
} a[maxn], b[maxn];

void fft(complex *a, int flag) {
	for (int i = 0; i < m; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < m; len <<= 1) {
		complex wn(cos(pi / len), flag * sin(pi / len));
		for (int i = 0; i < m; i += (len << 1)) {
			complex w(1, 0);
			for (int j = 0; j < len; j++, w = w * wn) {
				complex x = a[i + j], y = w * a[i + j + len];
				a[i + j] = x + y, a[i + j + len] = x - y;
			}
		}
	}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) scanf("%Lf", &q[i]);
	m = 1; while (m <= ((n - 1) << 1)) m <<= 1, ++k;
	for (int i = 0; i < m; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int i = 0; i < n; i++) a[i] = complex(q[i], 0);
	for (int i = 0; i < n; i++) b[i] = (double)1 / (i + 1) / (i + 1);
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < m; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 1; i <= n; i++) ans[i] += a[i - 1].x / m;
	// for (int i = 1; i <= n; i++) printf("%.4lf\n", ans[i]);
	// memset(ans, 0, sizeof(ans));
	for (int i = 0; i < n; i++) a[i] = complex(q[n - i], 0);
	fft(a, 1);
	for (int i = 0; i < m; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 1; i < n; i++) ans[i] -= a[n - i - 1].x / m;
	for (int i = 1; i <= n; i++) printf("%.3Lf\n", ans[i]);
}

} int main() { return ringo::main(), 0; }