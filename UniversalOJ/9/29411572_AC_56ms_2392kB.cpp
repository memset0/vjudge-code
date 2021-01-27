// =================================
//   author: memset0
//   date: 2019.06.23 13:03:18
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

const int N = 110;
char s[N];
int n, m, len;
std::vector<int> now;
std::vector<std::vector<int>> set;

inline bool cmp(const std::vector<int> &a, const std::vector<int> &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = 0; i < a.size(); i++) if (a[i] != b[i]) return a[i] < b[i];
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1), m = strlen(s + 1);
        if (i == 1) {
            while (isalpha(s[len + 1]) || s[len + 1] == '_')
                ++len;
        }
        now.clear();
        for (int i = len + 1; i <= m; i++)
            if (isdigit(s[i])) now.push_back(s[i]);
            else break;
        set.push_back(now);
    }
    std::sort(set.begin(), set.end(), cmp);
    for (auto it : set) {
        for (int i = 1; i <= len; i++) putchar(s[i]);
        for (auto ch : it) putchar(ch);
        puts(".in");
    }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}