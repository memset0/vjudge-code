#include <bits/stdc++.h>
const int N = 2e3 + 10;
int n, m, mod;

namespace fastMod {
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b;	// can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
}  // namespace fastMod
using Moder = fastMod::FastMod;
Moder moder(2);

struct z {
	int x;
	z(int x = 0) : x(x) {}
	friend inline z operator*(z a, z b) {
		return moder.reduce((long long)a.x * b.x);
	}
	friend inline z operator-(z a, z b) {
		return (a.x -= b.x) < 0 ? a.x + mod : a.x;
	}
	friend inline z operator+(z a, z b) {
		return (a.x += b.x) >= mod ? a.x - mod : a.x;
	}
} inv[N << 1], inw[N << 1];
z f[N][N][3][3], g[N][N][3][3];	 // 0 all | 1 next | 2 another
inline z fpow(z a, int b) {
	z s = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) s = s * a;
	return s;
}

void init(int n = N) {
	inv[0] = inv[1] = 1;
	for (int i = 2; i < n; i++) inv[i] = (mod - mod / i) * inv[mod % i];
	for (int i = 0; i < n; i++) inw[i] = 1 - inv[i];
}

void eval(z a, z b, z c, z d, z& f, z& g) {
	g = (a * d + c) * fpow(1 - d * b, mod - 2);
	f = b * g + a;
}

#define FNM f[n][m]
#define FnM f[n - 1][m]
#define FNm f[n][m - 1]
#define Fnm f[n - 1][m - 1]

#define GNM g[n][m]
#define GnM g[n - 1][m]
#define GNm g[n][m - 1]
#define Gnm g[n - 1][m - 1]

void dfs(int n, int m) {
	// printf("DFS %d %d\n", n, m);
	if (n == 0 || m == 0) {
		memset(FNM, 0, sizeof(FNM));
		memset(GNM, 0, sizeof(GNM));
		return;
	}
	if (n == 1 || m == 1) {
		for (int x = 0; x < 3; ++x)
			for (int y = 0; y < 3; ++y) { FNM[x][y] = GNM[x][y] = 2; }
		return;
	}

	FNM[1][0] = GnM[0][1] * inv[m] + GnM[0][0] * inw[m] + 1;
	FNM[1][1] = Gnm[0][0] * inv[m] + GnM[0][0] * inw[m] + 1;
	FNM[1][2] = Gnm[0][0] * inv[m] + GnM[0][1] * inv[m] +
		GnM[0][0] * (1 - inv[m] - inv[m]) + 1;

	GNM[0][1] = FNm[1][0] * inv[n] + FNm[0][0] * inw[n] + 1;
	GNM[1][1] = Fnm[0][0] * inv[n] + FNm[0][0] * inw[n] + 1;
	GNM[2][1] = Fnm[0][0] * inv[n] + FNm[0][0] * (1 - inv[n] - inv[n]) +
		FNm[1][0] * inv[n] + 1;

	FNM[0][2] = GNm[2][0] * inv[m] + GNM[2][1] * inv[m] +
		GNM[2][0] * (1 - inv[m] - inv[m]) + 1;
	GNM[2][0] = FnM[0][2] * inv[n] + FNM[0][2] * (1 - inv[n] - inv[n]) +
		FNM[1][2] * inv[n] + 1;

	eval(GNM[2][1] * inv[m] + GNm[2][0] * inv[m] + 1, 1 - inv[m] - inv[m],
		 FNM[1][2] * inv[n] + FnM[0][2] * inv[n] + 1, 1 - inv[n] - inv[n],
		 FNM[0][2], GNM[2][0]);

	FNM[0][0] = GNM[2][1] * inv[m] + GNM[2][0] * inw[m] + 1;
	FNM[0][1] = GNm[2][0] * inv[m] + GNM[2][0] * inw[m] + 1;
	GNM[0][0] = FNM[1][2] * inv[n] + FNM[0][2] * inw[n] + 1;
	GNM[1][0] = FnM[0][2] * inv[n] + FNM[0][2] * inw[n] + 1;

	// printf("%d %d\n", n, m);
	// printf("FNM => ");
	// for (int i = 0; i < 3; i++)
	// 	for (int j = 0; j < 3; j++) printf("%d ", FNM[i][j].x);
	// puts("");
	// printf("GNM => ");
	// for (int i = 0; i < 3; i++)
	// 	for (int j = 0; j < 3; j++) printf("%d ", GNM[i][j].x);
	// puts("");
}

int main() {
#ifdef memset0
	freopen("data.in", "r", stdin);
#endif
	std::cin >> n >> m >> mod, moder = Moder(mod), init();
	std::tie(n, m) = std::make_pair(std::max(n, m), std::min(n, m));
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j) dfs(i, j);
	std::cout << f[n][m][0][0].x << std::endl;
	fprintf(stderr, "clocks: %.4lf\n", clock() / (double)CLOCKS_PER_SEC);
}