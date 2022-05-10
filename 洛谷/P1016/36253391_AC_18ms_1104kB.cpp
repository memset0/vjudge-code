#include <bits/stdc++.h>

const int N = 110;
int n, res, now = 0;
double oil = 0.0, rch, used, _min, tot = 0.0, t, v, d, cst[N], dis[N];

int main() {
	std::cin >> t >> v >> d >> cst[0] >> n;
	for (int i = 1; i <= n; i++) std::cin >> dis[i] >> cst[i];
	dis[++n] = t, cst[n] = 0.0;
	while (now != n) {
		rch = dis[now] + v * d;
		_min = 2147400000.0;
		res = -1;
		for (int i = now + 1; i <= n && dis[i] <= rch; i++) {
			if (_min > cst[i]) _min = cst[i], res = i;
			if (cst[now] > _min) break;
		}
		if (res == -1) {
			printf("No Solution\n");
			return 0;
		}
		used = (dis[res] - dis[now]) / d;
		if (cst[now] > _min) {
			if (oil >= used)
				oil -= used;
			else
				tot += cst[now] * (used - oil), oil = 0.0;
		} else {
			tot += cst[now] * (v - oil), oil = v - used;
		}
		now = res;
	}
	printf("%.2lf\n", tot);
	return 0;
}