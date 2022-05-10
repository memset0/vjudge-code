#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
long long read(void);
char readchar(void);
int n, m, l, r;
char d;
long long a[maxn], s[maxn], c, ans;
struct Node {
	int l, r, mid, val, dt;
} p[maxn * 8];
void build (int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) / 2;
	p[u].val = p[u].dt = 0;
	if (l == r) return ;
	build(u << 1, l, p[u].mid);
	build((u << 1) + 1, p[u].mid + 1, r);
}
void insert(int u, int l, int r, long long c) {
	if (l == p[u].l && r == p[u].r) {
		p[u].dt += c;
		return ;
	} else p[u].val += c * (r - l + 1);
//	printf(">> %d %d => [%d %d %d, %d %d]\n", l, r, u, p[u].l, p[u].r, p[u].val, p[u].dt);
	if (r <= p[u].mid) insert(u << 1, l, r, c);
	else if (l > p[u].mid) insert((u << 1) + 1, l, r, c);
	else {
		insert(u << 1, l, p[u].mid, c);
		insert((u << 1) + 1, p[u].mid + 1, r, c);
	}
}
void lookup(int u, int l, int r) {
	if (p[u].dt) {
		p[u].val += p[u].dt * (p[u].r - p[u].l + 1);
		p[u << 1].dt += p[u].dt;
		p[(u << 1) + 1].dt += p[u].dt;
		p[u].dt = 0;
	}
//	printf(">> %d %d => [%d %d %d, %d]\n", l, r, u, p[u].l, p[u].r, p[u].val);
	if (l == p[u].l && r == p[u].r) {
		ans += p[u].val;
		return ;
	}
	if (r <= p[u].mid) lookup(u << 1, l, r);
	else if (l > p[u].mid) lookup((u << 1) + 1, l, r);
	else {
		lookup(u << 1, l, p[u].mid);
		lookup((u << 1) + 1, p[u].mid + 1, r);
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), s[i] = s[i - 1] + a[i];
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		d = readchar();
		if (d == '1') {
			l = read(), r = read(), c = read();
			insert(1, l, r, c);
		} else {
			l = read(), r = read();
			ans = 0;
			lookup(1, l, r);
			printf("%lld\n", ans + s[r] - s[l - 1]);
//			printf(">> ");
//			for (int i = 1; i <= n; i++) {
//				ans = 0;
//				lookup(1, i, i);
//				printf("%d ", ans + a[i]);
//			}
//			printf("\n");
		}
	}
	return 0;
}

long long ret; char chr; bool mrk;
long long read(void) {
	ret = 0, chr = getchar(), mrk = 0;
	while (!isdigit(chr) && chr != '-') chr = getchar();
	if (chr == '-') mrk = 1, chr = getchar();
	while (isdigit(chr)) ret = ret * 10 + chr - '0', chr = getchar();
	if (mrk) return -ret; else return ret;
}
char readchar(void) {
	chr = getchar();
	while (!(islower(chr) || isupper(chr) || isdigit(chr))) chr = getchar();
	return chr;
}