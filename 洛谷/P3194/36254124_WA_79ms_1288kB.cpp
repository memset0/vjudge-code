// ==============================
//  author: memset0
//  website: https://memset0.cn
//  note: _rqy 又强又可爱
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
template <typename T> inline void print(T x, char c = '\n') {
	static int buf[40];
	if (x < 0) putc('-'), x = -x; else if (x == 0) putc('0');
	else {
		for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
		while (buf[0]) putc((char) buf[buf[0]--]);
	} putc(c);
}

const int maxn = 50010;
const long double eps = 1e-19;

int n, top;
int s[maxn], ans[maxn];

struct edge {
	int k, b, i;;
} a[maxn];

bool cmp(const edge &a, const edge &b) {
	if (a.k != b.k) return a.k < b.k;
	return a.b > b.b;
}

long double cross(const edge &a, const edge &b) {
//	printf("(%d %d) cross (%d %d)\n", a.k, a.b, b.k, b.b);
//	printf("<<< %.2lf\n", (b.b - a.b) / (double) (a.k - b.k));
	return (b.b - a.b) / (long double) (a.k - b.k);
}

bool better(int i) {
	if (a[s[top]].k == a[i].k && top)
		return true;
	if (top > 1) {
		long double f = cross(a[i], a[s[top]]) - cross(a[s[top]], a[s[top - 1]]);
//		printf("%.2Lf %d\n", f, f >= -eps);
		if (f >= -eps) return true; // f >= 0
	}
	return false;
}

int main() {
//	freopen("INPUT", "r", stdin);
//	freopen("OUTPUT", "w", stdout);

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i].k);
		read(a[i].b);
		a[i].i = i;
	}
	std::sort(a + 1, a + n + 1, cmp);
	
	for (int i = 1; i <= n; i++) {
//		printf("(%d) %d %d %d \n", i, a[i].k, a[i].b, a[i].i);
		while (better(i))
			top--;
		s[++top] = i;
//		printf("%.2lf %.2lf %d %d %d\n", cross(a[s[top]], a[s[top - 1]]), cross(a[i], a[s[top]]), s[top - 1], s[top], i);
	}
	
	for (int i = 1; i <= top; i++)
		ans[i] = a[s[i]].i;
	std::sort(ans + 1, ans + top + 1);
	for (int i = 1; i <= top; i++)
		print(ans[i], ' ');
	putc('\n');

	return 0;
}