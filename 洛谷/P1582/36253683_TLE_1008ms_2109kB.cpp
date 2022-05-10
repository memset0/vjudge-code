#include <bits/stdc++.h>
using namespace std;
long long n, m, k, ans, cnt;
int main() {
	scanf("%lld%lld", &n, &k);
	while (1) {
		for (m = n + ans, cnt = 0; m > 0; cnt += m % 2, m /= 2) continue;
		if (cnt <= k) {
			printf("%lld\n", ans);
			return 0;
		}
		ans += n & -n;
	}
	return 0;
}