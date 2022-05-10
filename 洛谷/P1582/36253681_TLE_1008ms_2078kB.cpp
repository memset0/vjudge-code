#include <bits/stdc++.h>
using namespace std;
long long n, m, k, ans, cnt;
bool find_ans;
int main() {
	cin >> n >> k;
	while (!find_ans) {
		for (m = n + ans, cnt = 0; m > 0; cnt += m % 2, m /= 2) continue;
		if (cnt <= k) cout << ans << endl, find_ans = 1;
		ans += n & -n;
	}
}