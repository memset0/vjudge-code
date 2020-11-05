#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define rep(i, a, b) for(re int i = (a); i <= (b); ++ i)
#define mem(k, p) memset(k, p, sizeof(k))
#define int long long
#define mod 1000000007
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define N 105
il int qpow(int a, int b) { int r = 1; while(b) { if(b & 1) r = r * a % mod; a = a * a % mod, b >>= 1; } return r; }
#define K (1 << 15) + 5
int n, m, a[N], du[N], vis[N], st[N], top, val[N], c[K], dp[N][K], fac[N], inv[N], pax[N], Ans = 1, cnt, tot;
il int C(int a, int b) {
	if(a < b) return 0;
	return fac[a] * inv[b] % mod * inv[a - b] % mod;
}
il void dfs(int x, int st) {
	if(pax[x]) return;
	++ tot, pax[x] = st;
	rep(i, 1, n) if(a[x] % a[i] == 0 || a[i] % a[x] == 0) dfs(i, st);
}
signed main() {
	n = read(), fac[0] = inv[0] = 1;
	rep(i, 1, n) fac[i] = i * fac[i - 1] % mod, inv[i] = qpow(fac[i], mod - 2);
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n) rep(j, 1, n) if(i != j && a[i] % a[j] == 0) ++ du[i];
	rep(T, 1, n) {
		if(pax[T]) continue;
		tot = 0, dfs(T, T), mem(dp, 0), mem(c, 0), top = -1, mem(vis, 0);
		rep(i, 1, n) if(pax[i] == T && du[i] == 0) vis[i] = 1, st[++ top] = a[i];
		if(tot - top <= 2) continue;
		rep(i, 1, n) {
			if(vis[i] == 1 || pax[i] != T) continue;
			rep(j, 0, top) if(a[i] % st[j] == 0) val[i] |= (1 << j);
		}
		int M = (1 << (top + 1)) - 1;
		rep(i, 0, M) rep(j, 1, n) if(pax[j] == T && vis[j] == 0 && ((i & val[j]) == val[j])) ++ c[i];
		rep(i, 1, n) if(vis[i] == 0 && pax[i] == T) ++ dp[1][val[i]];
		rep(i, 1, tot - top - 2) {
			rep(S, 0, M) {
				if(dp[i][S] == 0) continue;
				if(c[S] > i) dp[i + 1][S] = (dp[i + 1][S] + dp[i][S] * (c[S] - i)) % mod;
				rep(j, 1, n) if(pax[j] == T && vis[j] == 0 && ((S & val[j]) != val[j]) && (S & val[j]))
					dp[i + 1][S | val[j]] = (dp[i + 1][S | val[j]] + dp[i][S]) % mod;
			}
		}
		int ans = 0;
		tot = tot - top - 1;
		rep(i, 0, M) ans = (ans + dp[tot][i]) % mod;
		Ans = Ans * ans % mod * C(cnt + tot - 1, tot - 1) % mod;
		cnt += tot - 1;
	}
	cout << Ans;
	return 0;
}