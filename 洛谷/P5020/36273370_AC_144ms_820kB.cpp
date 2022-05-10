#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

void openFile() { freopen("money.in", "r", stdin); freopen("money.out", "w", stdout); }
void closeFile() { fclose(stdin); fclose(stdout); }

inline int read() {
	char c = getchar(); int n = 0;
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
	return n;
}

const int maxN = 50005;

int n, m, ans, a[maxN];
bool f[maxN];

int main() {
	for (int tn = read(); tn; tn--) {
		n = read();
		memset(f, false, sizeof(f)); f[ans = m = 0] = true;
		for (register int i = 1; i <= n; i++) {
			a[i] = read();
			if (m < a[i]) { m = a[i]; }
		}
		std::sort(a + 1, a + n + 1);
		for (register int i = 1; i <= n; i++) {
			if (!f[a[i]]) {
				ans++;
				for (register int j = a[i]; j <= m; j++) { f[j] |= f[j - a[i]]; }
			}
		}
		printf("%d\n", ans);
	}
	closeFile();
	return 0;
}
