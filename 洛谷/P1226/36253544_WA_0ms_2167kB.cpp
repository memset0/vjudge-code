#include <bits/stdc++.h>
using namespace std;
long long ans, mul, mod, cnt, x, y, z;
int main() {
	ios::sync_with_stdio(0);
	cin >> x >> y >> z;
	ans = 1, mul = x, cnt = y, mod = z;
	while (cnt) {
		if (cnt % 2) ans = (ans * mul) % mod;
		mul = (mul * mul) % mod;
		cnt /= 2;
	}
	cout << x << "^" << y << " mod " << z << "=" << ans << endl;
	return 0;
}