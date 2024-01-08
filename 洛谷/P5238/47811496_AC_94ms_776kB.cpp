// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.02 14:41:39
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

ll L, R, T;

std::vector <char> read() {
	char c = getchar();
	std::vector <char> v;
	while (!isdigit(c) && c != '-') c = getchar();
	while (isdigit(c) || c == '-') v.push_back(c), c = getchar();
	return v;
}

int solve(std::vector <char> vet) {
	// printf("solve\n");
	// for (auto c : vet) putchar(c); puts("");
	ll x = 0;
	bool flag = false, first = true;
	if (vet.size() == 1 && vet[0] == '0') {
		if (L <= 0 && 0 <= R) return 0;
		return 2;
	}
	if (vet.size() == 1 && vet[0] == '-') {
		return 1;
	}
	for (int i = 0; i < vet.size(); i++) {
		char c = vet[i];
		if (c == '-') {
			if (i) return 1;
			flag = true;
		} else {
			if (first && c == '0') return 1;
			first = false;
			x = x * 10 + c - '0';
		}
	}
	if (flag == 0) {
		__int128 x = 0;
		__int128 limit = __LONG_LONG_MAX__;
		for (int i = 0; i < vet.size(); i++) {
			char c = vet[i];
			x = x * 10 + c - '0';
			if (x > limit) return 2;
		}
	} else {
		__int128 x = 0;
		__int128 limit = (__int128)(-__LONG_LONG_MAX__) - 1;
		for (int i = 0; i < vet.size(); i++) if (vet[i] != '-') {
			char c = vet[i];
			x = x * 10 - c + '0';
			if (x < limit) return 2;
		}
	}
	if (x == 0 && vet.size() > 1) return 1;
	if (flag) x = -x;
	if (x < L || x > R) return 2;
	return 0;
}

void main() {
	read(L), read(R), read(T);
	for (int i = 0; i < T; i++) {
		print(solve(read()), '\n');
	}
}

} signed main() { return ringo::main(), 0; }