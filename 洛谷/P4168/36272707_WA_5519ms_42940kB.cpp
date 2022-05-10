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

const int maxn = 40010, maxm = 210;

int n, m, l, r, bl, br, tn, sqn, ans;
int a[maxn], b[maxn], bln[maxn], fst[maxm], max[maxm], tmp[maxn];
int cnt[maxn][maxm], sum[maxn][maxm];

bool better(int x, int y, int a, int b) {
//	if ((x > y) || (x == y && a < b))
//		printf(": %d %d %d %d\n", x, y, a, b);
	return (x > y) || (x == y && a < b);
}

int query(int l, int r) {
//	printf(">> %d %d\n", l, r);
	ans = 0;
	if (bln[l] == bln[r]) {
		for (int i = l; i <= r; i++)
			if (better(++tmp[a[i]], tmp[ans], a[i], ans))
				ans = a[i];
		for (int i = l; i <= r; i++)
			--tmp[a[i]];
	} else {
		br = bln[r] - 1, bl = bln[l];
		for (int i = l; i < fst[bln[l] + 1]; i++)
			if (better(++tmp[a[i]] + sum[a[i]][br] - sum[a[i]][bl], tmp[ans] + sum[ans][br] - sum[ans][bl], a[i], ans))
				ans = a[i];
//		printf(">> %d %d %d %d\n", l, fst[bln[l] + 1] - 1, fst[bln[r]], r);
//		printf("=] %d\n", ans); 
		for (int i = fst[bln[r]]; i <= r; i++)
			if (better(++tmp[a[i]] + sum[a[i]][br] - sum[a[i]][bl], tmp[ans] + sum[ans][br] - sum[ans][bl], a[i], ans))
				ans = a[i];
//		printf("=] %d\n", ans);
		for (int i = bln[l] + 1; i <= bln[r] - 1; i++)
			if (better(tmp[max[i]] + sum[max[i]][br] - sum[max[i]][bl], tmp[ans] + sum[ans][br] - sum[ans][bl], max[i], ans))
				ans = max[i];
//		printf("=] %d\n", ans);
		for (int i = l; i < fst[bln[l] + 1]; i++)
			--tmp[a[i]];
		for (int i = fst[bln[r]]; i <= r; i++)
			--tmp[a[i]];
	}
	return ans;
}

int main() {
	
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		b[i] = a[i] = read();
	std::sort(b + 1, b + n + 1);
	tn = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
	
	sqn = sqrt(n) + 1;
	if (sqn * sqn < n) sqn++;
	bln[sqn + 1] = n + 1;
	for (int i = 1; i <= n; i++) {
		bln[i] = (i - 1) / sqn + 1;
		if (!fst[bln[i]]) fst[bln[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		cnt[a[i]][bln[i]]++;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= sqn; j++) 
			sum[i][j] = sum[i][j - 1] + cnt[i][j];
	for (int i = 1; i <= sqn; i++) {
		for (int j = fst[i]; j < fst[i + 1]; j++)
			if (better(++tmp[a[j]], tmp[max[i]], a[j], max[i]))
				max[i] = a[j];
		for (int j = fst[i]; j < fst[i + 1]; j++)
			--tmp[a[j]];
	}
	
	for (int i = 1; i <= m; i++) {
		l = (read() + ans - 1) % n + 1;
		r = (read() + ans - 1) % n + 1;
		if (l > r) std::swap(l, r);
		printf("%d\n", ans = b[query(l, r)]);
	}

	return 0;
}