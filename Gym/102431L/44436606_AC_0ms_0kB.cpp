#include <bits/stdc++.h>

int solve(int n, int m) {
	if (n == 1) return m == 1 ? 1 : 2;
	if (n == 2) return m << 1;
	return (n + m - 2) << 1;
}

int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
#endif
	int T;
	std::cin >> T;
	for (int task = 1; task <= T; task++) {
		int n, m;
		std::cin >> n >> m;
		if (n > m) std::swap(n, m);
		std::cout << "Case #" << task << ": " << solve(n, m) << std::endl;
	}
}