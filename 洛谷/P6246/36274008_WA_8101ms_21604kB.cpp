#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
int n, k;
long long l, w[N], f[N], g[N], a[N], b[N], sum[N];
struct node {
	int l, r, t;
} e[N];
inline long long read() {
	long long num = 0;
	char g = getchar();
	while (g < 48 || 57 < g) g = getchar();
	while (47 < g && g < 58) num = num * 10 + g - 48, g = getchar();
	return num;
}
inline long long getans(int l, int r) {
	int d = (l + r) >> 1;
	return (d - l + 1) * w[d] - sum[d] + sum[l - 1] - (r - d) * w[d] + sum[r] -
		sum[d];
}
inline long long checka(long long d) {
	int l = 1, r = 1;
	e[1].l = 1, e[1].r = n, e[1].t = 0;
	for (int i = 1; i <= n; i++) {
		while (e[l].r < i) l++;
		e[l].l = i + 1;
		f[i] = f[e[l].t] + getans(e[l].t + 1, i) - d, g[i] = g[e[l].t] + 1;
		while (r >= l &&
			   getans(i + 1, e[r].l) + f[i] <=
				   getans(e[r].t + 1, e[r].l) + f[e[r].t])
			r--;
		if (r >= l) {
			int l1 = e[r].l, l2 = e[r].r, pot = 0;
			while (l1 <= l2) {
				int d = (l1 + l2) >> 1;
				if (getans(i + 1, d) + f[i] > getans(e[r].t + 1, d) + f[e[r].t])
					pot = d, l1 = d + 1;
				else
					l2 = d - 1;
			}
			e[r].r = pot;
		}
		if (e[r].r == n) continue;
		r++;
		e[r].l = max(e[r - 1].r + 1, i + 1), e[r].r = n, e[r].t = i;
	}
	// printf("check %lld\n",d);
	// for(int i=1;i<=n;i++)printf("%lld%c",f[i]+g[i]*d," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%d%c",g[i]," \n"[i==n]);
	return g[n];
}
int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		w[i] = read(), w[i + n] = w[i] + l, sum[i] = sum[i - 1] + w[i];
	long long l = -1e12, r = 1e12, pos = 0;
	while (l <= r) {
		long long d = (l + r) >> 1;
		if (checka(d) <= k)
			pos = d, l = d + 1;
		else
			r = d - 1;
	}
	checka(pos);
	cout << f[n] + pos * k << endl;
}