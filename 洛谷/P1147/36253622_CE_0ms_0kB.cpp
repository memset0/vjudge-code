#include <bits/stdc++.h>
using namespace std;
int m, sum;
int main() {
	cin >> n;
	for (int i = 1; i <= n / 2; i++) {
		sum = 0;
		for (int j = i; j < n; j++) {
			sum += j;
			if (sum >= n) break;
		}
		if (sum == n) cout << i << ' ' << j << endl
	}
	return 0;
}