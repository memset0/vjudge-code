#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	int a[110];
	long long ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				if (a[i] + a[j] == a[k])
					ans++;
	cout << ans << endl;
	return 0;
}