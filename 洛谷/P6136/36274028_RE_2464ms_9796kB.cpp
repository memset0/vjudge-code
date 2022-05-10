#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>

// fread by memset0
const int BUFFER = 1 << 21;
char ibuf[BUFFER], *iS, *iT, obuf[BUFFER], *oS = obuf, *oT = oS + BUFFER - 1;
#define flush() (fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void())
#define getchar()                                                              \
	(iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, S, stdin),                  \
				 (iS == iT ? EOF : *iS++)) :                                   \
				*iS++)
#define putchar(x) (*oS++ = (x), oS == oT ? flush() : void())
struct Flusher_ {
	~Flusher_() { flush(); }
} flusher_;

using namespace std;
const int S = 800;
vector<vector<int>> a;
vector<int> b;
vector<int>::iterator it;
int fnds(int x) {
	int l = 0, r = a.size() - 1, rt = -1, md;
	while (l <= r) {
		md = (l + r) >> 1;
		if (a[md][a[md].size() - 1] >= x) {
			rt = md;
			r = md - 1;
		} else
			l = md + 1;
	}
	if (rt == -1) return a.size() - 1;
	return rt;
}
void rd_int(int& as) {
	as = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') {
		as = as * 10 + ch - 48;
		ch = getchar();
	}
	return;
}
int main() {
	int n, m, x, ns = 0, op, p, tt, last = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		rd_int(x);
		b.push_back(x);
	}
	sort(b.begin(), b.end());
	a.push_back(b);
	while (a[0].size() >= 2 * S) {
		b.clear();
		b.insert(b.begin(), a[0].end() - S, a[0].end());
		a[0].erase(a[0].end() - S, a[0].end());
		a.insert(a.begin() + 1, b);
	}
	while (m--) {
		rd_int(op);
		if (op == 1) {
			rd_int(x), x ^= last;
			p = fnds(x);
			it = lower_bound(a[p].begin(), a[p].end(), x);
			a[p].insert(it, x);
			if (a[p].size() >= 2 * S) {
				b.clear();
				b.insert(b.begin(), a[p].end() - S, a[p].end());
				a[p].erase(a[p].end() - S, a[p].end());
				a.insert(a.begin() + p + 1, b);
			}
		}
		if (op == 2) {
			rd_int(x), x ^= last;
			p = fnds(x);
			it = lower_bound(a[p].begin(), a[p].end(), x);
			a[p].erase(it);
		}
		if (op == 3) {
			rd_int(x), x ^= last;
			p = fnds(x);
			tt = 1;
			for (int i = 0; i < p; i++) tt += a[i].size();
			tt += lower_bound(a[p].begin(), a[p].end(), x) - a[p].begin();
			last = tt;
			ns ^= last;
		}
		if (op == 4) {
			rd_int(x), x ^= last;
			p = 0;
			x--;
			while (x >= a[p].size()) {
				x -= a[p].size();
				p++;
			}
			last = a[p][x];
			ns ^= last;
		}
		if (op == 5) {
			rd_int(x), x ^= last;
			p = fnds(x);
			if (a[p][0] >= x) {
				last = a[p - 1][a[p - 1].size() - 1];
				ns ^= last;
			}
			if (a[p][0] < x) {
				last = (*(lower_bound(a[p].begin(), a[p].end(), x) - 1));
				ns ^= last;
			}
		}
		if (op == 6) {
			rd_int(x), x ^= last;
			p = fnds(x + 1);
			it = upper_bound(a[p].begin(), a[p].end(), x);
			if (it == a[p].end()) it = a[p + 1].begin();
			last = (*it);
			ns ^= last;
		}
	}
	printf("%d\n", ns);
	return 0;
}