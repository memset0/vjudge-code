#include <bits/stdc++.h>

struct item {
	int x, y;
	double weight;
	int index;

	inline bool operator<(const item& other) const {
		return weight > other.weight;
	}
};

void solve() {
	int n, m;
	double l;
	std::cin >> n >> m >> l;

	std::vector<bool> vis(n);
	double limit = m * m * (1 - l) / (1 + l);
	double weight = m;

	std::vector<item> a;
	for (int i = 0; i < n; i++) {
		int x, y;
		double v;
		std::cin >> x >> y >> v;
		a.push_back({x, y, v, i + 1});
	}
	std::sort(a.begin(), a.end());

	std::function<std::pair<int, int>(int, int)> locate = [&](int x, int y) {
		return std::make_pair(int(x / weight), int(y / weight));
	};

	std::function<long long(const std::pair<int, int>&)> trans =
		[&](const std::pair<int, int>& p) {
			return (long long)p.first * 100000000 + p.second;
		};

	std::map<long long, std::vector<int>> map;
	for (int i = 0, x, y; i < n; i++) {
		auto pair = locate(a[i].x, a[i].y);
		auto it = map.find(trans(pair));
		if (it == map.end()) {
			map[trans(pair)] = std::vector<int>{i};
		} else {
			it->second.push_back(i);
		}
	}

	// for (int i = 0, x, y; i < n; i++) {
	// 	std::tie(x, y) = locate(a[i].x, a[i].y);
	// 	printf("%d : %d %d\n", a[i].index, x, y);
	// }

	std::function<bool(item&, item&)> cross = [&](item& i, item& j) {
		int l = std::abs(i.x - j.x);
		int r = std::abs(i.y - j.y);
		long long s = (long long)m * (l + r) - (long long)l * r;
		return s <= limit;
	};

	std::vector<int> ans;
	for (int i = 0; i < n; i++)
		if (!vis[i]) {
			int x, y, cur = i;
			vis[i] = 1;
			std::tie(x, y) = locate(a[i].x, a[i].y);
			ans.push_back(a[i].index);

			for (int deltax = -1; deltax <= 1; deltax++)
				for (int deltay = -1; deltay <= 1; deltay++) {
					auto pair = std::make_pair(x + deltax, y + deltay);
					auto it = map.find(trans(pair));
					if (it == map.end()) continue;

					std::vector<int>& vec = it->second;
					std::vector<int> now;
					for (int x : vec) {
						if (!vis[x] && cross(a[cur], a[x])) {
							// printf("check %d %d\n", a[cur].index,
							// a[x].index);
							vis[x] = 1;
						} else {
							now.push_back(x);
						}
					}
					std::swap(vec, now);
				}
		}

	std::sort(ans.begin(), ans.end());
	std::cout << ans.size() << std::endl;
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << " \n"[i + 1 == ans.size()];
	}
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