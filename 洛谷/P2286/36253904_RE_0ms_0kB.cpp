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

int n, x, opt, tag, ans;
set < int > s;
set < int > ::iterator l, r, it;

int main() {
	
	n = read();
	opt = read(), x = read();
	tag = opt, s.insert(x);
	for (int i = 2; i <= n; i++) {
		opt = read(), x = read();
//		printf(">>> %d %d : %d : ", opt, x, tag);
//		for (auto it = s.begin(); it != s.end(); it++)
//			printf("%d ", *it);
//		puts("");
		if (opt == tag) {
			s.insert(x);
		} else {
			if (!s.size()) {
				tag = opt;
				s.insert(x);
			}
			it = s.lower_bound(x);
			if (*it == x) {
				s.erase(it);
			} else {
				r = it, l = --it;
//				printf("%d %d\n", *l, *r);
				if (x - *l <= *r - x) {
					ans = (ans + abs(x - *l)) % 1000000;
					s.erase(l);
				} else {
					ans = (ans + abs(*r - x)) % 1000000;
					s.erase(r);
				}
			}
		}
	}
	
	printf("%d\n", ans);
	
	return 0;
}
