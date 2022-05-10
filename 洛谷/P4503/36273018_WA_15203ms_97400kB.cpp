// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 30010, maxm = 210;
const int M = 1000000007;
const int P1 = 19260817;
const int P2 = 20040301;

int n, m, t, ans;
int a[maxm];
char s[maxm];

int now1, val1, invM1, mul1[maxm], l1[maxm], r1[maxm];
int now2, val2, invM2, mul2[maxm], l2[maxm], r2[maxm];

typedef std::map < int, int > map;
typedef map::iterator iterator;

map map1, map2;

int change(char c) {
	if ('a' <= c && c <= 'z') return c - 'a' + 1;
	if ('A' <= c && c <= 'Z') return c - 'A' + 27;
	if ('0' <= c && c <= '9') return c - '0' + 53;
	if (c == '_') return 63;
	if (c == '@') return 64;
}

int inv(int x, int p) {
	if (x == 0 || x == 1) return 1;
	return 1ll * (p - p / x) * inv(p % x, p) % p;
}

int main() {
	// freopen("1.in", "r", stdin);

	read(n), read(m), read(t);
	// printf(">>> %d %d %d\n", n, m, t);
	invM1 = inv(M % P1, P1);
	invM2 = inv(M % P2, P2);
	mul1[0] = mul2[0] = 1;
	for (int i = 1; i <= m; i++) {
		mul1[i] = 1ll * mul1[i - 1] * M % P1;
		mul2[i] = 1ll * mul2[i - 1] * M % P2;
	}
	// printf("%lld %lld\n", invM1, invM2);
	for (int k = 1; k <= n; k++) {
		scanf("%s", s + 1);
		for (int i = 1; i <= m; i++)
			a[i] = change(s[i]);
		for (int i = 1; i <= m; i++) {
			l1[i] = (1ll * l1[i - 1] * M + a[i]) % P1;
			l2[i] = (1ll * l2[i - 1] * M + a[i]) % P2;
		}
		for (int i = m; i >= 1; i--) {
			r1[i] = (1ll * r1[i + 1] * invM1 + a[i]) % P1;
			r2[i] = (1ll * r2[i + 1] * invM2 + a[i]) % P1;
		}
		for (int i = 1; i <= m; i++) {
			r1[i] = 1ll * r1[i] * mul1[m - 1] % P1;
			r2[i] = 1ll * r2[i] * mul2[m - 1] % P2;
		}
		for (int i = 1; i <= m; i++) {
			now1 = (1ll * l1[i - 1] * mul1[m - i] + r1[i + 1]) % P1;
			now2 = (1ll * l2[i - 1] * mul2[m - i] + r2[i + 1]) % P2;
			val1 = map1[now1];
			val2 = map2[now2];
			// printf("%d %d %d %d\n", l1[i - 1], r1[i + 1], now1, val1);
			// printf("%d %d %d %d\n", l2[i - 1], r2[i + 1], now2, val2);
			if (val1 == val2) {
				ans += val1;
				map1[now1] = val1 + 1;
				map2[now2] = val2 + 1;
			} else {
				map1[now1] = 1;
				map2[now2] = 1;
			}
		}
		// putc('\n');
	}
	print(ans, '\n');

	return 0;
}