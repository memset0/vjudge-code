// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.10 10:12:54
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
template <class T> inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}
template <class T> inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 2e5 + 10, M = N * 200;
char s[N];
ll ans, dis[M]; 
std::vector <int> G[M];
int T, m, len, cnt, nod;
int x[N], y[N], q[M], val[M], ind[M];

namespace sa {
    const int M = N << 1;
    int siz, sa[M], rnk[M], tmp[M], tax[M], log[M], height[M], st[N][20];
    int query(int l, int r) {
        if (l > r) std::swap(l, r); l++; int t = log[r - l + 1];
        return std::min(st[l][t], st[r - (1 << t) + 1][t]);
    }
    void sort() {
        for (int i = 1; i <= siz; i++) tax[i] = 0;
        for (int i = 1; i <= len; i++) tax[rnk[i]]++;
        for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
        for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
    }
    void build(char *s) {
        memset(sa, 0, sizeof(sa)), memset(rnk, 0, sizeof(rnk)), memset(tmp, 0, sizeof(tmp)), memset(height, 0, sizeof(height));
        siz = 200, log[0] = -1;
        for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i, log[i] = log[i >> 1] + 1;
        sort();
        for (int now = 1, cnt = 0; cnt < len; siz = cnt, now <<= 1) {
            cnt = 0;
            for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
            for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now;
            sort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
            for (int i = 2; i <= len; i++) rnk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now]) ? cnt : ++cnt;
        }
        for (int i = 1, j, ans = 0; i <= len; i++) {
            j = sa[rnk[i] - 1]; if (ans) --ans;
            while (s[i + ans] == s[j + ans]) ++ans;
            height[rnk[i]] = ans;
        }
        height[1] = 0;
        for (int i = 1; i <= len; i++) st[i][0] = height[i];
        for (int i = 1; i < 20; i++)
            for (int j = 1; j + (1 << i) - 1 <= len; j++)
                st[j][i] = std::min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    }
}

namespace seg {
    int rt, nod, lc[M], rc[M], cnt[M];
    void build(int &u, int l, int r) {
        u = ++nod, cnt[u] = ++ringo::cnt, lc[u] = 0, rc[u] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(lc[u], l, mid);
        build(rc[u], mid + 1, r);
        G[cnt[u]].push_back(cnt[lc[u]]);
        G[cnt[u]].push_back(cnt[rc[u]]);
    }
    void modify(int &u, int k, int c, int l, int r) {
        int v = u; u = ++nod;
        lc[u] = lc[v], rc[u] = rc[v], cnt[u] = ++ringo::cnt;
        G[cnt[u]].push_back(cnt[v]);
        if (l == r) { G[cnt[u]].push_back(c); return; }
        int mid = (l + r) >> 1;
        if (k <= mid) modify(lc[u], k, c, l, mid), G[cnt[u]].push_back(cnt[lc[u]]);
        else modify(rc[u], k, c, mid + 1, r), G[cnt[u]].push_back(cnt[rc[u]]);
    }
    void query(int u, int ql, int qr, int s, int l, int r) {
        if (l == ql && r == qr) { G[s].push_back(cnt[u]); return; }
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(lc[u], ql, qr, s, l, mid);
        if (ql > mid) return query(rc[u], ql, qr, s, mid + 1, r);
        query(lc[u], ql, mid, s, l, mid), query(rc[u], mid + 1, qr, s, mid + 1, r);
    }
}

struct array {
    int n, l[N], r[N], id[N], len[N];
    inline void init() {
        read(n);
        for (int i = 1; i <= n; i++) read(l[i]), read(r[i]), id[i] = ++cnt, len[i] = r[i] - l[i] + 1;
    }
} a, b;

inline ll find_answer() {
    int l = 1, r = 0, u;
    for (int u = 1; u <= cnt; u++) for (auto v : G[u]) ind[v]++;
    for (int i = 1; i <= cnt; i++) if (!ind[i]) q[++r] = i;
    while (l <= r) {
        u = q[l++], ans = std::max(ans, dis[u]);
        for (auto v : G[u]) {
            dis[v] = std::max(dis[v], dis[u] + val[v]);
            if (!--ind[v]) q[++r] = v;
        }
    }
    if (r != cnt) return -1;
    return ans;
}

inline bool is_link(int s, int e) {
    int l = 1, r = 1, u; q[1] = s;
    while (l <= r) {
        u = q[l++];
        if (u == e) return true;
        for (auto v : G[u]) q[++r] = v;
    }
    return false;
}

void solve() {
    // puts("===========================");
    scanf("%s", s + 1), len = strlen(s + 1), a.init(), b.init(), read(m);
    for (int i = 1; i <= a.n; i++) G[1].push_back(a.id[i]), val[a.id[i]] = a.len[i];
    for (int i = 1; i <= m; i++) read(x[i]), read(y[i]), G[a.id[x[i]]].push_back(b.id[y[i]]);
    sa::build(s);
    
    std::vector<std::tuple<int, bool, int>> q;
    for (int i = 1; i <= a.n; i++) q.push_back(std::make_tuple(a.len[i], false, i));
    for (int i = 1; i <= b.n; i++) q.push_back(std::make_tuple(b.len[i], true, i));
    std::sort(q.begin(), q.end(),
        [](const std::tuple<int, bool, int> &a, const std::tuple<int, bool, int> &b) -> bool {
            return std::get<0>(a) == std::get<0>(b) ? std::get<1>(a) < std::get<1>(b) : std::get<0>(a) > std::get<0>(b);
        }       
    );
    seg::build(seg::rt, 1, len);
    for (const auto &it : q) {
        int i = std::get<2>(it);
        // printf(">> %c %d len=%d\n", std::get<1>(it) ? 'b' : 'a', i, std::get<0>(it));
        if (std::get<1>(it)) {
            int U = sa::rnk[b.l[i]], L = U, R = U;
            for (int l = 1, r = U - 1, mid; mid = l + r >> 1, l <= r; )
                if (sa::query(mid, U) >= b.len[i]) L = mid, r = mid - 1;
                else l = mid + 1;
            for (int l = U + 1, r = len, mid; mid = l + r >> 1, l <= r; )
                if (sa::query(U, mid) >= b.len[i]) R = mid, l = mid + 1;
                else r = mid - 1;
            // printf("%d : U = %d L = %d R = %d\n", i, U, L, R);
            seg::query(seg::rt, L, R, b.id[i], 1, len);
        } else {
            // printf(">>> append[%d] << %d\n", sa::rnk[a.l[i]], a.id[i]);
            seg::modify(seg::rt, sa::rnk[a.l[i]], a.id[i], 1, len);
        }
    }
    print(find_answer(), '\n');
    // for (int i = 1; i <= b.n; i++)
    //     for (int j = 1; j <= a.n; j++)
    //         if (is_link(b.id[i], a.id[j]))
    //             printf("b[%d] -> a[%d]\n", i, j);
    // for (int i = 1; i <= a.n; i++) print(a.id[i], " \n"[i == a.n]);
    // for (int i = 1; i <= b.n; i++) print(b.id[i], " \n"[i == b.n]);
    // for (int i = 1; i <= cnt; i++) for (auto j : G[i]) printf("%d %d\n", i, j);
}

void init() {
    for (int i = 1; i <= cnt; i++) G[i].clear(), dis[i] = ind[i] = val[i] = 0;
    cnt = 1, ans = 0, seg::rt = seg::nod = 0;
}
void main() { for (read(T); T--; ) init(), solve(); }

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}