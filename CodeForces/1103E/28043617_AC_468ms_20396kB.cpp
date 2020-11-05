// =================================
//   author: memset0
//   date: 2019.06.27 12:21:44
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ull unsigned long long
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; char c = getchar(); bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 4e5 + 10, lim = 100000;
const ull inv = 6723469279985657373ull;
int n, a[N], cnt[N], out[N];

struct number {
	ull a[5];
	inline void debug(char end='\n') const {
		for (int i = 0; i < 5; i++) print(a[i]), putchar(i == 4 ? end : ' ');
	}
	inline void mul_up(ull other) {
		for (int i = 0; i < 5; i++) a[i] *= other;
	}
	inline number operator+(const number &other) const {
		static number res;
		for (int i = 0; i < 5; i++) res.a[i] = a[i] + other.a[i];
		return res;
	}
	inline number operator*(const number &other) const {
		static ull tmp[10]; static number res;
		memset(tmp, 0, sizeof(tmp));
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				tmp[i + j] += a[i] * other.a[j];
		for (int i = 0; i < 5; i++) res.a[i] = tmp[i] - tmp[i + 5];
		return res;
	}
	inline ull to_int() {
		ull tmp = a[1];
		for (int i = 0; i < 5; i++) a[i] -= tmp;
		tmp = a[2];
		for (int i = 0; i < 5; i += 2) a[i] -= tmp;
		return a[0];
	}
} ans[N], bas[10], zero;

inline number fpow(number a, int b) {
	static number s; memset(s.a, 0, sizeof(s.a)), s.a[0] = 1;
	for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}

void fwt(number *a, int flag) {
	static int id[10];
	static number b[10];
	for (int len = 1; len < lim; len *= 10)
		for (int i = 0; i < lim; i += 10 * len)
			for (int j = 0; j < len; j++) {
				for (int d = 0; d < 10; d++) {
					id[d] = i + j + d * len;
					b[d] = a[id[d]], a[id[d]] = zero;
				}
				for (int d = 0; d < 10; d++)
					for (int e = 0; e < 10; e++)
						a[id[d]] = a[id[d]] + bas[(10 + flag) * d * e % 10] * b[e];
			}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), ++cnt[a[i]];
	for (int i = 0; i < 10; i++) bas[i].a[i % 5] = i >= 5 ? -1 : 1;
	for (int i = 0; i < lim; i++) ans[i].a[0] = cnt[i];
	fwt(ans, 1);
	for (int i = 0; i < lim; i++) ans[i] = fpow(ans[i], n);
	fwt(ans, -1);
	for (int i = 0; i < n; i++) print(((ans[i].to_int() * inv) >> 5) % (1ull << 58), '\n');
	// for (int i = 0; i < n; i++) ans[i].debug();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / (double)CLOCKS_PER_SEC << std::endl;
	return 0;
}