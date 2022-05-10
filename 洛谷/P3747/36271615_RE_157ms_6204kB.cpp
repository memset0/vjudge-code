// luogu-judger-enable-o2
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
#define endl ('\n')

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 200010;

int n, m, c, p, l, r, opt, maxp;
bool flag;

int a[maxn], phi[50];

struct node {
	int l, r, mid;
	int min, sum;
} e[maxn << 2]; 

int pow(int a, int b, int p) {
	ll x = a, y = 1;
	while (b) {
		if (b & 1) {
			y = y * x;
			if (y > p) {
				flag = 1;
				y %= p;
			}
		}
		x = x * x;
		if (x > p) {
			flag = 1;
			x %= p;
		}
		b >>= 1;
	}
	return y;
}

int calc(int x, int k) {
//	printf("calc %d %d %d\n", x, k, phi[k]);
	if (x > phi[k + 1]) x = x % phi[k + 1] + phi[k + 1]; 
	for (int i = 1; i <= k; i++) {
		flag = 0;
		x = pow(c, x, phi[k + 1 - i]);
		if (flag) x += phi[k + 1 - i];
	}
//	printf("=> %d\n", x);
	return x;
}

void build(int u, int l, int r) {
	e[u].l = l, e[u].r = r, e[u].mid = (l + r) >> 1;
	if (l == r) { e[u].sum = a[l] % p; return; }
	build(u << 1, l, e[u].mid);
	build(u << 1 | 1, e[u].mid + 1, r);
	e[u].sum = (e[u << 1].sum + e[u << 1 | 1].sum) % p;
	e[u].min = std::min(e[u << 1].min, e[u << 1 | 1].min);
}

void modify(int u, int l, int r) {
	if (e[u].min > maxp) return;
	if (e[u].l == e[u].r) {
		e[u].min++;
		e[u].sum = calc(a[l], e[u].min) % p;
		return;
	}
	if (r <= e[u].mid) modify(u << 1, l, r);
	else if (l > e[u].mid) modify(u << 1 | 1, l, r);
	else {
		modify(u << 1, l, e[u].mid);
		modify(u << 1 | 1, e[u].mid + 1, r);
	}
	e[u].sum = (e[u << 1].sum + e[u << 1 | 1].sum) % p;
	e[u].min = std::min(e[u << 1].min, e[u << 1 | 1].min);
}

int query(int u, int l, int r) {
	if (e[u].l == l && e[u].r == r)
		return e[u].sum;
	if (r <= e[u].mid) return query(u << 1, l, r);
	else if (l > e[u].mid) return query(u << 1 | 1, l, r);
	else return (query(u << 1, l, e[u].mid) +
		query(u << 1 | 1, e[u].mid + 1, r)) % p;
}

int calc_phi(int x) {
	if (x == 1) return 1;
	int t = x;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) {
			t = t / i * (i - 1);
			while (x % i == 0)
				x /= i;
		}
	if (x ^ 1)
		t = t / x * (x - 1);
	return t;
}

void init() {
	phi[++maxp] = p;
	while (phi[maxp] ^ 1)
		phi[maxp + 1] = calc_phi(phi[maxp]), ++maxp;
	phi[++maxp] = 1;
	build(1, 1, n);
}

int main() {
	read(n), read(m), read(p), read(c);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	init();
	for (int i = 1; i <= m; i++) {
		read(opt), read(l), read(r);
		if (opt) {
			print(query(1, l, r), endl);
		} else {
			modify(1, l, r);
		}
	}
	return 0;
}