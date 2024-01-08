// AC Onsite

#include <bits/stdc++.h>
using namespace std;
int n, W, f[10005], cnt[20];
int main() {
	cin >> n >> W;
	while (n--) {
		int x;
		cin >> x;
		cnt[x - 1]++;
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i < (1 << 13); i++) {
		for (int j = i; j; j = (j - 1) & i) {
			int s = 0;
			for (int k = 0; k < 13; k++)
				if (j & (1 << k)) s += cnt[k];
			if (s > W) continue;
			f[i] = min(f[i], f[i - j] + 1);
		}
	}
	cout << f[(1 << 13) - 1];
}