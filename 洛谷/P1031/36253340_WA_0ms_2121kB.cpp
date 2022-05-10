#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n, a[maxn], b[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += a[i];
	sum /= n;
	int ans = n + 1, cnt;
	for (int i = 1; i <= n; i++) 
		if (a[i] > sum) {
			cnt = 0;
			for (int j = 1; j <= n; j++)
				b[j] = a[j];
			for (int j = 1; j <= n; j++)
				if (b[(i + j - 2) % n + 1] > n) {
					b[(i + j - 1) % n + 1] = b[(i + j - 2) % n + 1] - sum;
					b[(i + j - 2) % n + 1] = sum;
					cnt ++;
				}
			if (cnt < ans) ans = cnt;
		}
	printf("%d\n", ans);
	return 0;
}