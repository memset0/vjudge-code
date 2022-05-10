#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int k, n, ans, a[maxn], b[maxn];
bool fnd = false;
int main() {
	cin >> k >> n;
	while (n > 0) {
		a[++a[0]] = n % k;
		n /= k;
	}
	while (1) {
		fnd = true;
		for (int i = 1; i <= a[0] / 2; i++)
			if (a[i] != a[a[0] - i + 1]) {
				fnd = false;
				break;
			}
		if (fnd) break;
		ans ++;
		for (int i = 1; i <= a[0]; i++)
			b[i] = a[a[0] - i + 1];
		for (int i = 1; i <= a[0]; i++) {
			a[i] += b[i];
			a[i + 1] += a[i] / k;
			a[i] %= k;
		}
		if (a[a[0] + 1]) a[0]++;
//		for (int i = 1; i <= a[0]; i++)
//			printf("%d", a[i]);
//		puts("");
	}
	printf("STEP=%d\n", ans);
	return 0; 
}