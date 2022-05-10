// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 1e5 + 10;
int tag, val, m1, m2, ansa, ansb;
char c, name;
// tag = 0  ==>  鏁板瓧
// tag = 1  ==>  杩愮畻绗﹀彿
// tag = 2  ==>  璐熷彿

int main() {
//	freopen("INPUT", "r", stdin);

	m1 = m2 = 1;
	c = getchar();
	while (true) {
		if (c == '=') {
			m2 = -1;
			c = getchar();
		} else if (c == '+') {
			m1 = 1;
			c = getchar();
		} else if (c == '-') {
			m1 = -1;
			c = getchar();
		} else if ('0' <= c && c <= '9') {
			int x = 0;
			while (isdigit(c)) {
				x = x * 10 + c - '0';
				c = getchar();
			}
			if ('a' <= c && c <= 'z') {
				ansa += m1 * m2 * x;
				m1 = 1;
				name = c;
				c = getchar();
			} else {
				ansb -= m1 * m2 * x;
				m1 = 1;
			}
		} else break;
	}
//	printf("%d %d\n", ansa, ansb);
	printf("%c=%.3lf\n", name, double(ansb) / double(ansa));

	return 0;
}