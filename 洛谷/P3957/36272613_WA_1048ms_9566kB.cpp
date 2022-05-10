// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
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

const int maxn = 500010;
int n, d, k, mid, l, r, t, pl, pr, lbound, rbound, ans;
int f[maxn], q[maxn];
struct node {
	int x, s;
	bool operator < (const node &b) {
		return x < b.x;
	}
} a[maxn];

void pop() {
	l++;
}

void push() {
	// printf("push()\n");
	while (l <= r && f[t] > f[q[r]]) r--;
	q[++r] = t++;
}

bool check(int val) {
	memset(f, 0, sizeof(0));
	pl = max(1, d - val), pr = d + val;
	l = 1, r = 0, t = 0;
	// printf("%d %d\n", pl, pr);
	for (int i = 1; i <= n; i++) {
		while (l <= r && a[q[l]].x < a[i].x - pr) pop();
		while (t < i && a[t].x <= a[i].x - pl) push();
		// printf(">>> i = %d l = %d r = %d rr = %d q[l] = %d f[q[l]] = %d\n", i, l, r, t, q[l], f[q[l]]);
		// printf("%d %d %d\n", t, a[t].x, a[i].x - pl);
		// for (int i = l; i <= r; i++)
		// 	printf("%d ", q[i]);
		// puts("");
		if (l <= r) {
			f[i] = f[q[l]] + a[i].s;
			if (f[i] >= k) return true;
		} else f[i] = -1e9;
	}
	// for (int i = 1; i <= n; i++)
	// 	printf("%d ", q[i]);
	// puts("");
	return false;
}

int main() {
	// freopen("INPUT", "r", stdin);
	// freopen("OUTPUT", "w", stdout);

	n = read(), d = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i].x = read(), a[i].s = read();
	sort(a + 1, a + n + 1);

	// printf("=== %d ===\n", check(0));
	lbound = 0, rbound = 1e9, ans = -1;
	while (lbound <= rbound) {
		mid = (lbound + rbound) >> 1;
		// printf("check(%d) = %d\n", mid, check(mid));
		if (check(mid)) {
			ans = mid;
			rbound = mid - 1;
		} else {
			lbound = mid + 1;
		}
	}
	printf("%d\n", ans);

	return 0;
}