// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T > il void read(T &x) {
    x = 0; rg char c = getc(); rg bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getc();
    while (isdigit(c)) x = x * 10 + c - '0', c = getc();
    if (f) x = -x;
}

template < class T > il void print(T x) {
    if (x < 0) putc('-'), x = -x;
    if (x > 9) print(x / 10);
    putc('0' + x % 10);
}

const int N = 1e5 + 10, sqn = 160, M = N / sqn + 10, P = N / sqn + 10;
int n, m, l, r, l1, l2, r1, r2, siz;
int a[N], rnk[N], srt[N], bln[N], lft[N], rit[N], s[M], q1[M], q2[M], fst[P], cnt[P][N];
ll ans, fur[P], sum[P][P], pre[P][N];
bool tag[M];

void modify(int k) { for (; k <= siz; k += k & -k) ++s[k]; }
int query(int k) { int x = 0; for (; k; k -= k & -k) x += s[k]; return x; }
ll get(int a, int b, int c, int d) { return pre[b][d] - pre[b][c - 1] - pre[a - 1][d] + pre[a - 1][c - 1]; }

int merge(int ll1, int rr1, int ll2, int rr2) {
    int l1 = 1, l2 = 1, r1 = 0, r2 = 0, ans = 0;
    memset(tag, 0, sizeof(tag));
    for (rg int i = ll1; i <= rr1; i++) tag[rnk[i]] = 1;
    for (rg int i = 1; i <= fst[bln[l] + 1] - fst[bln[l]]; ++i)
        if (tag[i]) q1[++r1] = srt[fst[bln[l]] + i - 1];
    memset(tag, 0, sizeof(tag));
    for (rg int i = ll2; i <= rr2; i++) tag[rnk[i]] = 1;
    for (rg int i = 1; i <= fst[bln[r] + 1] - fst[bln[r]]; ++i)
        if (tag[i]) q2[++r2] = srt[fst[bln[r]] + i - 1];
    while (l1 <= r1 && l2 <= r2)
        if (q1[l1] < q2[l2]) ++l1;
        else ++l2, ans += r1 - l1 + 1;
    return ans;
}

void main() {
}

} signed main() { return ringo::main(), 0; }

//	for (int i = 1; i <= n; i++) print(a[i]), putc(i == n ? '\n' : ' ');
//	for (int i = 1; i <= n; i++) print(bln[i]), putc(i == n ? '\n' : ' ');
//	for (int i = 1; i <= n; i++) print(lft[i]), putc(i == n ? '\n' : ' ');
//	for (int i = 1; i <= n; i++) print(rit[i]), putc(i == n ? '\n' : ' ');
//	for (int i = 1; i <= bln[n]; i++) for (int j = 1; j <= bln[n]; j++)
//		print(sum[i][j]), putc(j == bln[n] ? '\n' : ' ');
