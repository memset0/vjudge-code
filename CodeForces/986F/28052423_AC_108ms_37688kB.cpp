#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define ll long long
#define abs(_o) ((_o < 0) ? -(_o) : _o)
#define double long double
using namespace std;
namespace ywy {
inline ll gsc(ll a, ll b, ll p) {
	a %= p;
	b %= p;
	if (a <= 1000000000 && b <= 1000000000) return ((a * b) % p);
	ll cjr = (double)a * b / p;
	ll res = a * b - cjr * p;
	res %= p;
	res += p;
	res %= p;
	return (res);
}
void exgcd(ll a, ll b, ll& x, ll& y) {
	if (!b) {
		x = 1;
		y = 0;
		return;
	}
	ll x1, y1;
	exgcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
}
inline ll mi(ll a, ll b, ll p) {
	ll ans = 1, tmp = a;
	while (b) {
		if (b & 1) ans = gsc(ans, tmp, p);
		tmp = gsc(tmp, tmp, p);
		b >>= 1;
	}
	return (ans);
}
inline ll Rand() {
	ll a = rand(), b = rand(), c = rand(), d = rand();
	return ((a << 48) | (b << 32) | (c << 16) | d);
}
vector<ll> vec;
int pri[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
inline int check(ll n) {
	if (n == 2 || n == 3 || n == 5 || n == 7) return (1);
	if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return (0);
	for (register int i = 0; i < 10; i++) {
		if (n == pri[i]) return (1);
		ll tmp = n - 1;
		while (1) {
			ll cjr = mi(pri[i], tmp, n);
			if (cjr == n - 1) break;
			if (cjr != 1) return (0);
			if (tmp & 1) break;
			tmp >>= 1;
		}
	}
	return (1);
}
inline ll gcd(ll a, ll b) {
	while (b) {
		ll r = a % b;
		a = b;
		b = r;
	}
	return (a);
}
inline ll rho(ll n, int c) {
	ll x = Rand(), y = x, k = 2;
	while (1) {
		ll ji = 1;
		for (register int i = 1; i <= k; i++) x = (gsc(x, x, n) + c) % n, ji = gsc(ji, abs(y - x), n);
		ll g = gcd(ji, n);
		if (g > 1) return (g);
		y = x;
		k <<= 1;
	}
}
inline void pollard(ll n, int c) {
	if (n == 1) return;
	if (check(n)) {
		vec.push_back(n);
		return;
	}
	while (1) {
		ll cjr = rho(n, c);
		c--;
		if (cjr != n) {
			while (n % cjr == 0) n /= cjr;
			ll g = gcd(n, cjr);
			while (n % g == 0 && g != 1) n /= g;
			pollard(cjr, c);
			pollard(n, c);
			return;
		}
	}
}
ll dis[2000001];
int que[5000001];
unsigned char bv[2000001];
typedef struct _n {
	int id;
	ll n;
	ll k;
	friend bool operator<(const _n& a, const _n& b) { return (a.k < b.k); }
} node;
node memchi[20001];
unsigned char anss[20001];
void ywymain() {
	srand(19260817);
	int q;
	cin >> q;
	for (register int i = 1; i <= q; i++) {
		memchi[i].id = i;
		cin >> memchi[i].n >> memchi[i].k;
	}
	sort(memchi + 1, memchi + 1 + q);
	for (register int x = 1; x <= q; x++) {
		int cjr = x;
		while (cjr < q && memchi[cjr + 1].k == memchi[x].k) cjr++;
		if (memchi[x].k == 1) {
			x = cjr;
			continue;
		}
		vec.clear();
		pollard(memchi[x].k, 19260817);
		sort(vec.begin(), vec.end());
		if (vec.size() == 1) {
			for (register int i = x; i <= cjr; i++) {
				if (memchi[i].n % memchi[i].k == 0) anss[memchi[i].id] = 1;
			}
			x = cjr;
			continue;
		}
		if (vec.size() == 2) {
			ll X, y;
			ll p = vec[1], q = vec[0];
			exgcd(p, q, X, y);
			X %= q;
			X += q;
			X %= q;
			for (register int i = x; i <= cjr; i++) {
				ll dx = gsc(X, memchi[i].n, q), dy = memchi[i].n - dx * p;
				if (dy >= 0) anss[memchi[i].id] = 1;
			}
			x = cjr;
			continue;
		}
		for (register int i = 0; i < vec[0]; i++) dis[i] = 0x7f7f7f7f7f7f7f7f;
		int head = 0, tail = 1;
		que[0] = 0;
		dis[0] = 0;
		do {
			int me = que[head];
			head++;
			bv[me] = 0;
			for (register int i = 1; i < vec.size(); i++) {
				int dst = (me + vec[i]) % vec[0];
				if (dis[me] + vec[i] < dis[dst]) {
					dis[dst] = dis[me] + vec[i];
					if (!bv[dst]) bv[dst] = 1, que[tail] = dst, tail++;
				}
			}
		} while (head < tail);
		for (register int i = x; i <= cjr; i++) {
			if (dis[memchi[i].n % vec[0]] <= memchi[i].n) anss[memchi[i].id] = 1;
		}
		x = cjr;
	}
	for (register int i = 1; i <= q; i++)
		if (anss[i])
			printf("YES\n");
		else
			printf("NO\n");
}
}  // namespace ywy
int main() {
	ywy::ywymain();
	return (0);
}