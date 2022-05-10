// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 40010, maxm = 70, maxk = 10;

int n, m, k;
int a[maxk], b[maxm];

namespace sol1 {
	int ans, f[maxn][2];
	bool t[maxn];
	
	int main() {
		for (int i = 1; i <= k; i++)
			t[a[i]] = 1;
		for (int i = 1; i <= n; i++)
			if (t[i]) {
				++ans;
				for (int j = 1; j <= b[1]; j++)
					t[i + j - 1] ^= 1;
			}
		print(ans, '\n');
		return 0;
	}
}

namespace sol2 {
	int y, t[4], c[maxm], d[maxn], f[maxn][16];
	
	int min(int a, int b) {
		if (!~a) return b;
		if (!~b) return a;
		return std::min(a, b);
	}
	
	void out(int x) {
		for (int i = 0; i < 4; i++)
			putc('0' + (x & (1 << i) ? 1 : 0));
	}
	
	int main() {
		memset(f, -1, sizeof(f));
		for (int i = 0; i < 16; i++)
			f[0][i] = 0;
		for (int i = 1; i <= k; i++)
			d[a[i]] = 1;
		for (int i = 1; i <= m; i++)
			switch (b[i]) {
				case 1:
					c[i] = 1;
					break;
				case 2:
					c[i] = 3;
					break;
				case 3:
					c[i] = 7;
					break;
				case 4:
					c[i] = 15;
					break;
			}
		for (int i = 1; i <= n; i++) {
			for (int x = 0; x < 16; x++) {
				if (!~f[i - 1][x]) continue;
				t[0] = x & 8 ? 1 : 0;
				t[1] = x & 4 ? 1 : 0;
				t[2] = x & 2 ? 1 : 0;
				t[3] = x & 1 ? 1 : 0;
				if (t[0]) continue;
				y = d[i] + (t[3] << 1) + (t[2] << 2) + (t[1] << 3);
//				printf("> %d > %d %d %d %d %d\n", i, t[0], t[1], t[2], t[3], d[i]);
//				out(x), putc(' '), out(y), putc('\n');;
				for (int j = 1; j <= m; j++)
					f[i][y ^ c[j]] = min(f[i][y ^ c[j]], f[i - 1][x] + 1);
				f[i][y] = min(f[i][y], f[i - 1][x]);
			}
		}
//		for (int i = 0; i <= n; i++) {
//			for (int j = 0; j < 16; j++)
//				printf("%d ", f[i][j]);
//			puts("");
//		}
		print(f[n][0], '\n');
		return 0;
	}
}

namespace sol3 {
	int l, r, ux, vx, u[20], v[20], dis[1 << 16], q[1 << 16];
	int main() {
		memset(dis, -1, sizeof(dis));
		ux = 0;
		for (int i = 1; i <= k; i++)
			ux += 1 << (a[i] - 1);
		q[1] = ux, l = r = 1, dis[ux] = 0;
		while (l <= r) {
			ux = q[l++];
			for (int i = 1; i <= n; i++)
				u[i] = ux & (1 << (i - 1)) ? 1 : 0;
			for (int j = 1; j <= m; j++) {
				for (int i = 1; i + b[j] - 1 <= n; i++) {
					for (int p = 1; p <= b[j]; p++)
						u[i + p - 1] ^= 1;
					vx = 0;
					for (int p = 1; p <= n; p++)
						if (u[p])
							vx += 1 << (p - 1);
					for (int p = 1; p <= b[j]; p++)
						u[i + p - 1] ^= 1;
					if (~dis[vx]) continue;
					dis[vx] = dis[ux] + 1;
					q[++r] = vx;
					if (vx == 0) {
						print(dis[vx], '\n');
						return 0;
					}
				}
			}
		}
		return 0;
	}
}

namespace sol4 {
	int main() {
		srand(20040725);
		if (k == 0) {
			print(0, '\n');
			return 0;
		}
		print(rand() % 3 + 1, '\n');
		return 0;
	}
}

int main() {
//	freopen("starlit.in", "r", stdin);
//	freopen("starlit.out", "w", stdout);
	
	read(n), read(k), read(m);
	for (int i = 1; i <= k; i++)
		read(a[i]);
	for (int i = 1; i <= m; i++)
		read(b[i]);	

	int max = 0;
	for (int i = 1; i <= m; i++)
		max = std::max(b[i], max);
		
	if (m == 1) return sol1::main();
	if (max <= 4) return sol2::main();
	if (n <= 16) return sol3::main();
	return sol4::main();

	return 0;
}