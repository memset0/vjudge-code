#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long

using namespace std;

const int N = 2e5 + 5;
int n, m, vis[N];
ull val[N], sum[N], tag;
vector<int> vec[N];
map<ull, ll> x, y;
ull randd() { return ((ull)rand() * rand() * rand() * 20200619 + (ull)rand() * 20200619); }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int l, r;
		val[i] = randd();
		scanf("%d%d", &l, &r);
		vec[l].push_back(i);
		vis[l]++;
		vis[r + 1]--;
		sum[l] ^= val[i];
		sum[r + 1] ^= val[i];
	}
	for (int i = 1; i <= m; i++) vis[i] += vis[i - 1], sum[i] ^= sum[i - 1];
	for (int i = 1; i <= m; i++) sum[i] ^= sum[i - 1];
	ll ans = 0;
	for (int i = 1; i <= m; i++) {
		tag ^= sum[i] ^ sum[i - 1];
		for (int j = 0; j < vec[i].size(); j++) tag ^= val[vec[i][j]];
		x[tag]++;
		y[tag] += i - 1;
		ans += (ll)i * x[tag] - y[tag];
	}
	for (int i = 1; i <= m; i++) {
		if (vis[i]) continue;
		int r = i;
		while (r < m && !vis[r + 1]) r++;
		int len = r - i + 1;
		for (int j = 1; j <= len; j++) ans -= (ll)j * (len - j + 1);
		i = r;
	}
	printf("%llu\n", ans);
	return 0;
}