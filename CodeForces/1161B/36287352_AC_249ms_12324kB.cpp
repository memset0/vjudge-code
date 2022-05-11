// =================================
//   author: memset0
//   date: 2019.05.05 09:49:58
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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
	putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline void print(T *a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 2e5 + 10;
int n, m, l, r, tag[N];
std::set<std::pair<int, int>> set;
std::vector<std::pair<int, int>> v;

inline bool check(int k) {
	if (tag[k]) return false;
	tag[k] = 1;
	for (auto it : set) {
		auto A = std::make_pair((it.first + k - 1) % n + 1, (it.second + k - 1) % n + 1);
		auto B = std::make_pair(A.second, A.first);
		if (!set.count(A) && !set.count(B)) return false;
	}
	return true;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		read(l), read(r);
		set.insert(std::make_pair(l, r));
		v.push_back(std::make_pair(l, r));
	}
	for (int i = 1; i < n; i++)
		if (check(std::__gcd(i, n))) {
			puts("Yes");
			return;
		}
	puts("No");
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}