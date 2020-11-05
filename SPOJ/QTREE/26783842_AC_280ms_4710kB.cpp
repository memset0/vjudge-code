#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)
#define maxn 10010

typedef int arrT[maxn << 1];
arrT v, w, head, next, a;
arrT dep, top, son, size, fa, dfn, b;
int maxval[maxn << 2];
int n, tot, index, M;

void clear() {
    rep(i, 1, M + n) maxval[i] = 0;
    rep(i, 1, n) dep[i] = top[i] = son[i] = fa[i] = size[i] = dfn[i] = b[i] = head[i] = a[i] = 0;
    rep(i, 0, tot) v[i] = w[i] = next[i] = 0;
    tot = M = index = 0;
}

int max(int a, int b) { return a > b ? a : b; }
#define swap(A, B)   \
    {                \
        int __T = A; \
        A = B;       \
        B = __T;     \
    }

void ae(int x, int y, int z) {
    v[++tot] = y;
    w[tot] = z;
    next[tot] = head[x];
    head[x] = tot;
}
void dfs1(int x) {
    size[x] = 1;
    dep[x] = dep[fa[x]] + 1;
    for (int i = head[x]; i; i = next[i])
        if (v[i] != fa[x]) {
            fa[v[i]] = x;
            a[v[i]] = w[i];
            dfs1(v[i]);
            size[x] += size[v[i]];
            if (size[v[i]] > size[son[x]])
                son[x] = v[i];
        }
}
void dfs2(int x, int t) {
    top[x] = t;
    dfn[x] = ++index;
    b[dfn[x]] = a[x];
    if (son[x]) dfs2(son[x], t);
    for (int i = head[x]; i; i = next[i])
        if (v[i] != son[x] && v[i] != fa[x])
            dfs2(v[i], v[i]);
}

// zkw Segment Tree
void update(int x) {
    maxval[x] = max(maxval[x << 1], maxval[x << 1 | 1]);
}
void build() {
    for (M = 1; M < n + 2; M <<= 1);
    rep(i, M + 1, M + n) maxval[i] = b[i - M];
    rrep(i, M - 1, 1) update(i);
}
void modifySgt(int x, int nv) {
    for (maxval[x += M] = nv, x >>= 1; x; x >>= 1)
        update(x);
}
int queryMaxSgt(int s, int t) {
    int ans = INT_MIN;
    for (s += M - 1, t += M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s & 1) ans = max(ans, maxval[s ^ 1]);
        if (t & 1) ans = max(ans, maxval[t ^ 1]);
    }
    return ans;
}
int queryMax(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, queryMaxSgt(dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) swap(x, y);
    // 这里要注意，如果已经跳到同一个点了就不要查了。
    if (x == y) return ans;
    // dfn[y] + 1 不是 dfn[y]
    ans = max(ans, queryMaxSgt(dfn[y] + 1, dfn[x]));
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        rep(i, 1, n - 1) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            ae(x, y, z);
            ae(y, x, z);
        }
        dfs1(1);
        dfs2(1, 1);
        build();
        while (0207) {
            char str[10] = {0};
            scanf("%s", str);
            if (str[0] == 'Q') {
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%d\n", queryMax(x, y));
            } else if (str[0] == 'C') {
                int c, nv;
                scanf("%d%d", &c, &nv);
                c = (c << 1) - 1;
                int x = v[c], y = v[c + 1];
                if (dep[x] < dep[y]) swap(x, y);
                modifySgt(dfn[x], nv);
            } else break;
        }
        clear();
    }
    return 0;
}