// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.08 22:49:07
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

const int N = 1e5 + 10;
int n, m, k, max, sum;
int p[N], ans[N];
std::vector <int> appear[N];

struct node {
	int a, s, c, x, val, end, used;
	bool first;
	inline node() {}
	inline node(int _a, int _s, int _c, int _x) {
		a = _a, s =_s, c = _c, x = _x;
		first = 1, val = a + s;
		if (x) end = c % x ? c / x + 1 : c / x;
		else end = 100007;
	}
	inline int calc(int day) { return c - x * (day - 1) - used; }
	inline bool operator < (const node &other) const {
		return val < other.val;
	}
} a[N];
std::priority_queue <node> hep;
std::vector <node> tmp, rub;

struct info {
	int last, cost, delta;
	inline bool operator < (const info &other) const {
		return cost > other.cost;
	}
};
std::priority_queue <info> hap;

void main() {
	read(n), read(m), read(k);
	for (int i = 1, t, s, c, x; i <= n; i++) {
		read(t), read(s), read(c), read(x);
		a[i] = node(t, s, c, x);
	}
	for (int i = 1; i <= k; i++) read(p[i]), max = std::max(max, p[i]);
	for (int i = 1; i <= n; i++)
		if (a[i].end > max) hep.push(a[i]);
		else appear[a[i].end].push_back(i);
	// for (int i = 1; i <= n; i++) {
	// 	printf("[a = %d s = %d c = %d x = %d] end = %d\n", a[i].a, a[i].s, a[i].c, a[i].x, a[i].end);
	// 	for (int j = 1; j <= a[i].end; j++) print(a[i].calc(j), " \n"[j == a[i].end]);
	// }
	for (int day = max; day >= 1; day--) {
		for (std::vector <int> ::iterator it = appear[day].begin(); it != appear[day].end(); it++)
			hep.push(a[*it]);
        // printf("===== day %d =====\n", day);
		for (int now = m, use; now && hep.size(); ) {
			node it = hep.top(); hep.pop();
            // printf(">>> %d %d\n", it.calc(day), now);
			if (it.first) {
				it.used += 1, now -= 1;
				ans[max] += it.val;
				it.first = 0, it.val -= it.s;
                // printf("=> [1] %d %d\n", it.a + it.s, 1);
				hep.push(it);
			} else {
				use = std::min(it.calc(day), now);
				it.used += use, now -= use;
				ans[max] += use * it.a;
                // printf("=> [2] %d %d\n", it.a, use);
				tmp.push_back(it);
			}
		}
		for (std::vector <node> ::iterator it = tmp.begin(); it != tmp.end(); it++)
			if (it->calc(day) || it->x) hep.push(*it);
			else rub.push_back(*it);
		tmp.clear();
	}
	while (hep.size()) rub.push_back(hep.top()), hep.pop();
	for (std::vector <node> ::iterator it = rub.begin(); it != rub.end(); it++) {
		if (it->used == 1) hap.push((info){1, it->a + it->s, it->s});
		else if (it->used) hap.push((info){it->used, it->a, it->s});
		sum += it->used;
	}
	// while (hap.size()) {
	// 	info it = hap.top(); hap.pop();
	// 	std::cout << it.last << " " << it.cost << " " << it.delta << std::endl;
	// }
	for (int day = max - 1; day >= 1; day--) {
		ans[day] = ans[day + 1];
		// printf("===== %d %d =====\n", day, sum - day * m);
		for (int now = std::max(0, sum - day * m), use; now && hap.size(); ) {
			info it = hap.top(); hap.pop();
			if (it.last == 1) {
				ans[day] -= it.cost, --now, --sum;
				// printf("=> [3] 1 %d\n", it.cost);
			} else {
				use = std::min(now, it.last - 1);
				ans[day] -= use * it.cost;
				sum -= use, now -= use, it.last -= use;
				// printf("=> [4] %d %d\n", use, it.cost);
				if (it.last == 1) hap.push((info){1, it.cost + it.delta, it.delta});
				else hap.push(it);
			}
		}
	}
	for (int i = 1; i <= k; i++) print(ans[p[i]], '\n');
}

} signed main() { return ringo::main(), 0; }