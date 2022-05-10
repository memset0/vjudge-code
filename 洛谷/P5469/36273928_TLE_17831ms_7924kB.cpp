// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.06 16:01:47
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 610, M = 5000, mod = 1e9 + 7;
std::vector<int> rec;
bool tag[N], mrk[N][N];
int f[M][N], L[N][N], R[N][N], id[N][N];
int n, cnt, l[M], r[M], a[M], b[M], ifac[M], inte[N], prev[M], next[M];

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

int finv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * finv(mod % x) % mod; }
int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

void init_dfs(int l, int r) {
	if (l > r || mrk[l][r]) return;
	mrk[l][r] = true;
	for (int k = L[l][r]; k <= R[l][r]; k++) if (tag[k]) {
		init_dfs(l, k - 1);
		init_dfs(k + 1, r);
	}
	++cnt, ringo::l[cnt] = l, ringo::r[cnt] = r;
}

void init_fac(int n) {
	ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) ifac[i] = (ll)(mod - mod / i) * ifac[mod % i] % mod;
	for (int i = 1; i <= n; i++) ifac[i] = (ll)ifac[i - 1] * ifac[i] % mod;
}

int inter(int *a, int n, int s, int e) {
	int res = 0, del = e - s + 1, tmp = prev[n + 1];
	prev[n + 1] = next[n + 1] = 1;
	for (int i = n; i >= 1; i--) next[i] = (ll)next[i + 1] * (del - i) % mod;
	// for (int i = 1; i <= n; i++) printf("[%d %d] ", s + i - 1, a[i]);
	for (int i = 1; i <= n; i++) {
		if ((n + i) & 1) sub(res, (ll)a[i] * prev[i - 1] % mod * next[i + 1] % mod * ifac[i - 1] % mod * ifac[n - i] % mod);
		else add(res, (ll)a[i] * prev[i - 1] % mod * next[i + 1] % mod * ifac[i - 1] % mod * ifac[n - i] % mod);
	}
	prev[n + 1] = tmp;
	return res;
}

void main() {
	prev[0] = next[0] = 1;
	memset(tag, 1, sizeof(tag));
	for (int i = 0; i < N; i++) f[0][i] = 1;
	read(n), init_fac(n + 7);
	for (int i = 1; i <= n; i++) {
		read(a[i]), rec.push_back(a[i]);
		read(b[i]), rec.push_back(++b[i]);
	}
	std::sort(rec.begin(), rec.end());
	rec.erase(std::unique(rec.begin(), rec.end()), rec.end());
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++) {
			L[l][r] = R[l][r] = (l + r) >> 1;
			while (L[l][r] > l && std::abs((L[l][r] - 1 - l) - (r - L[l][r] + 1)) <= 2) L[l][r]--;
			while (R[l][r] < r && std::abs((R[l][r] + 1 - l) - (r - R[l][r] - 1)) <= 2) R[l][r]++;
			if (l == r) L[l][r] = R[l][r] + 1;
		}
	init_dfs(1, n);
	for (int i = 1; i <= cnt; i++) id[l[i]][r[i]] = i;
	for (int i = 0; i < rec.size(); i++) {
		int cur = rec[i], nxt = i + 1 == rec.size() ? cur + 1 : rec[i + 1];
		for (int i = 1; i <= n; i++) tag[i] = a[i] <= cur && cur < b[i];
		for (int x = 1; x <= n + 2; x++) {
			for (int l, r, i = 1; i <= cnt; i++) {
				l = ringo::l[i], r = ringo::r[i];
				f[i][x] = f[i][x - 1] + (l == r && tag[l]);
				for (int k = L[l][r]; k <= R[l][r]; k++) if (tag[k])
					f[i][x] = (f[i][x] + (ll)f[id[l][k - 1]][x] * f[id[k + 1][r]][x - 1]) % mod;
			}
			if (cur + x == nxt) {
				for (int i = 1; i <= cnt; i++) f[i][0] = f[i][x];
			}
		}
		for (int i = 1; i <= n + 1; i++) prev[i] = (ll)prev[i - 1] * (nxt - cur - i) % mod;
		if (n + 2 < nxt - cur)
			for (int i = 1; i <= cnt; i++) {
				f[i][0] = inter(f[i], r[i] - l[i] + 2, cur, nxt - 1);
			}
	}
 	print(f[cnt][0], '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}