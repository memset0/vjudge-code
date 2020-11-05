#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1 << 19 | 5, bloc = 100000;
const long long p1 = 469762049, p2 = 998244353, p3 = 1004535809, p = 1e9 + 7;
int rev[Maxn];
long long fac[Maxn], inv[Maxn], Pow2[Maxn], big_Pow2[Maxn];
void get_rev(int len) {
	for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (len >> 1));
}
long long fast_pow(long long x, long long y, long long mod = p) {
	long long ans = 1, now = x;
	while (y) {
		if (y & 1) ans = ans * now % mod;
		now = now * now % mod;
		y >>= 1;
	}
	return ans;
}
void NTT(long long now[], int len, int p, bool type = false) {
	long long inv3 = fast_pow(3, p - 2, p);
	get_rev(len);
	for (int i = 0; i < len; i++)
		if (i < rev[i]) swap(now[i], now[rev[i]]);
	for (int i = 1; i < len; i <<= 1) {
		long long w = fast_pow(type ? inv3 : 3, (p - 1) / (i << 1), p);
		for (int j = 0; j < len; j += (i << 1)) {
			long long l = 1;
			for (int k = j; k < i + j; k++, l = l * w % p) {
				long long x = now[i + k] * l % p, y = now[k];
				now[k] = (x + y) % p;
				now[i + k] = (y - x + p) % p;
			}
		}
	}
	if (type) {
		long long inv = fast_pow(len, p - 2, p);
		for (int i = 0; i < len; i++) now[i] = now[i] * inv % p;
	}
}
void multi(long long x[], long long y[], long long ans[], int len, int p) {
	get_rev(len);
	static long long tmpx[Maxn], tmpy[Maxn];
	memcpy(tmpx, x, sizeof(long long[len]));
	memcpy(tmpy, y, sizeof(long long[len]));
	NTT(tmpx, len, p), NTT(tmpy, len, p);
	for (int i = 0; i < len; i++) ans[i] = tmpx[i] * tmpy[i] % p;
	NTT(ans, len, p, true);
}
void multi(long long x[], long long y[], int len) {
	static long long ans1[Maxn], ans2[Maxn], ans3[Maxn];
	multi(x, y, ans1, len, p1), multi(x, y, ans2, len, p2), multi(x, y, ans3, len, p3);
	long long inv_p1 = fast_pow(p1, p2 - 2, p2), inv_p12 = fast_pow(p1 * p2 % p3, p3 - 2, p3);
	for (int i = 0; i < len; i++) {
		long long k1 = (ans2[i] - ans1[i] + p2) * inv_p1 % p2;
		long long tmp = (ans1[i] + k1 * p1) % (p1 * p2);
		long long k2 = (ans3[i] - tmp % p3 + p3) * inv_p12 % p3;
		x[i] = (tmp + k2 * p1 % p * p2 % p) % p;
	}
}
long long pow2(int x) { return Pow2[x % bloc] * big_Pow2[x / bloc] % p; }
long long* work(long long now[], int t, int len) {
	static long long tmp[Maxn];
	memset(tmp, 0, sizeof(len));
	for (int i = 0; i < len; i++) tmp[i] = now[i] * pow2(i * t % (p - 1)) % p;
	return tmp;
}
void poly_pow(long long x[], long long ans[], int y, int len) {
	int res = 1, Now = 1;
	static long long now[Maxn];
	memcpy(now, x, sizeof(long long[len]));
	ans[0] = 1;
	while (y) {
		if (y & 1) multi(ans, work(now, res, len << 1), len << 1), res += Now;
		multi(now, work(now, Now, len << 1), len << 1);
		for (int i = len; i < (len << 1); i++) now[i] = ans[i] = 0;
		y >>= 1;
		Now <<= 1;
	}
}
int k;
long long n;
void init(void) {
	fac[0] = 1;
	for (int i = 1; i <= k; i++) fac[i] = fac[i - 1] * i % p;
	inv[k] = fast_pow(fac[k], p - 2);
	for (int i = k - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % p;
	Pow2[0] = big_Pow2[0] = 1;
	for (int i = 1; i <= bloc; i++) Pow2[i] = Pow2[i - 1] * 2 % p;
	for (int i = 1; i <= bloc; i++) big_Pow2[i] = big_Pow2[i - 1] * Pow2[bloc] % p;
}
int lower(int x) {
	int tmp = 1;
	for (; tmp < x; tmp <<= 1)
		;
	return tmp;
}
long long tot, g[Maxn], ans[Maxn];
long long A(int x, int y) { return fac[x] * inv[x - y] % p; }
int main() {
	scanf("%lld%d", &n, &k);
	if (n > k) {
		puts("0");
		return 0;
	}
	k++;
	init();
	for (int i = 1; i < k; i++) g[i] = inv[i];
	poly_pow(g, ans, n, lower(k));
	for (int i = n; i < k; i++) (tot += ans[i] * A(k - 1, i) % p * fast_pow(Pow2[i], p - 2) % p) %= p;
	printf("%lld", tot);
	return 0;
}