#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define pi pair<int, int>
#define f first
#define s second
using namespace std;
const int N = 1e5, B = 29;
struct val {
    int v, pos;
    bool operator<(const val &y) const { return v < y.v; }
} ar[N + 10], qs[N + 10];
struct UD {
    int f[N + 10], sz[N + 10], TIM, t[N + 10], tt;
    pi ar[N + 10];
    long long ans;
    void init(int n) {
        for (int i = 1; i <= n; ++i)
            f[i] = i, sz[i] = 1;
        ans = TIM = tt = 0;
    }
    void Rec() { ++TIM; }
    void Back() {
        // cout << "BACK\n";
        while (tt && t[tt] == TIM) {
            sz[ar[tt].f] -= sz[ar[tt].s], ans -= 1ll * sz[ar[tt].f] * sz[ar[tt].s], f[ar[tt].s] = ar[tt].s;
            --tt;
        }
        --TIM;
    }
    int getf(int x) { return f[x] == x ? x : getf(f[x]); }
    void Merge(int x, int y) {
        // cout << "APPLY " << x << " " << y << "\n";
        x = getf(x), y = getf(y);
        // cout << "x=" << x << " y=" << y << "\n";
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        ar[++tt] = (pi){x, y};
        t[tt] = TIM, ans += 1ll * sz[x] * sz[y], sz[x] += sz[y], f[y] = x;
        // cout << "ANS=" << ans << "\n";
    }
} D;
int n, m, K, Q, u[N + 10], v[N + 10], c[N + 10];
int num, mp[N + 10];
long long prt[N + 10];
vector<pi> es[N + 10];
void Solve(int b, int l, int r, int ql, int qr) {
    if (ql > qr) return;
    // cout << "SOLVE " << b << " " << l << " " << r << " " << ql << " " << qr << "\n";
    if (b < 0 || l > r) {
        for (int i = ql; i <= qr; ++i)
            prt[qs[i].pos] = D.ans;
        return;
    }
    int p1 = l, p2 = r, p, d;
    while (!((mp[p1] >> b) & 1) && ((mp[p2] >> b) & 1))
        ++p1, --p2;
    p = (((mp[p2] >> b) & 1) ? p1 - 1 : p2);
    p1 = ql, p2 = qr;
    while (!((qs[p1].v >> b) & 1) && ((qs[p2].v >> b) & 1))
        ++p1, --p2;
    d = (((qs[p2].v >> b) & 1) ? p1 - 1 : p2);
    if ((K >> b) & 1) {
        D.Rec();
        for (int i = l; i <= p; ++i) {
            for (pi j : es[i])
                D.Merge(j.f, j.s);
        }
        Solve(b - 1, p + 1, r, ql, d);
        D.Back();
        D.Rec();
        for (int i = p + 1; i <= r; ++i) {
            for (pi j : es[i])
                D.Merge(j.f, j.s);
        }
        Solve(b - 1, l, p, d + 1, qr);
        D.Back();
    } else {
        Solve(b - 1, l, p, ql, d);
        Solve(b - 1, p + 1, r, d + 1, qr);
    }
}
int main() {
#ifdef popteam
    freopen("N.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> K;
    D.init(n);
    for (int i = 1; i <= m; ++i)
        cin >> u[i] >> v[i] >> c[i], ar[i] = (val){c[i], i};
    sort(ar + 1, ar + m + 1), ar[0].v = -1;
    for (int i = 1; i <= m; ++i)
        num += (ar[i].v != ar[i - 1].v), mp[num] = ar[i].v, es[num].push_back((pi){u[ar[i].pos], v[ar[i].pos]});
    cin >> Q;
    for (int i = 1; i <= Q; ++i)
        cin >> qs[i].v, qs[i].pos = i;
    sort(qs + 1, qs + Q + 1);
    Solve(B, 1, num, 1, Q);
    for (int i = 1; i <= Q; ++i)
        cout << prt[i] << "\n";
}