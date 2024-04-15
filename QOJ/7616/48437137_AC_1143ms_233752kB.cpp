#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 3e5 + 9, M = N * 60;
int n, m, nod, rt[N], a[N], pos[N], l[N], r[N];
long long ans[N];
struct node {
    int tag, lc, rc;
} p[M];
void build(int &u, int l, int r) {
    u = ++nod;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(p[u].lc, l, mid);
    build(p[u].rc, mid + 1, r);
}
void modify(int &u, int v, int ql, int qr, int k, int l, int r) {
    // fprintf(stderr, "modify %d %d | %d %d | %d | %d %d\n", u, v, ql, qr, k, l, r);
    u = ++nod;
    p[u].lc = p[v].lc;
    p[u].rc = p[v].rc;
    p[u].tag = p[v].tag;
    if (ql == l && qr == r) {
        p[u].tag += k;
        return;
    }
    int mid = (l + r) >> 1;
    if (qr <= mid) {
        modify(p[u].lc, p[v].lc, ql, qr, k, l, mid);
    } else if (ql > mid) {
        modify(p[u].rc, p[v].rc, ql, qr, k, mid + 1, r);
    } else {
        modify(p[u].lc, p[v].lc, ql, mid, k, l, mid);
        modify(p[u].rc, p[v].rc, mid + 1, qr, k, mid + 1, r);
    }
}
struct atom {
    int nod, cnt;
    long long sum;
    inline bool operator<(const atom &rhs) const { return nod < rhs.nod; }
};
void merge_same(vector<atom> &u) {
    sort(all(u));
    int j = 0, lst = -1;
    for (int i = 0; i < u.size(); i++)
        if (u[i].nod == lst) {
            u[j - 1].cnt += u[i].cnt;
            u[j - 1].sum += u[i].sum;
        } else {
            u[j++] = u[i];
            lst = u[i].nod;
        }
    u.resize(j);
    u.shrink_to_fit();
}
void pickup(vector<atom> &u, int l, int r) {
    for (auto &x : u)
        x.sum += (long long)x.cnt * p[x.nod].tag;
    // fprintf(stderr, "pickup l=%d r=%d\n", l, r);
    // for (auto &x : u)
    //     fprintf(stderr, "> nod=%d cnt=%d sum=%d\n", x.nod, x.cnt, x.sum);
    if (l == r) {
        for (auto &x : u) {
            ans[l] += x.sum;
        }
        return;
    }
    int mid = (l + r) >> 1;
    vector<atom> lu = u;
    for (auto &x : lu)
        x.nod = p[x.nod].lc;
    merge_same(lu);
    pickup(lu, l, mid);
    vector<atom> ru = u;
    for (auto &x : ru)
        x.nod = p[x.nod].rc;
    merge_same(ru);
    pickup(ru, mid + 1, r);
}
void dfs(int u, int sum, int l, int r) {
    sum += p[u].tag;
    if (l == r) {
        cerr << sum << " \n"[r == n];
        return;
    }
    int mid = (l + r) >> 1;
    dfs(p[u].lc, sum, l, mid);
    dfs(p[u].rc, sum, mid + 1, r);
}
int st[N], sz;
int main() {
#ifdef popteam
    freopen("K.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    sz = 0;
    for (int i = 1; i <= n; ++i) {
        while (sz && a[st[sz]] < a[i])
            --sz;
        l[i] = (sz ? st[sz] : -1);
        st[++sz] = i;
    }
    sz = 0;
    for (int i = n; i >= 1; --i) {
        while (sz && a[st[sz]] < a[i])
            --sz;
        r[i] = (sz ? st[sz] : -1);
        st[++sz] = i;
    }
    build(rt[pos[n]], 1, n);
    p[rt[pos[n]]].tag++;
    for (int v = n - 1; v >= 1; v--) {
        int i = pos[v];
        int k = l[i] == -1 || r[i] == -1 ? l[i] + r[i] + 1 : (a[l[i]] > a[r[i]] ? l[i] : r[i]);
        // fprintf(stderr, "i=%d v=%d li=%d ri=%d >> %d\n", i, v, l[i], r[i], k);
        rt[i] = rt[k];
        if (l[i] != -1 && l[i] > 1) {
            modify(rt[i], rt[i], 1, l[i] - 1, 1, 1, n);
        }
        if (r[i] != -1 && r[i] < n) {
            modify(rt[i], rt[i], r[i] + 1, n, 1, 1, n);
        }
        // dfs(rt[i], 0, 1, n);
    }
    vector<atom> it;
    for (int i = 1; i <= n; i++)
        it.emplace_back(rt[i], 1, 0);
    pickup(it, 1, n);
    for (int i = 1; i <= n; i++) {
        cout << (ans[i] - 1) << " \n"[i == n];
    }
}