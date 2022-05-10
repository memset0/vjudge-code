#include <bits/stdc++.h>
int n, i, ans, a, b;
int main() {
	std::scanf("%d", &n);
	for (i = 1; i <= n; i++) b = a, scanf("%d", &a), ans += std::max(0, a - b);
	std::printf("%d\n", ans);
	return 0;
}
