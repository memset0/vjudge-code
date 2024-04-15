#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1000011;
const int m1 = 998244353, m2 = 1e9 + 9, base = 131;
ll Qpow1(ll a, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * a % m1;
        a = a * a % m1, p >>= 1;
    }
    return res;
}
ll Qpow2(ll a, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * a % m2;
        a = a * a % m2, p >>= 1;
    }
    return res;
}
struct Hash {
    int x, y;
    Hash(int _x = 0, int _y = 0) { x = _x, y = _y; }
    Hash operator+(const Hash &you) {
        int f = x + you.x, g = y + you.y;
        if (f >= m1) f -= m1;
        if (g >= m2) g -= m2;
        return Hash(f, g);
    }
    Hash operator-(const Hash &you) {
        int f = x - you.x, g = y - you.y;
        if (f < 0) f += m1;
        if (g < 0) g += m2;
        return Hash(f, g);
    }
    Hash operator*(const Hash &you) { return Hash((ll)x * you.x % m1, (ll)y * you.y % m2); }
    Hash inv() { return Hash((int)Qpow1(x, m1 - 2), (int)Qpow2(y, m2 - 2)); }
    bool operator==(const Hash &you) {
        // printf("Compare %d %d with %d %d\n", x, y, you.x, you.y);
        return x == you.x && y == you.y;
    }
} f[MAXN], pw[MAXN];
Hash Qpow(Hash a, int p) {
    Hash res(1, 1);
    while (p) {
        if (p & 1) res = res * a;
        a = a * a, p >>= 1;
    }
    return res;
}
Hash Sum(Hash x, Hash q, int n) {
    // printf("Sum([%d,%d],%d,%d)=", x.x, x.y, q.x, n);
    Hash res = x * (Qpow(q, n) - Hash(1, 1)) * ((q - Hash(1, 1)).inv());
    // printf("%d %d\n", res.x, res.y);
    return res;
}
Hash get(int l, int r) {
    // printf("get[%d,%d]\n", l, r);
    return f[r] - f[l - 1] * pw[r - l + 1];
}
char s[MAXN];

struct PAM {
    int t[MAXN][26];
    int last, tot, now, fail[MAXN], len[MAXN], size[MAXN];
    int period[MAXN];
    Hash h[MAXN], g[MAXN];
    bool mark[MAXN];
    PAM() {
        len[0] = -1;
        last = tot = 1;
        h[0] = h[1] = {0, 0};
    }
    void extend(int w) {
        int pos = last;
        while (pos && s[now - len[pos]] - 'a' != w)
            pos = fail[pos];
        if (!t[pos][w]) {
            int cur = ++tot;
            t[pos][w] = cur, len[cur] = len[pos] + 2;
            h[cur] = get(now + 2 - len[cur], now + 1);
            // printf("cur=%d,len=%d,(%d,%d)\n", cur, len[cur], h[cur].x, h[cur].y);
            if (!pos)
                fail[cur] = 1;
            else {
                pos = fail[pos];
                while (pos && s[now - len[pos]] - 'a' != w)
                    pos = fail[pos];
                fail[cur] = t[pos][w];
            }
            last = tot;
        } else {
            last = t[pos][w];
        }
        ++now, ++size[last];
    }
    ll solve() {
        // puts("Enter 85!\n");
        for (int u = tot; u; --u)
            size[fail[u]] += size[u];
        for (int u = 2; u <= tot; ++u) {
            int f = fail[u], p = period[f];
            Hash x = g[f];
            // printf("u=%d(%d),f=%d(%d),p=%d,h=%d\n", u, len[u], f, len[f], p, h[u].x);
            if (p && Sum(x, pw[p], len[u] / p) == h[u])
                period[u] = p, g[u] = x, mark[f] = 1; //, printf("mark %d\n", f);
            else
                period[u] = len[u], g[u] = h[u];
            // if (period[u] == len[u]) ans += (ll)len[u] * len[u];
        }

        ll ans = 0;
        for (int u = 2; u <= tot; ++u)
            if (!mark[u]) ans += (ll)(len[u] / period[u]) * (len[u] / period[u]);
        return ans;
    }
} pam;
int main() {
#ifdef popteam
    freopen("H.in", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    pw[0] = Hash(1, 1);
    for (int i = 1; i < MAXN; ++i)
        pw[i] = pw[i - 1] * Hash(base, base);
    for (int i = 1; i <= n; ++i) {
        // printf("String %d:", i);
        scanf("%s", s + 1);
        pam.last = 1, pam.now = 0;
        int m = strlen(s + 1);
        f[0] = Hash(0, 0);
        for (int j = 1; j <= m; ++j)
            f[j] = Hash(((ll)f[j - 1].x * base + s[j]) % m1, ((ll)f[j - 1].y * base + s[j]) % m2);
        for (int j = 1; j <= m; ++j)
            pam.extend(s[j] - 'a');
    }
    printf("%lld\n", pam.solve());
    return 0;
}