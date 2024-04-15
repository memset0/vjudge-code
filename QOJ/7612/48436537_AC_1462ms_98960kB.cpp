#include <bits/stdc++.h>
using namespace std;
typedef std::pair<int, int> pii;
typedef long long ll;
const int MAXN = 2011, mod = 1e9 + 7;
void Add(int &a, int t) {
    a += t;
    if (a >= mod) a -= mod;
}
ll Qpow(ll a, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod, p >>= 1;
    }
    return res;
}
int a[MAXN][MAXN], ra[MAXN][MAXN], b[MAXN][MAXN], rb[MAXN][MAXN], res[MAXN][MAXN];
int f[MAXN][MAXN];
int row[MAXN], col[MAXN], cr, cc;
bool type[MAXN];

void gauss(int a[MAXN][15], int n,int m) {//rank = m , n>m
    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= n; ++j)
            if (a[j][i]) {
                std::swap(a[i], a[j]);
                break;
            }
        int inv = Qpow(a[i][i], mod - 2);
        for (int k = 1; k <= m + 1; ++k)
            a[i][k] = ll(a[i][k]) * inv % mod;
        for (int j = 1; j <= n; ++j)
            if (i != j && a[j][i]) {
                int r = a[j][i];
                for (int k = i; k <= m + 1; ++k)
                    a[j][k] = ((a[j][k] - ll(r) * a[i][k]) % mod + mod) % mod;
            }
    }
}
int eq[MAXN][15];
struct one {
    int x, y, v;
    bool operator< (const one& you)const{return x<you.x||(x==you.x&&y<you.y);}
};
std::vector<one> ans;
vector<pii> seq;
int main() {

#ifdef popteam
    // freopen("I.in", "r", stdin);
#endif
    mt19937 rd(std::chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j], ra[i][j] = a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> b[i][j], rb[i][j] = b[i][j], res[i][j] = b[i][j];
    for (int i = 1; i <= n; ++i)
        f[i][i] = 1;
    int lst = rd() % n + 1;
    for (int w = 1; w <= n*3; ++w) {
        int x = rd() % n + 1;
        seq.emplace_back(pii(lst, x));
        lst = x;
    }
    lst = rd() % n + 1;
    for (int w = 1; w <= n*3; ++w) {
        int x = rd() % n + 1;
        seq.emplace_back(pii(lst, x));
        lst = x;
    }
    for (auto [x, y] : seq)
        for (int k = 1; k <= n; ++k)
            Add(ra[y][k], ra[x][k]), Add(f[y][k], f[x][k]);
    int lim=min(12,n);
    for (int c = 1; c <= n; ++c) {
        bool err = 0;
        for (int i=1;i<=lim;++i) {
            int sum = 0;
            for (int k = 1; k <= n; ++k)
                sum = (sum + ll(ra[i][k]) * b[k][c]) % mod;
            // printf("c=%d,i=%d,sum=%d\n", i, c, sum);
            if (sum != f[i][c]) {
                err = 1;
                break;
            }
        }
        if (err) col[++cc] = c; //, printf("Err,c=%d\n", c);
    }
    assert(cc <= 12);
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i)
        f[i][i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ra[i][j] = a[i][j];
    for (auto [x, y] : seq)
        for (int k = 1; k <= n; ++k)
            Add(ra[k][y], ra[k][x]), Add(f[k][y], f[k][x]);
    for (int r = 1; r <= n; ++r) {
        bool err = 0;
        for (int j=1;j<=lim;++j) {
            int sum = 0;
            for (int k = 1; k <= n; ++k)
                sum = (sum + ll(b[r][k]) * ra[k][j]) % mod;
            if (sum != f[r][j]) {
                err = 1;
                break;
            }
        }
        if (err) row[++cr] = r, type[r] = 1; //, printf("Err,r=%d\n", r);
    }
    fprintf(stderr, "cr=%d\n", cr);
    assert(cr <= 12);
    for (int w = 1; w <= cc; ++w) {
        memset(eq, 0, sizeof eq);
        int c = col[w];
        for (int i = 1; i <= n; ++i) {
            if (i == c) ++eq[i][cr + 1];
            int cur = 0;
            for (int r = 1; r <= n; ++r)
                if (type[r])
                    eq[i][++cur] = a[i][r];
                else
                    eq[i][cr + 1] = ((eq[i][cr + 1] - ll(a[i][r]) * b[r][c]) % mod + mod) % mod;
        }
        gauss(eq, n,cr);
        int cur = 0;
        for (int r = 1; r <= n; ++r)
            if (type[r]) {
                ++cur;
                if (res[r][c] != eq[cur][cr + 1]) ans.emplace_back(one{r, c, eq[cur][cr + 1]});
            }
    }
    std::sort(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for (auto P : ans)
        cout << P.x << " " << P.y << " " << P.v << '\n';
    return 0;
}