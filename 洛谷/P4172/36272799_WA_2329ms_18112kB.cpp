#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') fu = -1; c = getchar();}
    while(c >= '0' && c <= '9') {f = (f << 3) + (f << 1) + (c & 15); c = getchar();}
    f *= fu;
}

const int N = 200000 + 10;

struct ele {
    int u, v, a;
    bool operator < (const ele A) const {return a < A.a;}
}p[N];

int fa[N], ch[N][2], rev[N], maxn[N], val[N], wz[N], st[N], n, m, q, len;
bool ok[1010][1010]; int Q[N][3], ans[N], f[N], pre[1010][1010];

int isroot(int u) {return ch[fa[u]][0] != u && ch[fa[u]][1] != u;}

int get(int u) {return ch[fa[u]][1] == u;}

void update(int u) {
    maxn[u] = val[u]; wz[u] = u;
    if(maxn[ch[u][0]] > maxn[u] && ch[u][0]) maxn[u] = maxn[ch[u][0]], wz[u] = wz[ch[u][0]];
    if(maxn[ch[u][1]] > maxn[u] && ch[u][1]) maxn[u] = maxn[ch[u][1]], wz[u] = wz[ch[u][1]];
}

void pushdown(int u) {
    if(rev[u]) {
        swap(ch[u][0], ch[u][1]);
        rev[ch[u][0]] ^= 1;
        rev[ch[u][1]] ^= 1;
        rev[u] ^= 1;
    }
}

void rotate(int u) {
    int old = fa[u], oldd = fa[old], k = get(u);
    if(!isroot(old)) ch[oldd][get(old)] = u; fa[u] = oldd;
    ch[old][k] = ch[u][k ^ 1]; fa[ch[u][k ^ 1]] = old;
    fa[old] = u; ch[u][k ^ 1] = old;
    update(old); update(u);
}

void splay(int u) {
    st[len = 1] = u;
    for(int i = u; !isroot(i); i = fa[i]) st[++len] = fa[i];
    for(int i = len; i >= 1; i--) pushdown(st[i]);
    for(; !isroot(u); rotate(u)) if(!isroot(fa[u])) rotate(get(u) == get(fa[u]) ? fa[u] : u);
}

void access(int u) {
    for(int i = 0; u; i = u, u = fa[u]) {
        splay(u);
        ch[u][1] = i;
        update(u);
    }
}

void makeroot(int u) {
    access(u);
    splay(u);
    rev[u] ^= 1;
}

void link(int u, int v) {
    makeroot(u);
    fa[u] = v;
}

void cut(int u, int v) {
    makeroot(u);
    access(v);
    splay(v);
    fa[u] = ch[v][0] = 0;
    update(v);
}

int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}

int query(int u, int v) {
    makeroot(u);
    access(v);
    splay(v);
    return wz[v];
}

int main() {
    read(n); read(m); read(q);
    for(int i = 1; i <= n; i++) f[i] = i;
    for(int i = 1; i <= m; i++) {
        read(p[i].u); read(p[i].v);
        read(p[i].a);
    }
    for(int i = 1; i <= q; i++) {
        read(Q[i][0]);
        read(Q[i][1]);
        read(Q[i][2]);
        if(Q[i][0] == 2) ok[Q[i][1]][Q[i][2]] = ok[Q[i][2]][Q[i][1]] = 1;
    }
    sort(p + 1, p + m + 1);
    for(int i = 1; i <= m; i++) {
        pre[p[i].u][p[i].v] = pre[p[i].v][p[i].u] = i;
        if(!ok[p[i].u][p[i].v]) {
            if(find(p[i].u) != find(p[i].v)) {
                f[find(p[i].u)] = find(p[i].v);
                val[i + n] = maxn[i + n] = p[i].a;
                link(i + n, p[i].u); link(i + n, p[i].v);
            }
        }
    }
    for(int i = q; i >= 1; i--) {
        if(Q[i][0] == 1) {
            ans[i] = val[query(Q[i][1], Q[i][2])];
        } else {
            int x = Q[i][1], y = Q[i][2], b = pre[x][y];
            int wz = query(x, y);
            if(p[wz - n].a > p[b].a) {
                cut(wz, p[wz - n].u);
                cut(wz, p[wz - n].v);
                link(b + n, p[b].v);
                link(b + n, p[b].u);
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        if(Q[i][0] == 1) printf("%d\n", ans[i]);
    }
    return 0;
}