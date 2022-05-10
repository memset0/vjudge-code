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

const int maxn = 55;
const double eps = 1e-4;

int n, x, max, flag;
double tmp, ans[maxn], f[maxn][maxn];

void main() {
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	read(n);
	rep(i, 1, n) rep(j, 1, n + 1)
		read(x), f[i][j] = x;
	for (int i = 1; i <= n; i++) {
		max = i;
		for (int j = i; j <= n; j++)
			if (fabs(f[j][i]) > fabs(f[max][i]))
				max = j;
		for (int j = i; j <= n + 1; j++)
			std::swap(f[i][j], f[max][j]);
		// rep(i, 1, n) { rep(j, 1, n + 1) printf("%.2lf ", f[i][j]); putc('\n'); } putc('\n');
		if (fabs(f[i][i]) > eps) {
			for (int j = n + 1; j >= i; j--)	
				f[i][j] /= f[i][j];
			for (int j = i + 1; j <= n; j++) {
				for (int k = n + 1; k >= i; k--)
					f[j][k] -= f[i][k] * f[j][i];
			}
		}
		// rep(i, 1, n) { rep(j, 1, n + 1) printf("%.2lf ", f[i][j]); putc('\n'); } putc('\n');
	}
	// rep(i, 1, n) { rep(j, 1, n + 1) printf("%.2lf ", f[i][j]); putc('\n'); }
	flag = 1;
	for (int i = n; i >= 1; i--) {
		if (fabs(f[i][i]) > eps) {
			ans[i] = f[i][n + 1] / f[i][i];
			for (int j = 1; j < i; j++)
				f[j][n + 1] -= f[j][i] * ans[i];
		} else {
			if (fabs(f[i][n + 1]) > eps) flag = -1;
			else flag = 0;
		}
	}
	if (flag != 1) print(flag), putc('\n');
	else {
		for (int i = 1; i <= n; i++) {
			putc('x'), print(i), putc('=');
			if (fabs(ans[i]) > eps) printf("%.2lf\n", ans[i]);
			else putc('0'), putc('\n');
		}
	}
}

} int main() { return ringo::main(), 0; }