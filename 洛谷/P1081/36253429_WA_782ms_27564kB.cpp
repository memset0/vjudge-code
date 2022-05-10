// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 100010;
const int inf = 1e9;

int n, m, u, x;
int at[maxn], pre[maxn], nxt[maxn], tmp[4];
int min1[maxn], min2[maxn], sum1[maxn], sum2[maxn];
int f[maxn][20], s1[maxn][20], s2[maxn][20];

struct node {
	int h, i;
	bool operator < (node b) {
		return h < b.h;
	}
} a[maxn];

bool cmp(int x, int y) {
	if (abs(a[u].h - a[x].h) != abs(a[u].h - a[y].h))
		return abs(a[u].h - a[x].h) < abs(a[u].h - a[y].h);
	return a[x].h < a[y].h;
}

void parr(int *a, std::string s) {
	std::cout << s << " ";
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	puts("");
}

struct status {
	int a, b;
	status () {}
	status (int x, int y) { a = x, b = y; }
} now;

struct answer {
	int a, b, i;
	answer () {}
	answer (int x, int y, int j) { a = x, b = y, i = j; }
} ans;

status go(int s, int x) {
//	printf("go(%d,%d)", s, x);
	int u = s;
	status now(0, 0);
	for (int i = 18; i >= 0; i--) {
		if (~f[u][i] && s1[u][i] + s2[u][i] <= x) {
//			printf("<%d %d -> %d %d %d> ", u, i, f[u][i], s1[u][i], s2[u][i]);
			x -= s1[u][i] + s2[u][i];
			now.a += s1[u][i], now.b += s2[u][i];
			u = f[u][i];
		}
	}
//	printf("[%d]", u);
	if (~min2[u] && sum2[u] <= x) {
		x -= sum2[u];
		now.a += sum2[u];
		u = min2[u];
	}
//	printf("[%d]", u);
//	printf(" => %d %d\n", now.a, now.b);
	return now;
}

int main() {
//	freopen("INPUT", "r", stdin);

	n = read();
	for (int i = 1; i <= n; i++) {
		a[i].h = read();
		a[i].i = i;
	}
	std::sort(a + 1, a + n + 1);
	a[0].h = inf;
	for (int i = 1; i <= n; i++) {
		at[a[i].i] = i;
		pre[a[i].i] = a[i - 1].i;
		nxt[a[i].i] = a[i + 1].i;
	}
	for (int i = 1; i <= n; i++) {
		u = at[i];
		tmp[1] = at[pre[pre[i]]];
		tmp[2] = at[pre[i]];
		tmp[3] = at[nxt[i]];
		tmp[4] = at[nxt[nxt[i]]];
		std::sort(tmp + 1, tmp + 5, cmp);
//		printf("%d %d %d %d\n", tmp[1], tmp[2], tmp[3], tmp[4]);
		min1[i] = a[tmp[1]].i;
		min2[i] = a[tmp[2]].i;
		sum1[i] = abs(a[u].h - a[tmp[1]].h);
		sum2[i] = abs(a[u].h - a[tmp[2]].h);
		pre[nxt[i]] = pre[i];
		nxt[pre[i]] = nxt[i];
	}
	
	for (int i = 1; i <= n; i++) {
		f[i][0] = min1[min2[i]];
		if (!min2[i] || !min1[min2[i]])
			f[i][0] = -1;
		s1[i][0] = sum2[i];
		s2[i][0] = sum1[min2[i]];
//		printf("%d %d %d %d\n", min2[i], min1[min2[i]], s1[i][0], s2[i][0]);
	}
	for (int i = 1; i <= n; i++) {
		if (!min1[i]) min1[i] = -1;
		if (!min2[i]) min2[i] = -1;
	}
	
	for (int i = 1; i < 19; i++)
		for (int j = 1; j <= n; j++) {
			f[j][i] = f[f[j][i - 1]][i - 1];
			s1[j][i] = s1[f[j][i - 1]][i - 1] + s1[j][i - 1];
			s2[j][i] = s2[f[j][i - 1]][i - 1] + s2[j][i - 1];
		}
	
	x = read();
	for (int i = 1; i <= n; i++) {
		now = go(i, x);
		if (!ans.i || now.a * ans.b < ans.a * now.b)
			ans = answer(now.a, now.b, i);
	}
	printf("%d\n", ans.i);
	
	m = read();
	for (int i = 1; i <= m; i++) {
		u = read(), x = read();
		now = go(u, x);
		printf("%d %d\n", now.a, now.b);
	}
	
	return 0;
}