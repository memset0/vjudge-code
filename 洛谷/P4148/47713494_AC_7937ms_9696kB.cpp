// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

namespace FastIO  {
    const size_t str = 1 << 20;
  
    struct Reader  {
        char buf[str], *s, *t;
        Reader ( ) : s( ), t( ), buf() {    }
        inline char pick ( )  {
            return (s == t) ? ( t = buf + fread ( s = buf, 1, str , stdin ), *s++ ) : ( *s++ );
        }
  
        template < class T >
        inline Reader& operator >> ( T& x )  {
            static char ch;
            static short opt;
            opt = (ch != 45);
            while ( !isdigit ( ch = pick () ) && (ch ^ -1) && ( ch ^ 45 ) );
            if ( ch == -1 )     return *this;
            if ( ch == 45 )     {   opt = 0; ch = pick ();   }
            for ( x = -48 + ch; isdigit ( ch = pick () ); ( x *= 10 ) += ch - 48 );
            opt ? 1 : x = -x;
            return *this;
        }
  
    } cin;
  
    struct Writer  {
        char buf[str], *s, *t;
        Writer () : s ( buf ), t( buf + str ), buf ( ) {    }
        ~Writer () { fwrite( buf, 1, s - buf, stdout ); }
  
        inline void echo ( char c )  {
            ( s == t ) ? ( fwrite ( s = buf, 1, str, stdout ), *s++ = c ) : ( *s++ = c );
        }
  
        inline Writer& operator << ( long long x )  {
            if( !x ) return echo( 48 ), *this;
            static int t[21], top;
            if (x < 0) x = -x, echo ( '-' );
            while ( x ) t[++top] = x % 10, x /= 10;
            while ( top ) echo(t[top--] + 48);
            return *this;
        }
        inline Writer& operator << (const char* s)  {
            while ( *s ) echo( *s++ ) ;
            return *this;
        }
    } cout;
    const char *endl = "\n";
} 
 
using FastIO::cin;
using FastIO::cout;
using FastIO::endl;

namespace wyl {
template <typename T> inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}
template <typename T> inline void print(T x, char c = ' ') {
    static int buf[40];
    if (x == 0) { putc('0'); putc(c); return; }
    if (x < 0) putc('-'), x = -x;
    for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
    while (buf[0]) putc((char) buf[buf[0]--]);
    putc(c);
}

const int maxn = 200010;

int n, x, y, k, x1, x2, y1, y2, rt, top, opt, cnt, ans, flag, FG;
int stk[maxn];

struct point {
    int a[2], val;
    point () {}
    point (int x, int y, int z) { a[0] = x, a[1] = y, val = z; }
} p[maxn];
bool operator < (const point &a, const point &b) {
    return a.a[FG] < b.a[FG];
}

struct node {
    int sum, cnt;
    int min[2], max[2], ch[2];
    point x;
    void out() {
        printf("%3d%3d%3d%3d", min[0], min[1], max[0], max[1]);
    }
} e[maxn];

#define lc e[u].ch[0]
#define rc e[u].ch[1]

void update(int u) {
    for (int i = 0; i < 2; i++) {
        e[u].min[i] = e[u].max[i] = e[u].x.a[i];
        if (lc) e[u].min[i] = std::min(e[u].min[i], e[lc].min[i]);
        if (rc) e[u].min[i] = std::min(e[u].min[i], e[rc].min[i]);
        if (lc) e[u].max[i] = std::max(e[u].max[i], e[lc].max[i]);
        if (rc) e[u].max[i] = std::max(e[u].max[i], e[rc].max[i]);
    }
//	printf("[%3d] : ", u), e[u].out(), e[lc].out(), e[rc].out(), puts("");
    e[u].sum = e[lc].sum + e[rc].sum + e[u].x.val;
    e[u].cnt = e[lc].cnt + e[rc].cnt + 1;
}

int newnode(const point &x) {
    int u = top ? stk[top--] : ++cnt;
    lc = rc = 0, e[u].x = x, update(u);
    return u;
}

void pia(int u, int k) {
    if (lc) pia(lc, k);
    p[e[lc].cnt + k] = e[u].x, stk[++top] = u;
    if (rc) pia(rc, e[lc].cnt + k + 1);
}

int build(int l, int r, int flag) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    FG = flag, std::nth_element(p + l, p + mid, p + r + 1);
    int u = newnode(p[mid]);
//	printf("build %d %d %d %d\n", u, l, r, flag);
    lc = build(l, mid - 1, flag ^ 1);
    rc = build(mid + 1, r, flag ^ 1);
    return update(u), u;
}

void check(int &u, int flag) {
    static double ratio = 2.5;
    if (e[lc].cnt * ratio < e[rc].cnt || e[rc].cnt * ratio < e[lc].cnt) {
//		std::cerr << e[lc].cnt << " " << e[rc].cnt << endl;
        pia(u, 1), u = build(1, e[u].cnt, flag);
    }
}

void insert(int &u, const point &x, int flag) {
    if (!u) { u = newnode(x); return; }
    insert(e[u].ch[x.a[flag] <= e[u].x.a[flag] ? 0 : 1], x, flag ^ 1);
    update(u), check(u, flag);
}

bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
    return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
}

bool out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
    return x2 < X1 || X2 < x1 || y2 < Y1 || Y2 < y1;
}

int query(int u, int x1, int y1, int x2, int y2) {
    if (!u) return 0;
    if (in(x1, y1, x2, y2, e[u].min[0], e[u].min[1], e[u].max[0], e[u].max[1]))	return e[u].sum;
//	printf("query %d %d %d %d %d %d %d %d %d\n", u, x1, y1, x2, y2, e[u].min[0], e[u].min[1], e[u].max[0], e[u].max[1]);
    if (out(x1, y1, x2, y2, e[u].min[0], e[u].min[1], e[u].max[0], e[u].max[1])) return 0;
    return (in(x1, y1, x2, y2, e[u].x.a[0], e[u].x.a[1], e[u].x.a[0], e[u].x.a[1]) ? e[u].x.val : 0) +
        query(e[u].ch[0], x1, y1, x2, y2) + query(e[u].ch[1], x1, y1, x2, y2);
}

#undef lc
#undef rc

int main() {

	cin >> n;
    while (true) {
        cin >> opt;
        switch (opt) {
            case 1:
//                read(x), read(y), read(k);
				cin >> x >> y >> k;
                x ^= ans, y ^= ans, k ^= ans;
                insert(rt, point(x, y, k), 0);
                break;
            case 2:
                cin >> x1 >> y1 >> x2 >> y2;
                x1 ^= ans, y1 ^= ans, x2 ^= ans, y2 ^= ans;
                cout << (ans = query(rt, x1, y1, x2, y2)) << endl;
                break;
            case 3:
                return 0;
                break;
        }
    }

    return 0;
}

} int main() { return wyl::main(); }