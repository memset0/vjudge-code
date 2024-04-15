#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define getw(x) (x == t[t[x].f].c[1])
#define isr(x) (t[t[x].f].v != t[x].v)
#define pi pair<int, int>
#define f first
#define s second
using namespace std;
const int N = 5e5;
struct node {
    int f, c[2], v, sz;
} t[N + 10];
int n, Q, a[N + 10], rt, lg[N + 10], id[N + 10];
long long ans, prt[N + 10];
pi mx[22][N + 10];
string op[N + 10];
void Upd(int x) { t[x].sz = t[t[x].c[0]].sz + t[t[x].c[1]].sz + 1; }
void Rotate(int x) {
    int c = getw(x), y = t[x].f;
    t[y].c[c] = t[x].c[c ^ 1], t[t[x].c[c ^ 1]].f = y;
    if (t[y].f) t[t[y].f].c[getw(y)] = x;
    t[x].f = t[y].f;
    t[x].c[c ^ 1] = y, t[y].f = x;
    Upd(y), Upd(x);
}
void Splay(int x) {
    // cout << "(SPLAY " << x << ")";
    int y;
    while (!isr(x)) {
        y = t[x].f;
        if (isr(y))
            Rotate(x);
        else {
            if (getw(y) == getw(x))
                Rotate(y);
            else
                Rotate(x);
            Rotate(x);
        }
    }
    if (!t[x].f) rt = x;
}
void _Splay(int x) {
    // cout << "(_SPLAY " << x << ")";
    int y;
    while (!isr(t[x].f)) {
        y = t[x].f;
        if (isr(t[y].f))
            Rotate(x);
        else {
            if (getw(y) == getw(x))
                Rotate(y);
            else
                Rotate(x);
            Rotate(x);
        }
    }
}
pi Max(int l, int r) {
    int k = lg[r - l + 1];
    return max(mx[k][l], mx[k][r - (1 << k) + 1]);
}
void Prt(int x) {
    if (!x) return;
    Prt(t[x].c[0]);
    cout << x << "[" << t[x].c[0] << "," << t[x].c[1] << "],sz=" << t[x].sz << " v=" << t[x].v << "\n";
    Prt(t[x].c[1]);
}
void Inc(int x) {
    Splay(x), ++t[x].v, ans += 1ll * (t[t[x].c[0]].sz + 1) * (t[t[x].c[1]].sz + 1);
    // cout << "ANS+=" << 1ll * (t[t[x].c[0]].sz + 1) * (t[t[x].c[1]].sz + 1) << "\n";
    Splay(x);
}
void Dec(int x) {
    // cout << "DEC " << x << "\n";
    Splay(x);
    // cout << "TREE " << x << ":\n";
    // Prt(rt);
    int t1 = t[x].c[0], t2 = t[x].c[1];
    if (t[t1].v == t[x].v) {
        while (t[t[t1].c[1]].v == t[t1].v)
            t1 = t[t1].c[1];
        Splay(t1);
    }
    if (t[t2].v == t[x].v) {
        while (t[t[t2].c[0]].v == t[t2].v)
            t2 = t[t2].c[0];
        if (t[t1].v == t[x].v)
            _Splay(t2);
        else
            Splay(t2);
    }
    /*cout << "T1=" << t1 << " T2=" << t2 << "\n";
    if (!((!t[x].c[0] || isr(t[x].c[0])) && (!t[x].c[1] || isr(t[x].c[1])))) {
        cout << "! tree=\n";
        Prt(rt);
    }*/
    assert((!t[x].c[0] || isr(t[x].c[0])) && (!t[x].c[1] || isr(t[x].c[1])));
    --t[x].v, ans -= 1ll * (t[t[x].c[0]].sz + 1) * (t[t[x].c[1]].sz + 1);
    // cout << "ANS-=" << 1ll * (t[t[x].c[0]].sz + 1) * (t[t[x].c[1]].sz + 1) << "\n";
}
int Build(int fa, int l, int r) {
    if (l > r) return 0;
    // cout << "BUILD " << fa << " [" << l << " " << r << "]\n";
    int p = Max(l, r).s;
    ans += 1ll * a[p] * (r - p + 1) * (p - l + 1);
    t[p].f = fa, t[p].v = a[p];
    if (!fa) rt = p;
    t[p].c[0] = Build(p, l, p - 1), t[p].c[1] = Build(p, p + 1, r);
    Upd(p);
    return p;
}
void Solve(int fl) {
    // cout << "------------------------SOLVE " << fl << "\n";
    for (int i = 1; i <= n; ++i)
        mx[0][i] = (pi){a[i], i};
    for (int i = 1; i <= lg[n]; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << i - 1)]);
    ans = 0, Build(0, 1, n);
    // cout << "TREE=" << rt << "\n", Prt(rt);
    // cout << "ANS=" << ans << "\n";
    for (int i = 1; i <= Q; ++i) {
        if (op[i][0] == '+')
            fl ? Dec(id[i]), 0 : (Inc(id[i]), 0);
        else
            fl ? Inc(id[i]), 0 : (Dec(id[i]), 0);
        prt[i] += ans;
        // cout << "op " << op[i] << " " << id[i] << ",ans=" << ans << ",rt=" << rt << "\n";
        // Prt(rt);
    }
}
int main() {
#ifdef popteam
    freopen("F.in", "r", stdin);
#endif
    // cin.tie(0)->sync_with_stdio(0);
    cin >> n >> Q;
    t[0].v = -1919810;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= Q; ++i)
        cin >> op[i] >> id[i];
    Solve(0);
    for (int i = 1; i <= n; ++i)
        a[i] = -a[i];
    Solve(1);
    for (int i = 1; i <= Q; ++i)
        cout << prt[i] << "\n";
}