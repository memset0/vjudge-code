// luogu-judger-enable-o2
// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
    while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
    static int buf[40];
    if (x == 0) { putc('0'); putc(c); return; }
    if (x < 0) putc('-'), x = -x;
    for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
    while (buf[0]) putc((char) buf[buf[0]--]);
    putc(c);
}

namespace FastIO  {
    const size_t str = 1 << 20;
    const char *endl = "\n";
    struct Reader  {
        char buf[str], *s, *t;
        Reader () : s(), t(), buf() {}
        inline char pick () { return (s == t) ? (t = buf + fread (s = buf, 1, str, stdin), *s++) : (*s++); }
        template < class T > inline Reader &operator >> (T &x) {
            static char ch; static short opt; opt = (ch != 45);
            while (!isdigit(ch = pick()) && (ch ^ -1) && (ch ^ 45));
            if (ch == -1) return *this;
            if (ch == 45) opt = 0, ch = pick();
            for (x = -48 + ch; isdigit(ch = pick()); (x *= 10) += ch - 48);
            opt ? 1 : x = -x; return *this;
        }
    } cin;
    struct Writer  {
        char buf[str], *s, *t;
        Writer () : s (buf), t(buf + str), buf () {}
        ~Writer () { fwrite(buf, 1, s - buf, stdout); }
        inline void echo ( char c ) { (s == t) ? (fwrite(s = buf, 1, str, stdout), *s++ = c) : (*s++ = c); }
        inline Writer& operator << (const char* s) { while (*s) echo(*s++); return *this; }
        template < class T > inline Writer& operator << (T x)  {
            if( !x ) return echo( 48 ), *this;
            static int t[21], top;
            if (x < 0) x = -x, echo ( '-' );
            while ( x ) t[++top] = x % 10, x /= 10;
            while ( top ) echo(t[top--] + 48);
            return *this;
        }
    } cout;
}
using FastIO::cin;
using FastIO::cout;
using FastIO::endl;

const int maxn = 1000010, inf = 1e9;

int n, m, x, y, rt, opt, cnt, top, ans, dep_cnt, FG;
int stk[maxn];

struct point {
    int x[2];
    point () {}
    point (int a, int b) { x[0] = a, x[1] = b; } 
} p[maxn]; 
bool operator < (const point &a, const point &b) {
    return a.x[FG] < b.x[FG];
}

struct node {
    int ch[2], min[2], max[2], cnt;
    point a;
} e[maxn];

#define lc e[u].ch[0]
#define rc e[u].ch[1]

void update(int u) {
    e[u].min[0] = e[u].max[0] = e[u].a.x[0];
    if (lc) e[u].min[0] = std::min(e[u].min[0], e[lc].min[0]);
    if (rc) e[u].min[0] = std::min(e[u].min[0], e[rc].min[0]);
    if (lc) e[u].max[0] = std::max(e[u].max[0], e[lc].max[0]);
    if (rc) e[u].max[0] = std::max(e[u].max[0], e[rc].max[0]);
    e[u].min[1] = e[u].max[1] = e[u].a.x[1];
    if (lc) e[u].min[1] = std::min(e[u].min[1], e[lc].min[1]);
    if (rc) e[u].min[1] = std::min(e[u].min[1], e[rc].min[1]);
    if (lc) e[u].max[1] = std::max(e[u].max[1], e[lc].max[1]);
    if (rc) e[u].max[1] = std::max(e[u].max[1], e[rc].max[1]);
    e[u].cnt = e[lc].cnt + e[rc].cnt + 1;
}

int newnode(point s) {
    int u = top ? stk[top--] : ++cnt;
    e[u].a = s, lc = rc = 0;
//	printf("%d -> %d %d, %d %d\n", u, s.x[0], s.x[1], e[u].a.x[0], e[u].a.x[1]);
    return update(u), u;
}
    
void pia(int u, int k) {
    if (lc) pia(lc, k);
    p[k + e[lc].cnt] = e[u].a, stk[++top] = u;
    if (rc) pia(rc, k + e[lc].cnt + 1);
}

int build(int l, int r, int flag) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    FG = flag, std::nth_element(p + l, p + mid, p + r + 1);
    int u = newnode(p[mid]);
    lc = build(l, mid - 1, flag ^ 1);
    rc = build(mid + 1, r, flag ^ 1);
    return update(u), u;
}

void check(int &u, int flag) {
    #define ratio 4
    if ((e[lc].cnt * ratio < e[rc].cnt) || (e[rc].cnt * ratio < e[lc].cnt)) {
//		printf("%d %d(%d) %d(%d)\n", u, lc, e[lc].cnt, rc, e[rc].cnt);
//		printf("REBUILD\n");
        pia(u, 1);
//		for (int i = 1; i <= e[u].cnt; i++)
//			printf("> %d : %d %d\n", i, p[i].x[0], p[i].x[1]);
        u = build(1, e[u].cnt, flag); 
    }
}

void insert(int &u, point a, int flag) {
//	printf("insert %d %d %d %d\n", u, a.x[0], a.x[1], flag);
    if (!u) return (void)(u = newnode(a));
    insert(a.x[flag] <= e[u].a.x[flag] ? lc : rc, a, flag ^ 1);
    update(u), check(u, flag);
}

inline int min_dis(const point &a, int min[2], int max[2]) {
//    return std::max(0, min[0] - a.x[0]) + std::max(0, a.x[0] - max[0]) +
//        std::max(0, min[1] - a.x[1]) + std::max(0, a.x[1] - max[1]);
    int ret = 0;
    if (min[0] > a.x[0]) ret += min[0] - a.x[0];
    if (a.x[0] > max[0]) ret += a.x[0] - max[0];
    if (min[1] > a.x[1]) ret += min[1] - a.x[1];
    if (a.x[1] > max[1]) ret += a.x[1] - max[1];
    return ret;
}
inline int max_dis(const point &a, int min[2], int max[2]) {
//	return std::max(std::abs(a.x[0] - min[0]), std::abs(a.x[0] - max[0])) +
//		std::max(std::abs(a.x[1] - min[1]), std::abs(a.x[1] - max[1]));
    return std::max(std::abs(a.x[0] - min[0]), std::abs(a.x[0] - max[0])) +
        std::max(std::abs(a.x[1] - min[1]), std::abs(a.x[1] - max[1]));
}
inline int get_dis(const point &a, const point &b) {
    return abs(a.x[0] - b.x[0]) + abs(a.x[1] - b.x[1]);
}

void query(int u, point a) {
    if (!u) return;
    ++dep_cnt;
//	printf("query %d %d %d %d %d\n", u, a.x[0], a.x[1], ans, min_dis(a, e[u].min, e[u].max));
//	printf(">>>>> %d %d %d %d\n", e[u].min[0], e[u].min[1], e[u].max[0], e[u].max[1]);
    ans = std::min(ans, get_dis(a, e[u].a));
    ans = std::min(ans, max_dis(a, e[u].min, e[u].max));
    int dl = lc ? min_dis(a, e[lc].min, e[lc].max) : INT_MAX;
    int dr = rc ? min_dis(a, e[rc].min, e[rc].max) : INT_MAX;
    if (dl < dr) {
        if (dl < ans) query(lc, a);
        if (dr < ans) query(rc, a);
    } else {
        if (dr < ans) query(rc, a);
        if (dl < ans) query(lc, a);
    }
}

void dfs(int u) {
    if (lc) dfs(lc);
    printf("%d : %d %d %d %d %d %d %d %d\n", u, lc, rc, e[u].a.x[0], e[u].a.x[1], e[u].min[0], e[u].min[1], e[u].max[0], e[u].max[1]);
    if (rc) dfs(rc);
}

int main() {
//	freopen("INPUT", "r", stdin);
//	freopen("3.txt", "r", stdin);
//	freopen("1.txt", "w", stdout);
    cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        cin >> x >> y;
////		printf("PRE INSERT %d %d\n", x, y);
//        insert(rt, point(x, y), 0);
////		dfs(rt);
//    }
    for (int i = 1; i <= n; i++) {
    	cin >> x >> y;
    	p[i] = point(x, y);
    }
    rt = build(1, n, 0);
//    printf("finish pre insert\n");
    for (int i = 1; i <= m; i++) {
    	cin >> opt >> x >> y;
//		printf(">>> %d %d %d\n", opt, x, y);
        if (opt == 1) {
            insert(rt, point(x, y), 0);
        } else {
            ans = inf;
            query(rt, point(x, y));
            cout << ans << endl;
        }
//		dfs(rt);
    }
//    std::cerr << std::clock() << std::endl;
    return 0;
}
