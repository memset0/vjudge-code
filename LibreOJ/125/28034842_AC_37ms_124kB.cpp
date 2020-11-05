#include <cstdio>

const int mod = 998244353, inv2 = 499122177, inv6 = 166374059;
int n, ans, ans0, ans1, ans2;

inline int f(int n) { return 1ll * n * (n + 1) % mod; }
inline int g(int n) { return 1ll * n * (n + 1) % mod * (n + n + 1) % mod; }

int main() {
	scanf("%d", &n);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans0 = (ans0 + 1ll * (n / l) * (g(r) - g(l - 1))) % mod;
		ans1 = (ans1 + 1ll * (n / l) * (f(r) - f(l - 1))) % mod;
		ans2 = (ans2 + 1ll * (n / l) * (r - l + 1)) % mod;
	}
	ans = (ans + 2ll * ans0 * inv6) % mod;
	ans = (ans + 3ll * ans1 * inv2) % mod;
	ans = (ans + 5ll * ans2) % mod;
	printf("%d\n", (ans + mod) % mod);
}
