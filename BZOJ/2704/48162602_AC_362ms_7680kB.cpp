#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long dint;
#define _l (long long int)
#define mbit(_x_,_y_) ((_l _x_)<<((_y_)<<2))
#define gbit(_x_,_y_) (((_x_)>>((_y_)<<2))&0xf)

const int maxn = 13;
const int maxst = 570009;

dint slst[maxst];
int n, m, v[maxn][maxn], tots, f[2][maxst], cnt[17];
bool av[2][maxst];

void dfsState(int l, int tot, dint z) {
    if (l == m) {
        for (int i = 1; i <= tot; ++ i)
            if (cnt[i] != 2)
                return;
        slst[tots ++] = z;
    }
    else {
        for (int i = 0; i <= tot; ++ i)
            if (!i || cnt[i] == 1) {
                ++ cnt[i];
                dfsState(l + 1, tot, z | mbit(i, l));
                -- cnt[i];
            }
        ++ cnt[tot + 1];
        dfsState(l + 1, tot + 1, z | mbit(tot + 1, l));
        -- cnt[tot + 1];
        if (!cnt[15] && l < m - 1) {
            ++ cnt[15];
            dfsState(l + 1, tot, z | mbit(15, l));
            -- cnt[15];
        }

    }
}

void preState() {
    tots = 0;
    memset(cnt, 0, sizeof(cnt));
    dfsState(0, 0, 0);
    sort(slst, slst + tots);
}

inline int fState(dint x) {
    return lower_bound(slst, slst + tots, x) - slst;
    //if (slst[ret] != x)
        //puts("naive");
    //return ret;
}

#define fUpMax(_sa_,_sv_) { \
    register int _a_(_sa_), _v_(_sv_); \
    if (!av[cur][_a_]) { \
        av[cur][_a_] = 1; \
        f[cur][_a_] = _v_; \
    } \
    else if (_v_ > f[cur][_a_]) \
        f[cur][_a_] = _v_; \
}
#define upMax(_a_,_b_) { \
    if (_a_ < _b_) \
        _a_ = _b_; \
}

void unzipState(dint z, int* a) {
    for (int i = 0; i < m; ++ i)
        a[i] = gbit(z, i);
}

dint zipState(int* a) {
    dint s(0);
    for (int i = 0; i < m; ++ i)
        s |= mbit(a[i], i);
    return s;
}

bool isFinalPlug(int *a, int y) {
    for (int i = 0; i < y - 1; ++ i)
        if (a[i])
            return 0;
    for (int i = y + 1; i <m; ++ i)
        if (a[i])
            return 0;
    return 1;
}

int mergePlug(int* a, int y) {
    static int b[maxn], c[17];
    memcpy(b, a, sizeof(b));
    if (a[y - 1] == 15) {
        b[y - 1] = b[y];
        b[y] = 0;
    }
    else {
        int f(a[y - 1]), t(a[y]);
        for (int i = 0; i < m; ++ i)
            if (b[i] == f)
                b[i] = t;
        b[y - 1] = b[y] = 0;
        memset(c, 0, sizeof(c));
        f = 0;
        for (int i = 0; i < m; ++ i)
            if (b[i]) {
                if (c[b[i]])
                    b[i] = c[b[i]];
                else
                    b[i] = c[b[i]] = ++ f;
            }
    }
    return fState(zipState(b));
}

int extendPlugRight(int* a, int y) {
    static int b[maxn];
    memcpy(b, a, sizeof(b));
    if (a[y - 1] == 15) {
        int t(1);
        for (int i = 0; i < y - 1; ++ i)
            if (a[i] < 15 && a[i] + 1 > t)
                t = a[i] + 1;
        for (int i = y + 1; i < m; ++ i)
            if (a[i] < 15 && a[i] >= t)
                ++ b[i];
        b[y - 1] = b[y] = t;
    }
    else {
        b[y] = b[y - 1];
        b[y - 1] = 0;
    }
    return fState(zipState(b));
}

int newPlug(int* a, int y) {
    static int b[maxn];
    memcpy(b, a, sizeof(b));
    b[y] = 15;
    return fState(zipState(b));
}

int dp() {
    int prv(0), cur(1), so(fState(15)), ans(0);
    memset(av, 0, sizeof(av));
    av[cur][so] = 1;
    f[cur][so] = v[0][0];
    for (int x = 0; x < n; ++ x)
        for (int y = !x ? 1 : 0; y < m; ++ y) {
            swap(prv, cur);
            memset(av[cur], 0, sizeof(av[cur]));
            for (int i = 0; i < tots; ++ i)
                if (av[prv][i]) {
                    dint s(slst[i]);
                    static int a[maxn];
                    unzipState(s, a);
                    if (v[x][y]) {
                        if (y && a[y - 1] && a[y]) {
                            if (a[y - 1] == a[y]) {
                                if (isFinalPlug(a, y))
                                    upMax(ans, f[prv][i] + v[x][y]);
                            }
                            else {
                                fUpMax(mergePlug(a, y), f[prv][i] + v[x][y]);
                            }
                        }
                        if (y && a[y - 1] && !a[y])
                            fUpMax(extendPlugRight(a, y), f[prv][i] + v[x][y]);
                        if (a[y] && (!y || a[y - 1] != 15)) 
                            fUpMax(i, f[prv][i] + v[x][y]);
                        if (!a[y] && (!y || a[y - 1] != 15) && y < m - 1)
                            fUpMax(newPlug(a, y), f[prv][i] + v[x][y]);
                    }
                    if (!a[y] && (!y || a[y - 1] != 15))
                        fUpMax(i, f[prv][i]);
                }
        }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    bool sw(0);
    scanf("%d%d", &n, &m);
    if (n < m)
        sw = 1;
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j)
            if (sw)
                scanf("%d", v[j] + i);
            else
                scanf("%d", v[i] + j);
    if (sw)
        swap(n, m);
    preState();
    printf("%d\n", dp());
}