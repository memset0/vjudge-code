#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	int a[110];
	int b[20010];
	memset(b, 0, sizeof(b));
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			b[a[i] + a[j]] ++;
		}
	long long ans = 0;
	for (int i = 1; i <= 20000; i++)
		ans += b[i] * (b[i] - 1);
	cout << ans << endl;
	return 0;
}