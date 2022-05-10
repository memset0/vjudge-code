#pragma GCC target("avx")
#pragma GCC target("popcnt,tune=native")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("inline-functions-called-once")

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

// fread by memset0
const int BUFFER = 1 << 21;
char ibuf[BUFFER], *iS, *iT;
#define getchar()                                                              \
	(iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, S, stdin),                  \
				 (iS == iT ? EOF : *iS++)) :                                   \
				*iS++)

#define all(S) (S).begin(), (S).end()

const int S = 800, minS = 200, maxS = 1200;
std::vector<std::vector<int>> a;
std::vector<int> b;
std::vector<int>::iterator it;

void read(int& as) {
	as = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		as = as * 10 + ch - '0';
		ch = getchar();
	}
	return;
}

int find(int x) {
	int l = 0, r = a.size() - 1, rt = -1, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (a[mid][a[mid].size() - 1] >= x) {
			rt = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return ~rt ? rt : a.size() - 1;
}

int main() {
	int n, m, x, ans = 0, op, p, tt, t1, t2, t3, last = 0;
	read(n), read(m);
	b.resize(n);
	for (int i = 0; i < n; i++) read(b[i]);
	std::sort(all(b));
	a.push_back(b);
	while (a[0].size() >= 2 * S) {
		a.insert(a.begin() + 1, std::vector<int>(a[0].end() - S, a[0].end()));
		a[0].erase(a[0].end() - S, a[0].end());
	}
	while (m--) {
		switch (read(op), op) {
			case 1:
				read(x), x ^= last;
				p = find(x);
				it = std::lower_bound(all(a[p]), x);
				a[p].insert(it, x);
				if (a[p].size() >= maxS) {
					a.insert(a.begin() + p + 1, std::vector<int>(a[p].end() - S, a[p].end()));
					a[p].erase(a[p].end() - S, a[p].end());
				}
				break;
			case 2:
				read(x), x ^= last;
				p = find(x);
				it = std::lower_bound(all(a[p]), x);
				a[p].erase(it);
				if (a[p].size() <= minS && a.size() != 1) {
					if (p == 0) {
						a[p + 1].insert(a[p + 1].begin(), all(a[p]));
					} else if (p == a.size() - 1) {
						a[p - 1].insert(a[p - 1].end(), all(a[p]));
					} else {
						bool flag = a[p + 1].size() > a[p - 1].size();
						if (flag) {
							a[p - 1].insert(a[p - 1].end(), all(a[p]));
						} else {
							a[p + 1].insert(a[p + 1].begin(), all(a[p]));
						}
					}
					a.erase(a.begin() + p);
				}
				break;
			case 3:
				read(x), x ^= last;
				p = find(x);
				tt = 1, t1 = t2 = t3 = 0;
				int i;
				for (i = 0; i < p - 4; i += 4) {
					tt += a[i].size();
					t1 += a[i + 1].size();
					t2 += a[i + 2].size();
					t3 += a[i + 3].size();
				}
				if (i < p) tt += a[i].size();
				if (i + 1 < p) t1 += a[i + 1].size();
				if (i + 2 < p) t2 += a[i + 2].size();
				if (i + 3 < p) t3 += a[i + 3].size();
				tt += t1 + t2 + t3;
				tt += std::lower_bound(all(a[p]), x) - a[p].begin();
				last = tt;
				ans ^= last;
				break;
			case 4:
				read(x), x ^= last;
				p = 0;
				x--;
				while (x >= a[p].size()) {
					x -= a[p].size();
					p++;
				}
				last = a[p][x];
				ans ^= last;
				break;
			case 5:
				read(x), x ^= last;
				p = find(x);
				if (a[p][0] >= x) {
					last = a[p - 1][a[p - 1].size() - 1];
				} else {
					last = (*(std::lower_bound(all(a[p]), x) - 1));
				}
				ans ^= last;
				break;
			case 6:
				read(x), x ^= last;
				p = find(x + 1);
				it = std::upper_bound(all(a[p]), x);
				if (it == a[p].end()) it = a[p + 1].begin();
				last = *it;
				ans ^= last;
		}
	}
	printf("%d\n", ans);
}