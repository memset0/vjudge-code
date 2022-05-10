// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.06 09:49:14
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
inline char read() {
	static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
	static bool f; static char c;
	for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline void print(T a, int l, int r) {
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 3e6 + 10;
char s[N];
int ans[N];
bool del[N];
int n, siz, len;
int sa[N], rnk[N], tax[N], log[N], tmp[N], height[N], st[20][N];

struct setClass : std::vector<int> {
	using std::vector<int>::vector;
	inline void reset() {
		setClass tmp = *this;
		this->clear();
		for (int i = 0; i < tmp.size(); i++)
			if (del[i]) del[i] = 0;
			else this->push_back(tmp[i]);
	}
	inline bool count(int v) {
		for (auto it = begin(); it != end(); it++)
			if (*it == v) return true;
		return false;
	}
} set;

int query(int l, int r) {
	if (l == r) return n;
	l = rnk[l], r = rnk[r]; if (l > r) std::swap(l, r); l++;
	int t = log[r - l + 1];
	return std::min(st[t][l], st[t][r - (1 << t) + 1]);
}

void baseSort() {
	for (int i = 1; i <= siz; i++) tax[i] = 0;
	for (int i = 1; i <= len; i++) tax[rnk[i]]++;
	for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
	for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
}

void buildSA(char *s) {
	siz = 200;
	for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i;
	baseSort();
	for (int now = 1, cnt = 0; cnt < len; siz = cnt, now <<= 1) {
		cnt = 0;
		for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
		for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now;
		baseSort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
		for (int i = 2; i <= len; i++) rnk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now]) ? cnt : ++cnt;
	}
	for (int i = 1, j, ans = 0; i <= len; i++) {
		j = sa[rnk[i] - 1]; if (ans) --ans;
		while (s[i + ans] == s[j + ans]) ++ans;
		height[rnk[i]] = ans;
	}
	height[1] = 0;
	for (int i = 1; i <= len; i++) st[0][i] = height[i];
	for (int i = 1; i < 20; i++)
		for (int j = 1; j + (1 << i) - 1 <= len; j++)
			st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}

inline int better(int i, int j, int L) {
	// printf("better %d %d %d : %d %d\n", i, j, L, i - j + L + 1, j - i);
	int lcp = query(1, i - j + L + 1);
	// printf("       %d %d : %d %d : %c %c\n", lcp, j - i, i - j + L + 1 + lcp, 1 + lcp,s[i - j + L + 1 + lcp], s[1 + lcp]);
	if (lcp < j - i) {
		if (s[i - j + L + 1 + lcp] < s[1 + lcp]) return i;
		if (s[i - j + L + 1 + lcp] > s[1 + lcp]) return j;
	}
	lcp = query(1, 1 + j - i);
	// printf("       %d %d : %d %d : %c %c\n", lcp, i - 1, lcp + 1, 1 + j - i + lcp, s[1 + lcp], s[1 + j - i + lcp]);
	if (lcp < i - 1) {
		if (s[1 + lcp] < s[1 + j - i + lcp]) return i;
		if (s[1 + lcp] > s[1 + j - i + lcp]) return j;
	}
	return i;
}

void main() {
	scanf("%s", s + 1), n = len = strlen(s + 1);
	log[0] = -1;
	for (int i = 1; i <= n; i++) log[i] = log[i >> 1] + 1;
	buildSA(s);
	set.push_back(1), ans[1] = 1;
	// for (int i = 1; i <= n; i++)
	// 	for (int j = i + 1; j <= n; j++)
	// 		printf("lcp %d %d => %d\n", i, j, query(i, j));
	for (int L = 2; L <= len; L++) {
		// printf("===== L = %d =====\n", L);
		set.push_back(L);
		for (int i = 0; i < set.size(); i++)
			for (int j = i + 1; j < set.size(); j++) {
				int lcp = query(set[i], set[j]);
				// printf(">> %d %d >> %d\n", set[i], set[j], lcp);
				if (lcp < L - set[j] + 1) {
					if (s[set[i] + lcp] < s[set[j] + lcp]) del[j] = 1;
					if (s[set[i] + lcp] > s[set[j] + lcp]) del[i] = 1;
				}
			}
		set.reset();
		// print(set, 0, set.size() - 1, "set");
		for (int p = 0; p < set.size(); p++)
			for (int q = p + 1; q < set.size(); q++) {
				int i = set[p], j = set[q];
				if (L - j + 1 < L - i + 1 && L - i + 1 < 2 * (L - j + 1)) {
					int k = (j << 1) - i;
					// printf(">> %d %d %d : %d\n", i, j, k, set.count(k));
					// if (set.count(k))
					del[q] = 1;
				}
			}
		set.reset();
		// print(set, 0, set.size() - 1, "set");
		ans[L] = set[0];
		for (int i = 1; i < set.size(); i++) {
			ans[L] = better(ans[L], set[i], L);
		}
		// if (ans[L] == 6) {
		// 	for (int i = 0; i < L; i++) {
		// 		putchar(s[(i + 2 - 1) % L + 1]);
		// 		putchar(s[(i + 6 - 1) % L + 1]);
		// 		putchar('\n');
		// 	}
		// 	return;
		// }
	}
	print(ans, 1, len);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
#endif
	ringo::main();
	ringo::flush();
	std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
	return 0;
}