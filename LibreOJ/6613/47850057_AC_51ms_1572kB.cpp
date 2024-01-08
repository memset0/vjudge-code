// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.15 17:57:49
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

int n;
std::vector<std::pair<int, int>> opt;

bool isQueue() {
	std::queue<int> q;
	for (auto it : opt)
		if (it.first == 1) q.push(it.second);
		else {
			if (!q.size()) return false;
			if (q.front() != it.second) return false;
			q.pop();
		}
	return true;
}

bool isStack() {
	std::stack<int> q;
	for (auto it : opt)
		if (it.first == 1) q.push(it.second);
		else {
			if (!q.size()) return false;
			if (q.top() != it.second) return false;
			q.pop();
		}
	return true;
}

bool isHeap1() {
	std::priority_queue<int> q;
	for (auto it : opt)
		if (it.first == 1) q.push(it.second);
		else {
			if (!q.size()) return false;
			if (q.top() != it.second) return false;
			q.pop();
		}
	return true;
}

bool isHeap2() {
	std::priority_queue<int, std::vector<int>, std::greater<int>> q;
	for (auto it : opt)
		if (it.first == 1) q.push(it.second);
		else {
			if (!q.size()) return false;
			if (q.top() != it.second) return false;
			q.pop();
		}
	return true;
}

void main() {
    read(n);
	for (int i = 1, x, y; i <= n; i++) {
		read(x), read(y);
		opt.push_back(std::make_pair(x, y));
	}
	std::string t[] = {"No", "Yes"};
	std::cout << t[isQueue()] << "\n" << t[isStack()] << "\n" << t[isHeap1()] << "\n" << t[isHeap2()] << std::endl;
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}