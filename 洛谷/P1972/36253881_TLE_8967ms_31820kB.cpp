// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define isnum(c) ('0' <= c && c <= '9')
#define ll long long
using namespace std;

inline char getc() {
    static const int IN_LEN = 10000000;
    static char buf[IN_LEN], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, IN_LEN, stdin), p1 == p2) ? EOF: *p1++;
}

template <typename T>
inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}

inline void putc(char ch) {
    static const int OUT_LEN = 10000000;
    static char buf[OUT_LEN], *p1 = buf;
    if (ch == -1) fwrite(buf, 1, p1 - buf, stdout);
    if (p1 == buf + OUT_LEN) fwrite(buf, 1, OUT_LEN, stdout), p1 = buf;
    *p1++ = ch;
}
template <typename T>
inline void write(T x){
    if (x < 0) x = -x;
    if (x > 9) write(x / 10);
    putc(x % 10 + 48);
}

const int maxn = 500010, maxm = 500010;
int n, sqn, m, tl, tr, now, ans[maxm], a[maxn], bel[maxn], cnt[1000001];
struct Query{
    int l, r, i;
} b[maxm];
il bool cmp(Query &a, Query &b) { return bel[a.l] ^ bel[b.l] ? a.l < b.l : bel[a.l] & 1 ? a.r < b.r : a.r > b.r; }
int main() {
    read(n);
    for (rg int i = 1; i <= n; i++)
        read(a[i]);
    read(m);
    sqn = 400;
    for (rg int i = 1; i <= n; i++)
        bel[i] = i / sqn;
    for (rg int i = 1; i <= m; i++)
        read(b[i].l), read(b[i].r), b[i].i = i;
    sort(b + 1, b + m + 1, cmp);
    tl = 1, tr = 0;
    for (rg int i = 1; i <= m; i++) {
//		printf("%d %d %d %d\n", i, b[i].i, b[i].l, b[i].r);
        while (b[i].l < tl) now += !cnt[a[--tl]]++;;
        while (b[i].l > tl) now -= !--cnt[a[tl++]];;
        while (b[i].r > tr) now += !cnt[a[++tr]]++;;
        while (b[i].r < tr) now -= !--cnt[a[tr--]];;
        ans[b[i].i] = now;
    }	
    for (rg int i = 1; i <= m; i++)
        write(ans[i]), putc('\n');
    putc(EOF);
    return 0;
}