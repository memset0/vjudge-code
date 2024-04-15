#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
typedef long long ll;
const int N = 1e5 + 9;
int n, m, a[N], b[N];
long long sum;
struct node {
    int f, c[2], sz, tg;
    int v, pos;
    ll sum[4];
};
struct SPLAY {
    int nod;
    int cnt, rt;
    node t[(N << 1) + 10];
    void Shift(int x, int sv) {
        if (!x) return;
        // cerr << "SFT " << x << " " << sv << "\n";
        ll tmp[4] = {t[x].sum[0], t[x].sum[1], t[x].sum[2], t[x].sum[3]};
        t[x].sum[(0 + sv) & 3] = tmp[0];
        t[x].sum[(1 + sv) & 3] = tmp[1];
        t[x].sum[(2 + sv) & 3] = tmp[2];
        t[x].sum[(3 + sv) & 3] = tmp[3];
        t[x].pos = (t[x].pos + sv) & 3;
        t[x].tg = (t[x].tg + sv) & 3;
    }
    void Psd(int x) {
        if (!t[x].tg) return;
        Shift(t[x].c[0], t[x].tg), Shift(t[x].c[1], t[x].tg);
        t[x].tg = 0;
    }
    void Upd(int x) {
        Psd(x);
        t[x].sz = t[t[x].c[0]].sz + t[t[x].c[1]].sz + 1;
        t[x].sum[0] = t[t[x].c[0]].sum[0] + t[t[x].c[1]].sum[0];
        t[x].sum[1] = t[t[x].c[0]].sum[1] + t[t[x].c[1]].sum[1];
        t[x].sum[2] = t[t[x].c[0]].sum[2] + t[t[x].c[1]].sum[2];
        t[x].sum[3] = t[t[x].c[0]].sum[3] + t[t[x].c[1]].sum[3];
        t[x].sum[t[x].pos] += t[x].v;
    }
    void Rotate(int x) {
        int y = t[x].f, z = t[y].f, c = (x == t[y].c[1]);
        Psd(y), Psd(x);
        t[y].c[c] = t[x].c[c ^ 1], t[t[x].c[c ^ 1]].f = y;
        if (z) t[z].c[t[z].c[1] == y] = x;
        t[x].f = z;
        t[x].c[c ^ 1] = y, t[y].f = x;
        Upd(y), Upd(x);
    }
    void Splay(int x, int tr) {
        int y;
        // cerr << "SPLAY " << x << " " << tr << "\n";
        while (t[x].f != tr) {
            y = t[x].f;
            if (t[t[x].f].f == tr)
                Rotate(x);
            else {
                if ((t[y].c[1] == x) == (t[t[y].f].c[1] == y))
                    Rotate(y);
                else
                    Rotate(x);
                Rotate(x);
            }
        }
        if (!tr) rt = x;
    }
    void New(int x, int v, int rk, int fa) {
        t[x].f = fa;
        // cerr << "T " << x << " .f=" << fa << "\n";
        t[x].sz = 1;
        t[x].v = v, t[x].pos = (rk & 3);
        t[x].sum[t[x].pos] = t[x].v;
    }
    void prt(int x) {
        if (!x) return;
        // Psd(x);
        prt(t[x].c[0]);
        cerr << "NODE " << x << "(" << t[x].v << "):f=" << t[x].f << ",c=[" << t[x].c[0] << "," << t[x].c[1] << "],pos=" << t[x].pos << "\n";
        cerr << "TAGs:" << t[x].tg << "\n";
        prt(t[x].c[1]);
    }
    void Insert(int v) {
        // fprintf(stderr, "INS %d\n", v);
        ++nod;
        if (nod == 1) {
            rt = ++cnt, New(cnt, v, 0, 0);
            return;
        }
        int nw = rt, rk = 0;
        while (1) {
            Psd(nw);
            if (v > t[nw].v) {
                if (!t[nw].c[0]) {
                    t[nw].c[0] = ++cnt, New(cnt, v, rk, nw);
                    break;
                }
                nw = t[nw].c[0];
            } else {
                rk += t[t[nw].c[0]].sz + 1;
                if (!t[nw].c[1]) {
                    t[nw].c[1] = ++cnt, New(cnt, v, rk, nw);
                    break;
                }
                nw = t[nw].c[1];
            }
        }
        while (nw)
            Upd(nw), nw = t[nw].f;
        // cout << "NOWTREE:\n", prt(rt);
        Splay(cnt, 0);
        Shift(t[cnt].c[1], 1), Upd(cnt);
        // cerr << "TREE(" << rt << "):\n", prt(rt);
    }
    void Find(int v) {
        int nw = rt;
        while (1) {
            // Psd(nw);
            if (v == t[nw].v) return (void)Splay(nw, 0);
            if (v > t[nw].v)
                nw = t[nw].c[0];
            else
                nw = t[nw].c[1];
        }
    }
    void Delete(int v) {
        // cerr << "DLT " << v << "\n";
        --nod;
        if (!nod) {
            rt = 0;
            return;
        }
        // cerr << "BTREE:\n", prt(rt);
        Find(v);
        int x = rt;
        // cerr << "TREE:\n", prt(rt);
        int t1 = t[x].c[0], t2 = t[x].c[1];
        if (t1)
            while (t[t1].c[1])
                Psd(t1), t1 = t[t1].c[1];
        if (t2)
            while (t[t2].c[0])
                Psd(t2), t2 = t[t2].c[0];
        if (t1 && t2) {
            Splay(t1, 0), Splay(t2, t1);
            assert(t[x].f == t2);
            t[t2].c[0] = 0, Upd(t2);
            Shift(t2, 3), Upd(t1);
        } else if (t1) {
            Splay(t1, 0);
            assert(t[x].f == t1);
            t[t1].c[1] = 0, Upd(t1);
        } else {
            Splay(t2, 0);
            assert(t[x].f == t2);
            t[t2].c[0] = 0, Upd(t2);
            Shift(t2, 3);
        }
        // cout << "AFTER:\n", prt(rt);
    }
    void Query(ll *res) {
        if (nod) {
            for (int j = 0; j < 4; j++)
                res[j] = t[rt].sum[j];
        } else {
            for (int j = 0; j < 4; j++)
                res[j] = 0;
        }
    }
} bg, sm;
void update(int x, bool fl) {
    // fprintf(stderr, "update %d %d\n", x, fl);
    if (x > 0) {
        if (fl) {
            bg.Insert(x);
        } else {
            bg.Delete(x);
        }
    } else {
        if (fl) {
            sm.Insert(x);
        } else {
            sm.Delete(x);
        }
    }
}
long long solve() {
    static long long tmp[4];
    long long ans = sum;
    bg.Query(tmp);
    // fprintf(stderr, "bg :: %lld %lld %lld %lld\n", tmp[0], tmp[1], tmp[2], tmp[3]);
    ans += tmp[1] + tmp[2];
    sm.Query(tmp);
    // fprintf(stderr, "sm :: %lld %lld %lld %lld\n", tmp[0], tmp[1], tmp[2], tmp[3]);
    if (bg.nod & 1) {
        ans += tmp[0] + tmp[2];
    } else {
        ans += tmp[1] + tmp[3];
    }
    return ans;
}
int main() {
#ifdef popteam
    freopen("I.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        sum += a[i];
        update(b[i] - a[i], 1);
    }
    cout << solve() << endl;
    for (int k, x, y, i = 1; i <= m; i++) {
        cin >> k >> x >> y;
        sum -= a[k];
        update(b[k] - a[k], 0);
        a[k] = x;
        b[k] = y;
        sum += a[k];
        update(b[k] - a[k], 1);
        cout << solve() << endl;
    }
}