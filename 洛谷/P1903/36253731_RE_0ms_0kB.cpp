#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}
char readc() {
	char c = getchar();
	while (c != 'Q' && c != 'R') c = getchar();
	return c;
}

const int maxn = 50010;
int n, m, l, r, sqn, p, t, opt, now, z;
int a[maxn], cnt[100010], ans[maxn];
struct Query {
	int l, r, t, i;
} q[maxn];
struct Modify {
	int k, v;
} d[maxn];
bool cmp(Query a, Query b) {
	if (a.l / sqn != b.l / sqn) return a.l < b.l;
	if (a.r / sqn != b.r / sqn) return a.r < b.r;
	return a.t < b.t;
}
void ist(int t) {
//	printf("ist %d\n", t);
	if (!cnt[t]) now++;
	cnt[t]++;
}
void rmv(int t) {
//	printf("rmv %d\n", t);
	cnt[t]--;
	if (!cnt[t]) now--;
}
void upd(int i) {
//	printf("upd %d %d\n", d[i].k, d[i].v);
	if (l <= d[i].k && d[i].k <= r) rmv(a[d[i].k]);
	swap(a[d[i].k], d[i].v);	
	if (l <= d[i].k && d[i].k <= r) ist(a[d[i].k]);
}
int main() {
	n = read(), m = read(), sqn = sqrt(n);
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++)
		if ((opt = readc()) == 'Q') q[++p] = {read(), read(), t, p};
		else d[++t] = {read(), read()};
	sort(q + 1, q + p + 1, cmp);
	l = 1, r = 0, t = 0;
	for (int i = 1; i <= p; i++) {
//		printf(">>> %d %d %d %d\n", q[i].l, q[i].r, q[i].t, q[i].i);
		while (l < q[i].l) rmv(a[l++]);
		while (l > q[i].l) ist(a[--l]);
		while (r > q[i].r) rmv(a[r--]);
		while (r < q[i].r) ist(a[++r]);
		while (t < q[i].t) upd(++t);
		while (t > q[i].t) upd(t--);
		ans[q[i].i] = now;
//		printf(">>> %d\n", now);
	}
	for (int i = 1; i <= p; i++)
		printf("%d\n", ans[i]);
	return 0;
}