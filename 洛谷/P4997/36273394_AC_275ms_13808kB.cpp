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


const int maxn = 602, maxm = 360001;
const int mov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, l[2], r[2], ux, uy, vx, vy, flag;
int a[maxn][maxn], c[maxn][maxn], id[maxn][maxn];
int f[maxm], s[maxm];
bool used[maxm];
char ch;

struct node {
    int x, y;
} now, q[2][maxm];

#define at(x,y) id[x][y]

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int calc(int x, int y) {
    for (int t = 0, i, j; t < 4; t++) {
        i = x + mov[t][0];
        j = y + mov[t][1];
        if (i < 1 || j < 1 || i > n || j > n)
            continue;
        if (!~a[i][j])
            return 1;
    }
    return 0;
}

bool check(int x, int y, int col) {
    // printf("check %d %d %d\n", x, y, col);
    if (~a[x][y]) return false;
    a[x][y] = col;
    bool flag = true; int sum = 0, fa[4], nc[4];
    for (int t = 0, i, j; t < 4; t++) {
        i = x + mov[t][0];
        j = y + mov[t][1];
        if (i < 1 || j < 1 || i > n || j > n)
            continue;
        if (!~a[i][j])
            continue;
        fa[t] = find(at(i, j));
        nc[t] = calc(i, j);
        s[fa[t]] += nc[t] - c[i][j];
        if (a[i][j] != a[x][y] && !s[fa[t]])
            flag = false;
    }
    for (int t = 0, i, j; t < 4; t++) {
        i = x + mov[t][0];
        j = y + mov[t][1];
        if (i < 1 || j < 1 || i > n || j > n)
            continue;
        if (!~a[i][j])
            continue;
        int &frm = s[fa[t]];
        if (a[i][j] == a[x][y] && !used[fa[t]]) {
            sum += frm;
            used[fa[t]] = 1;
        }
    }
    for (int t = 0, i, j; t < 4; t++) {
        i = x + mov[t][0];
        j = y + mov[t][1];
        if (i < 1 || j < 1 || i > n || j > n)
            continue;
        if (!~a[i][j])
            continue;
        int &frm = s[fa[t]];
        frm -= nc[t] - c[i][j];
        if (a[i][j] == a[x][y])
            used[fa[t]] = 0;
    }
    sum += calc(x, y);
    if (!sum) flag  = false;
    a[x][y] = -1;
    return flag;
}

void setup(int x, int y, int col) {
    a[x][y] = col;
    for (int t = 0, i, j, f1, f2; t < 4; t++) {
        i = x + mov[t][0];
        j = y + mov[t][1];
        int now = calc(i, j);
        s[find(at(i, j))] += now - c[i][j];
        c[i][j] = now;
        f1 = find(at(i, j));
        f2 = find(at(x, y));
        if (a[i][j] == a[x][y] && f1 != f2) {
            f[f1] = f2;
            s[f2] += s[f1];
        }
    }
}

int main() {
    // freopen("in", "r", stdin);
    
    read(n);
    memset(a, -1, sizeof(a));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
        	id[i][j] = (i - 1) * n + j;
            f[at(i, j)] = at(i, j);
            s[at(i, j)] = 1;
            c[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            while (ch = getc(), ch != '.' && ch != 'X' && ch != 'O');
            switch (ch) {
                case 'X':
                    setup(i, j, 0);
                    break;
                case 'O':
                    setup(i, j, 1);
                    break;
                case '.':
                	q[0][++r[0]] = (node){i, j};
                	q[1][++r[1]] = (node){i, j};
                	break;
            }
        }

    l[0] = l[1] = 1;
    for (int i = 0; true; i ^= 1) {
        flag = 0;
        while (l[i] <= r[i]) {
            now = q[i][l[i]++];
            if (check(now.x, now.y, i)) {
                print(now.x), print(now.y, '\n');
                setup(now.x, now.y, i);
                flag = 1;
                break;
            }
        }
        if (!flag) {
            puts("-1 -1");
            return 0;
        }
    }

    return 0;
}