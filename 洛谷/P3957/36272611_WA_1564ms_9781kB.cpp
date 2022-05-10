#include <bits/stdc++.h>
#define N 2000000000
using namespace std;
const int maxn = 500010;
int n, d, k, l, r, f[500010], a[500010], v[500010];
struct Queue {
	int a[maxn], l = 1, r = 0;
	void push(int x) {
		a[++r] = x;
		return ;
	}
	void clean() {
		memset(a, 0, sizeof(a));
		l = 1, r = 0;
		return ;
	}
	int operator [] (int k) {
		return a[k];
	}
} q;
bool check(int g) {
//	printf("[FUN]check(%d)\n", g);
	l = max(1, d - g), r = d + g;
	memset(f, 0, sizeof(f)), q.clean();
	f[0] = 0; q.push(0);
	for (int i = 1; i <= n; i++) {
		f[i] = -1 * N;
		for (int j = q.l; j <= q.r; j++)
			if (l <= a[i] - a[q[j]] && a[i] - a[q[j]] <= r) {
				f[i] = max(f[i], f[q[j]] + v[i]);
//				printf("  f[i:%d] = %d; f[j:%d] = %d;\n", i, f[i], q[j], f[q[j]]);
//				printf("q[%d] = {", q.r - q.l + 1);
//				for (int i = q.l; i <= q.r; i++)
//					printf("%d, ", q[i]);
//				puts("}");
				while (f[i] >= q[q.r] && q.r >= q.l) q.r--;
				q.push(i);
				if (f[i] >= k) return true;
				break;
			} else l++;
	}
	return false;
}
int main() {
	scanf("%d%d%d", &n, &d, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &v[i]);
	long long sum = 0;
	for (int i = 1; i <= n; i++)
		if (v[i] > 0) sum += v[i];
	if (sum < k) {
		printf("-1\n");
		return 0;
	}
//	cout << check(3);
//	cout << check(2);
//	cout << check(1);
//	cout << check(0);
	int ll = 0, rr = 100000000, mid;
	while (ll + 3 < rr) {
		mid = (ll + rr) / 2;
		if (check(mid)) rr = mid;
		else ll = mid;
	}
	for (int i = ll; i <= rr; i++)
		if (check(i)) {
			printf("%d\n", i);
			return 0;
		}
	return 0;
}