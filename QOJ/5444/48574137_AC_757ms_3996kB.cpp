#include <bits/stdc++.h>
#define pi pair<int, int>
#define f first
#define s second
#define p2 pair<double, double>
using namespace std;
const int N = 7;
int n, m;
p2 t1, t2;
vector<pi> a, b;
p2 Solve(vector<pi> x, vector<pi> y) {
    if (!x.size() && !y.size()) return (pi){0, 0};
    if (!x.size()) return (pi){0, 1};
    if (!y.size()) return (pi){1, 0};
    vector<pi> tx, ty;
    p2 ret = (pi){0, 0}, tmp;
    for (int i = 0; i < y.size(); ++i) {
        tx = x, ty = y;
        ty[i].f -= tx[0].s;
        tx[0].f -= ty[i].s;
        if (ty[i].f <= 0) ty.erase(ty.begin() + i);
        if (tx[0].f > 0) tx.push_back(tx[0]);
        tx.erase(tx.begin());
        tmp = Solve(ty, tx);
        ret.f += tmp.s / y.size();
        ret.s += tmp.f / y.size();
    }
    return ret;
}
int main() {
    // cin.sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    a.resize(n), b.resize(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i].f, a[i].s = a[i].f;
    for (int i = 0; i < m; ++i)
        cin >> b[i].f, b[i].s = b[i].f;
    if (n > m)
        t1 = Solve(a, b);
    else if (m > n)
        t1 = Solve(b, a), swap(t1.f, t1.s);
    else {
        t1 = Solve(a, b), t2 = Solve(b, a);
        t1.f = (t1.f + t2.s) / 2.0, t1.s = (t1.s + t2.f) / 2.0;
    }
    cout << fixed << setprecision(10) << t1.f << "\n" << t1.s << "\n" << 1.0 - t1.f - t1.s << "\n";
    return 0;
}
/*
2 3
2 5
3 4 1

6 6
1 1 4 5 1 4
1 1 4 5 1 4
*/