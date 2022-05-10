// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.11 19:26:36
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 1e5 + 10, M = 350, L = 1000;
int n, m, tn, sqn, mod;
int a[N], b[N], bln[N], cnt[N], ans[N], _2[M], __2[M];
ll map_p[L];
std::unordered_map <int, ll> map;

struct query {
    int l, r, p, i;
    inline bool operator < (const query &other) const {
        if (bln[l] != bln[other.l]) return l < other.l;
        return bln[l] & 1 ? r < other.r : r > other.r;
    }
} q[N];

inline int fpow(int b) {
    return (ll)__2[b / sqn] * _2[b % sqn] % mod;
}

inline void addup(int k, ll x) {
	if (!k) return;
	if (k < L) {
		map_p[k] += x;
	} else {
    	map[k] += x;
	}
}

inline void delup(int k, ll x) {
	if (!k) return;
	if (k < L) {
		map_p[k] -= x;
	} else {
		auto it = map.find(k);
		it->second -= x;
		if (!it->second) map.erase(it);
	}
}

inline void add(int x) {
	delup(cnt[x], b[x]);
    ++cnt[x];
	addup(cnt[x], b[x]);
}

inline void del(int x) {
	delup(cnt[x], b[x]);
    --cnt[x];
	addup(cnt[x], b[x]);
}

void main() {
    read(n), read(m), sqn = sqrt(n);
    for (register int i = 1; i <= n; i++) read(a[i]), b[++tn] = a[i];
    std::sort(b + 1, b + tn + 1), tn = std::unique(b + 1, b + tn + 1) - b - 1;
    for (register int i = 1; i <= n; i++) bln[i] = (i - 1) / sqn + 1;
    for (register int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
    for (register int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), read(q[i].p), q[i].i = i;
    std::sort(q + 1, q + m + 1), sqn = sqrt(n) + 1;
    int ul = 1, ur = 0, ql, qr; _2[0] = __2[0] = 1;
    for (register int i = 1; i <= m; i++) {
        ql = q[i].l, qr = q[i].r, mod = q[i].p;
        if (ql > ur) {
            for (register int i = ul; i <= ur; i++) del(a[i]);
            for (register int i = ql; i <= qr; i++) add(a[i]);
            ul = ql, ur = qr;
        } else {
            while (ul > ql) add(a[--ul]);
            while (ur < qr) add(a[++ur]);
            while (ul < ql) del(a[ul++]);
            while (ur > qr) del(a[ur--]);
        }
        for (register int i = 1; i <= sqn; i++) {
            _2[i] = _2[i - 1] << 1;
            if (_2[i] >= mod) _2[i] -= mod;
        }
        for (register int i = 1; i <= sqn; i++) {
            __2[i] = (ll)__2[i - 1] * _2[sqn] % mod;
        }
        int sum = 0, __fpow = fpow(qr - ql + 1), delta = qr - ql + 1;
		for (int i = 1; i < L; i++) if (map_p[i])
			sum = (sum + map_p[i] % mod * (__fpow - fpow(delta - i))) % mod;
        for (auto it : map)
            sum = (sum + it.second % mod * (__fpow - fpow(delta - it.first))) % mod;
        if (sum < 0) sum += mod; ans[q[i].i] = sum;
    }
    for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() { return ringo::main(), ringo::flush(), 0; }