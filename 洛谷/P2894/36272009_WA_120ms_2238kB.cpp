#include <bits/stdc++.h> 
#define isnum(c) ('0' <= c && c <= '9')
#define read(x) do { \
	x = 0, r_::c = getchar(), r_::m = 0; \
	while (!isnum(r_::c) && r_::c != '-') r_::c = getchar(); \
	if (r_::c == '-') r_::c = getchar(), r_::m = 1; \
	while (isnum(r_::c)) x = x * 10 + r_::c - '0' , r_::c = getchar(); \
	if (r_::m) x = -x; \
} while(false)

namespace r_ { char c; bool m; }
using namespace std;

const int maxn = 50010, maxm = 250;
int n, m, x, t, a, b;
struct Square {
	int left, right, n, L, R, M, tag;
	bool a[maxm];
	void flat()  {
		if (tag == 0) {
//			cout << "?";
			for (int i = 1; i <= n; i++)
				a[i] = 0;
			tag = -1;
		} else if (tag == 1) {
//			cout << "!";
			for (int i = 1; i <= n; i++)
				a[i] = 1;
			tag = -1;
		}
	}
	void rebuild() {
		int cnt; bool mrk;
		L = R = M = 0;
		flat();
		for (int i = 1; i <= n; i++)
			if (a[i]) break;
			else L++;
		for (int i = n; i > 0; i--) 
			if (a[i]) break;
			else R++;
		for (int i = 1; i <= n; i++)
			if (a[i]) cnt = 0;
			else {
				cnt++;
				if (cnt > M) M = cnt;
			}
		if (M == n) tag = 0;
		else if (M == 0) tag = 1;
		else tag = -1;
//		cout << ">>> " << M << " " << tag << endl;
	}
} s[maxm];

void print() {
//	puts("=====");
//	for (int i = 1; i <= t; i++) {
//		printf("%3d%3d|%3d%3d%3d|%3d|", s[i].left, s[i].right, s[i].L, s[i].R, s[i].M, s[i].tag);
//		for (int j = 1; j <= s[i].n; j++)
//			printf("%3d", s[i].a[j]);
//		puts("");
//	}
//	puts("=====");
}

struct Room {
	int l, r;
} ret;

int build(int n, int m) {
	int t = ceil(sqrt(m)), tn = floor(sqrt(m)), j = 1;
	for (int i = 1; i <= t; i++) {
		if (i == t) s[i].n = m - tn * (t - 1);
		else s[i].n = tn;
		s[i].left = j;
		s[i].right = j + s[i].n - 1;
		s[i].tag = 0;
		j += s[i].n;
	}
	return t;
}

Room query(int len) {
	int f_l, f_r, f = 0;
	int sum;
	bool sum_start;
	for (int i = 1; i <= t && !f; i++)
		if (s[i].tag == -1) {
			if (sum_start) {
				sum += s[i].L;
				if (sum >= len) {
					f_r = i, f = 1;
					break;
				}
				sum_start = 0;
			}
			if (s[i].M >= len) {
				f_l = f_r = i, f = 1;
				break;
			}
			if (s[i].R > 0) {
				sum = s[i].R, f_l = i;
				if (sum >= len) {
					f_r = i, f = 1;
					break;
				}
				sum_start = 1; 
			} 
		} else if (s[i].tag == 0) {
			if (!sum_start) {
				sum = s[i].n, f_l = i;
				if (sum >= len) {
					f_r = i, f = 1;
					break;
				}
				sum_start = 1;
			} else {
				sum += s[i].n;
				if (sum >= len) {
					f_r = i, f = 1;
					break;
				}
			}
//			cout << sum << " " << len << endl;
		} else if (s[i].tag == 1) {
			if (sum_start) {
				sum_start = 0;
			}
		}
	Room ret;
	if (f) ret = {f_l, f_r};
	else ret = {0, 0};
	return ret;
}

int cover(int l, int r, int len) {
	if (l == r) {
		int i = l;
		if (s[i].tag == 0) {
			for (int j = 1; j <= s[i].n; j++)
				s[i].a[j] = 0;
			s[i].tag = -1;
		} 
		int cnt = 0, start;
		for (int j = 1; j <= s[i].n; j++) {
			if (s[i].a[j]) cnt = 0;
			else {
				if (cnt == 0) start = j;
				cnt ++;
				if (cnt == len) {
					break;
				}
			}
//			cout << "*" << j << " " << cnt << "*";
		}
		for (int j = start; j <= start + len - 1; j++)
			s[i].a[j] = 1;
		s[i].rebuild();
//		cout << ">> " << i << endl;
		return start + s[i].left - 1;
	} else {
		int start;
		for (int i = l; i <= r; i++)
			if (i == l)  {
				if (s[i].tag == 0) {
					start = 1;
					len -= s[i].n;
					s[i].tag = 1;
				} else if (s[i].tag == -1) {
					start = s[i].n - s[i].R + 1;
					len -= s[i].L;
					for (int j = s[i].n - s[i].R + 1; j <= s[i].n; j++)
						s[i].a[j] = 1;
					s[i].rebuild();
				}
			}
			else if (i == r) {
				if (s[i].tag == 0) {
					for (int j = 1; j <= s[i].n; j++)
						s[i].a[j] = 0;
					s[i].tag = -1;
				} 
				for (int j = 1; j <= len; j++)
					s[i].a[j] = 1;
				s[i].rebuild();
			}
			else {
				len -= s[i].n;
				s[i].tag = 1;
			}
		return start + s[l].left - 1;
//		cout << ">> " << start << endl;
	}
}

void clear(int l, int r) {
//	printf("clear|%d %d\n", l, r);
	for (int i = 1; i <= t; i++)
		if (l <= s[i].left) {
//			cout << "> > " << i << endl;
			if (l < s[i].left) {
//				cout << "> > " << i - 1 << endl;
				s[i - 1].flat();
				for (int j = (l - s[i - 1].left + 1); j <= (s[i - 1].n); j++)
					s[i - 1].a[j] = 0;
				s[i - 1].rebuild();
			}
			for (; i <= t; i++) {
//				printf("[%d]\n", i);
				if (r >= s[i].right) {
					s[i].tag = 0;
				} else break;
			}
			if (r >= s[i].left) {
				for (int j = 1; j <= (r - s[i].left + 1); j++)
					s[i].a[j] = 0;
				s[i].rebuild();
			}
			break;
		}
}

int main() {
	
//	freopen("hotel.in", "r", stdin);
//	freopen("hotel.out", "w", stdout);
	
	read(m); read(n);
	t = build(n, m);
//	for (int i = 1; i <= t; i++)	
//		cout << s[i].left << " " << s[i].right << endl;

	for (int i = 1; i <= n; i++) {
		read(x);
		if (x == 1) {
			read(a);
			ret = query(a);
			if (ret.l == 0) printf("0\n");
			else {
//				cout << ret.l << " " << ret.r << endl;
				printf("%d\n", cover(ret.l, ret.r, a));
			}
		} else {
			read(a); read(b);
			clear(a, a + b);
		}
		print();
	}
	return 0;
}