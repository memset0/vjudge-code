#include <bits/stdc++.h>
#define pb push_back
using namespace std;

typedef long long ll;
const int N = 3e5 + 10, INF = 1e9;
int n, K;
int a[N], b[N], len[N];

int read() {
	int ret = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) ret = ret * 10 + (c ^ 48), c = getchar();
	return ret;
}

struct seg {
	int l, r, c;
	seg(int _l = 0, int _r = 0, int _c = 0) : l(_l), r(_r), c(_c) {}
	bool operator<(const seg& a) const { return l < a.l || (l == a.l && r < a.r); }
};
set<seg> s;
set<seg>::iterator it;
vector<seg> e[N];
vector<seg>::iterator ti;

void init() {
	s.insert(seg(0, INF, 0));
	for (int i = 1; i <= n; ++i) {
		it = s.lower_bound(seg(a[i], INF, 0));
		--it;
		if (it->r >= b[i]) {
			e[i].pb(seg(a[i], b[i], it->c));
			if (it->l < a[i]) s.insert(seg(it->l, a[i] - 1, it->c));
			if (it->r > b[i]) s.insert(seg(b[i] + 1, it->r, it->c));
			s.erase(it);
			s.insert(seg(a[i], b[i], i));
			continue;
		}
		e[i].pb(seg(a[i], it->r, it->c));
		if (it->l < a[i]) s.insert(seg(it->l, a[i] - 1, it->c));
		s.erase(it++);
		if (it->r < a[i]) ++it;
		while (it->r < b[i]) e[i].pb(*it), s.erase(it++);
		e[i].pb(seg(it->l, b[i], it->c));
		if (it->r > b[i]) s.insert(seg(b[i] + 1, it->r, it->c));
		s.erase(it);
		s.insert(seg(a[i], b[i], i));
	}
}
bool check(int x) {
	int sum = 0;
	ll cnt = 0;
	for (int i = 1, l = 1; i <= n; ++i) {
		sum += (len[i] = b[i] - a[i] + 1);
		for (ti = e[i].begin(); ti != e[i].end(); ++ti) {
			len[ti->c] -= ti->r - ti->l + 1;
			if (ti->c >= l) sum -= ti->r - ti->l + 1;
		}
		while (sum >= x) sum -= len[l], ++l;
		cnt += l - 1;
	}
	return cnt >= K;
}
ll solve(int x) {
	int sum = 0;
	ll ans = 0, cnt = 0, now = 0;
	for (int i = 1, l = 1; i <= n; ++i) {
		sum += (len[i] = b[i] - a[i] + 1);
		for (ti = e[i].begin(); ti != e[i].end(); ++ti) {
			len[ti->c] -= ti->r - ti->l + 1;
			if (ti->c >= l) sum -= ti->r - ti->l + 1;
			if (ti->c && ti->c < l) now -= (ll)ti->c * (ti->r - ti->l + 1);
		}
		while (sum >= x) sum -= len[l], now += (ll)l * len[l], ++l;
		ans += now + (ll)sum * (l - 1);
		cnt += l - 1;
	}
	return ans - (ll)x * (cnt - K);
}

int main() {
	n = read();
	K = read();
	for (int i = 1; i <= n; ++i) a[i] = read(), b[i] = read() - 1;
	init();

	int l = 1, r = INF, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%lld", solve(ans));
	return 0;
}