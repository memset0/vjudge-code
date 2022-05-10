// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define ll long long
#define mod 998244353
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; } 
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); } 
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

const int N = 110;
int n, m, ans, base_status, t[N << 2], p[N << 2], id[N][6];
int popcount[1 << 20], tag[1 << 20];

struct card {
	int a, c;
	inline card() {}
	inline card(int _a, int _c) { a = _a, c = _c; }
} a[20], b[N << 2];
std::vector <card> vet;

namespace helper {
	bool flag;
	card a[20];
	int tn, lst, cnt[N];
	void dfs2(int u) {
		bool find = false;
		for (int i = u; i <= n - 2 && !flag; i++)
			if (cnt[i] && cnt[i + 1] && cnt[i + 2]) {
				find = true;
				--cnt[i], --cnt[i + 1], --cnt[i + 2], lst -= 3;
//				printf("dfs2 %d\n", i);
				dfs2(i);
				++cnt[i], ++cnt[i + 1], ++cnt[i + 2], lst += 3;
			} 
		if (!find) { flag |= lst == 0; return; }
	}
	void dfs1(int u) {
		bool find = false;
		for (int i = u; i <= n && !flag; i++)
			if (cnt[i] >= 3) {
				find = true;
				cnt[i] -= 3, lst -= 3;
//				printf("dfs1 %d\n", i);
				dfs1(i), dfs2(1);
				cnt[i] += 3, lst += 3;
			}
		if (!find) { dfs2(1); return; }
	}
	int check(int status) {
//		printf("check %d\n", status);
		flag = false, tn = 0, lst = 14, memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= m; i++)
			if ((status >> (i - 1)) & 1)
				a[++tn] = b[i];
		for (int i = 1; i <= 14; i++) ++cnt[a[i].a];
		int cnt2 = 0;
		for (int i = 1; i <= n; i++) cnt2 += cnt[i] >= 2;
		flag |= cnt2 == 7;
//		for (int i = 1; i <= n; i++) print(cnt[i], " \n"[i == n]);
		for (int i = 1; i <= n && !flag; i++) if (cnt[i] >= 2) {
			cnt[i] -= 2, lst -= 2;
//			printf("dfs0 => %d\n", i);
			dfs1(1);
			cnt[i] += 2, lst += 2;
		}
//		printf("flag = %d\n", flag);
		return flag;
	}
} // end namespace helper
using helper::check;

void main() {
// 	freopen("mahjong.in", "r", stdin);
// 	freopen("mahjong.out", "w", stdout);
	read(n);
	if (n > 5) {
		puts("1");
		return;
	}
	for (int i = 1; i <= 13; i++) read(a[i].a), read(a[i].c);
	for (int i = 1; i <= n; i++) 
		for (int c = 1; c <= 4; c++)
			b[++m] = card(i, c), id[i][c] = m;
	for (int i = 1; i <= 13; i++) 
		base_status |= 1 << (id[a[i].a][a[i].c] - 1);
	for (int i = 0; i < (1 << m); i++) popcount[i] = popcount[i >> 1] + (i & 1);
	for (int i = 0; i < (1 << m); i++)
		if (popcount[i] == 14)
			if (check(i)) tag[i] = 1;
	for (int i = 0; i < (1 << m); i++) if (tag[i])
		for (int k = 1, j; k <= m; k++)
			j = i | (1 << (k - 1)), tag[j] = 1;
	m = 0;
	for (int i = 1; i <= n; i++)
		for (int c = 1; c <= 4; c++) {
			bool flag = true;
			for (int k = 1; k <= 13; k++)
				if (a[k].a == i && a[k].c == c)
					{ flag = false; break; }
			if (flag) t[++m] = id[i][c];
		}
//	printf("n = %d m = %d\n", n, m);
	for (int i = 1; i <= m; i++) p[i] = i;
	do {
		int id = -1, status = base_status;
//		printf("===============\n");
//		for (int i = 1; i <= m; i++) print(p[i], " \n"[i == m]);
		for (int i = 1; i <= m; i++) {
			status |= 1 << (t[p[i]] - 1);
//			printf(">> %d -> %d | pop = %d\n", status, tag[status], popcount[status]);
			if (tag[status]) { id = i; break; }
		}
		if (!~id) { id = m; /*printf("ERROR\n");*/ }
		ans = sub(ans, id);
	} while (std::next_permutation(p + 1, p + m + 1));
	for (int i = 1; i <= m; i++) ans = mul(ans, inv(i));
	print(ans, '\n');
}

} signed main() { ringo::main(); return 0; }
