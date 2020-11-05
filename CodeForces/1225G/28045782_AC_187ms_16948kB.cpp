#include <bits/stdc++.h>
const int N = 16, M = 2108;
int n, k, a[N], b[N];
std::bitset<M> f[1 << N];
std::priority_queue<std::pair<int, int>> q;
void dfs(int x, int v, int s) {
	if (!x) return;
	if (v * k <= M && f[x][v * k]) return dfs(x, v * k, s + 1);
	for (int i = 0; i < n; i++)
		if (((x >> i) & 1) && v >= a[i] && f[x ^ (1 << i)][v - a[i]])
			return b[i] = s, dfs(x ^ (1 << i), v - a[i], s);
}
int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	scanf("%d%d", &n, &k), f[0][0] = 1;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]), b[i] = -1;
	for (int x = 1; x < (1 << n); x++) {
		for (int i = 0; i < n; i++)
			if ((x >> i) & 1) f[x] |= f[x ^ (1 << i)] << a[i];
		for (int i = (M - 1) / k * k; i >= 0; i -= k)
			if (f[x][i]) f[x].set(i / k);
	}
	// for(int x=0;x<(1<<n);x++)for(int i=0;i<M;i++)if(f[x][i])printf("-> %d
	// %d\n",x,i);
	if (!f[(1 << n) - 1][1]) {
		puts("NO");
		return 0;
	}
	puts("YES"), dfs((1 << n) - 1, 1, 0);
	// for(int i=0;i<n;i++)printf("=> %d %d\n",a[i],b[i]);
	for (int i = 0; i < n; i++) q.push(std::make_pair(b[i], a[i]));
	while (q.size() > 1) {
		int b1 = q.top().first, a1 = q.top().second;
		q.pop();
		int b2 = q.top().first, a2 = q.top().second;
		q.pop();
		// printf("> %d %d | %d %d\n",a1,b1,a2,b2);
		auto x = std::make_pair(b1, a1 + a2);  // assert(b1==b2);
		while (x.second % k == 0) x.second /= k, x.first--;
		q.push(x);
		printf("%d %d\n", a1, a2);
	}
}