#include <bits/stdc++.h>

void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	std::vector<int> ans(n + 1);
	std::function<std::set<int>(int, int)> dfs = [&](int u, int fa) {
		std::set<int> setu = {u};
		ans[u] = 1;
		for (int v : G[u])
			if (v != fa) {
				auto setv = dfs(v, u);
				if (setv.size() > setu.size()) { std::swap(setu, setv); }
				ans[u] += ans[v];
				for (int x : setv) {
					ans[u] -= setu.count(x - 1) + setu.count(x + 1);
				}
				for (int x : setv) { setu.insert(x); }
			}
		return setu;
	};
	dfs(1, 0);

	for (int i = 1; i <= n; i++) { std::cout << ans[i] << " \n"[i == n]; }
}

int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	for (int task = 1; task <= T; task++) {
		std::cout << "Case #" << task << ": ";
		solve();
	}
}