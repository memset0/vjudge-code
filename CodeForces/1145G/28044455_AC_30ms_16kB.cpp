// =================================
//   author: memset0
//   date: 2019.04.07 09:52:28
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

const std::string T = "RRRRPSSPRR";
std::string s, t, input;

void main() {
    for (int i = 0; i < 10; i++) {
        printf("%c\n",T[i]);
		getline(std::cin, input);
        s += (input == "ai" ? '0' : '1');
    }
    if (s == "0000100100") t = "PPPPPPPPPP";
    if (s == "0000011000") t = "SSSSSSSSSS";
    if (s == "1111000011") t = "RRRRRRRRRR";
    if (s == "0010000010") t = "SRPSRPSRPS";
    if (s == "0000110000") t = "PSRPSRPSRP";
    if (s == "0000000110") t = "SPRSPRSPRS";
    for (int i = 0; i < 10; i++) {
        printf("%c\n", t[i]);
		getline(std::cin, input);
    }
    return;
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}