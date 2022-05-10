// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.06 09:49:14
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
inline char read() {
    static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
    static bool f; static char c;
    for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
    for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
    if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
    if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
    *ooh++ = c;
}
template<class T> inline void print(T x) {
    static int buf[30], cnt;
    if (!x) { print('0'); return; }
    if (x < 0) print('-'), x = -x;
    for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
    while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline void print(T a, int l, int r) {
    for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 6e6 + 10, M = 23;
char s[N]; bool del[N];
int n, siz, len, ans[N], pre[N], tmp[N];

struct setClass {
    int top, stk[100];
    inline void clear() { top = 0; }
    inline void pop_back() { top--; }
    inline int size() { return top; }
    inline void push_back(int x) { stk[top++] = x; }
    inline int& operator[](size_t k) { return stk[k]; }
    inline void reset() {
        int siz = 0;
        for (int i = 0; i < top; i++) {
            if (del[i]) del[i] = 0;
            else tmp[siz++] = stk[i];
        }
        top = siz;
        for (int i = 0; i < top; i++)
            stk[i] = tmp[i];
    }
} set, lis;

void zAlgorithm() {
#define z pre
	z[1] = n;
	for (int i = 2, l = 1, r = 1; i <= n; i++) {
		if (i <= r) z[i] = std::min(r - i + 1, z[i - l - 1]);
		while (i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
	// for (int i = 1; i <= n; i++) print(z[i], " \n"[i == n]);
#undef z
}

inline int better(int i, int j, int L) {
    int lcp = pre[i - j + L + 1	];
    if (lcp < j - i) {
        if (s[i - j + L + 1 + lcp] < s[1 + lcp]) return i;
        if (s[i - j + L + 1 + lcp] > s[1 + lcp]) return j;
    }
    lcp = pre[1 + j - i];
    if (lcp < i - 1) {
        if (s[1 + lcp] < s[1 + j - i + lcp]) return i;
        if (s[1 + lcp] > s[1 + j - i + lcp]) return j;
    }
    return i;
}

void main() {
    scanf("%s", s + 1), n = len = strlen(s + 1);
    zAlgorithm(), set.push_back(1), ans[1] = 1;
    for (int L = 2; L <= len; L++) {
        lis = set, lis.push_back(L), set.clear();
        for (int j = 0; j < lis.size(); j++) {
            bool flag = 1;
            for (int i = set.size() - 1; i >= 0; i--) {
                if (s[set[i] + L - lis[j]] < s[lis[j] + L - lis[j]]) { flag = 0; break; }
				if (s[set[i] + L - lis[j]] > s[lis[j] + L - lis[j]]) set.pop_back();
            }
            if (flag) set.push_back(lis[j]);
        }
        set.reset();
        // for (int i = 0; i < set.size(); i++) std::cerr << set[i] << " \n"[i == set.size() - 1];
        for (int q = 0; q < set.size(); q++)
            for (int p = 0; p < q; p++) {
                int i = set[p], j = set[q];
                if (L - j + 1 < L - i + 1 && L - i + 1 < 2 * (L - j + 1)) {
                    del[q] = 1;
                    break;
                }
            }
        set.reset();
        // for (int i = 0; i < set.size(); i++) std::cerr << set[i] << " \n"[i == set.size() - 1];
        ans[L] = set[0];
        for (int i = 1; i < set.size(); i++) {
            ans[L] = better(ans[L], set[i], L);
        }
    }
    print(ans, 1, len);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    // freopen("2.in", "r", stdin);
    freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
#endif
    ringo::main();
    ringo::flush();
    std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
    return 0;
}