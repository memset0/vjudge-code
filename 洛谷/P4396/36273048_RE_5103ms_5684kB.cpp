// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)

int read() {
	int x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') m = 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}

const int maxn = 100010;

#define lowbit(x) ((x)&(-(x)))

int n, m, l, r, x, y, tn, ql, qr, sqn;
int a[maxn], b[maxn], bln[maxn], cnt[maxn], s[2][maxn], ans[2][maxn];

struct query {
	int l, r, x, y, i;
} q[maxn];
bool operator < (const query &x, const query &y) {
	if (bln[x.l] ^ bln[y.l]) return x.r < y.r;
	return x.l < y.l;
}

void modify(int i, int x, int k) {
	i++;
	for (; i <= n + 1; i += lowbit(i))
		s[k][i] += x;
}

int query(int i, int k) {
	int ret = 0;
	i++;
	for (; i >= 2; i -= lowbit(i))
		ret += s[k][i];
	return ret; 
}

void add(int x) {
	if (!cnt[x]) {
		modify(x, 1, 1);
	}
	modify(x, 1, 0);
	cnt[x]++;
}

void del(int x) {
	modify(x, -1, 0);
	cnt[x]--;
	if (!cnt[x]) {
		modify(x, -1, 1);
	}
}

int main() {

	n = read(), m = read(), sqn = n / sqrt(m * 2.0 / 3);
	for (int i = 1; i <= n; i++)
		bln[i] = i / sqn;
	
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		b[i] = a[i];
	tn = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
	
	for (int i = 1; i <= m; i++) {
		q[i].l = read(), q[i].r = read();
		q[i].x = read(), q[i].y = read();
		q[i].i = i;
	}
	std::sort(q + 1, q + m + 1);
	
	ql = 1, qr = 0; 
	for (int i = 1; i <= m; i++) {
		l = q[i].l, r = q[i].r;
		x = q[i].x, y = q[i].y;
		while (ql < l) del(a[ql++]);
		while (ql > l) add(a[--ql]);
		while (qr > r) del(a[qr--]);
		while (qr < r) add(a[++qr]);
		ans[0][q[i].i] = query(y, 0) - query(x - 1, 0);
		ans[1][q[i].i] = query(y, 1) - query(x - 1, 1);
	}
	
	for (int i = 1; i <= m; i++)
		printf("%d %d\n", ans[0][i], ans[1][i]); 

	return 0;
}
