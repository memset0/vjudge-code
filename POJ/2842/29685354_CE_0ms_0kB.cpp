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

const int maxn = 4010;
int n, m, tn, ans;
int l[maxn], r[maxn], a[maxn], b[maxn], vis[maxn];

int main() {
//	freopen("INPUT", "r", stdin);
	read(m), read(n);
	for (int i = 1; i <= n; i++) {
		read(l[i]), read(r[i]);
		b[++tn] = l[i], b[++tn] = r[i];
		b[++tn] = l[i] + 1, b[++tn] = r[i] + 1;
	}
	std::sort(b + 1, b + tn + 1);
	tn = std::unique(b + 1, b + tn + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		l[i] = std::lower_bound(b + 1, b + tn + 1, l[i]) - b;
		r[i] = std::lower_bound(b + 1, b + tn + 1, r[i]) - b;
	}
//	for (int i = 1; i <= tn; i++)
//		print(b[i]); putc('\n');
//	for (int i = 1; i <= n; i++)
//		printf("%d %d\n", l[i], r[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = l[i]; j <= r[i]; j++)
			a[j] = i;
	}
//	for (int i = 1; i <= tn; i++)
//		print(a[i]); putc('\n');
	for (int i = 1; i <= tn; i++)
		if (!vis[a[i]] && a[i]) {
			vis[a[i]] = 1;
			ans++;
		}
	print(ans, '\n');
	return 0;
}

