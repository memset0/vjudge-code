// ==============================
//  author: memset0
//  website: https://memset0.cn
//  note: _rqy 又强又可爱
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)

namespace FastIO {
	const int IN_LEN = 1000000, OUT_LEN = 10000000;
	char buf[IN_LEN], obuf[OUT_LEN], *ooh = obuf;
	inline char getc() {
		static char *s, *t;
	    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
	}
	template < class T > inline void read(T &x) {
		static bool iosig;
		static char c;
		for (iosig = false, c = getc(); !isdigit(c); c = getc()) {
			if (c == '-') iosig = true;
			if (c == -1) return;
		}
		for (x = 0; isdigit(c); c = getc())
			x = ((x + (x << 2)) << 1) + (c ^ '0');
		if (iosig) x = -x;
	}
	inline void putc(char c) {
	    if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	    *ooh++ = c;
	}
	inline void flush() {
		fwrite(obuf, 1, ooh - obuf, stdout);
	}
	template < class T > inline void print(T x) {
	    static int buf[30], cnt;
	    if (x == 0) putc('0');
	    else {
	        if (x < 0) putc('-'), x = -x;
	        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
	        while (cnt) putc((char) buf[cnt--]);
	    }
	}
}
using namespace FastIO;

const int maxn = 100010, maxm = maxn * 400;

#define lowbit(x) ((x)&(-(x)))

int n, m, u, pos;
ll ans;
int a[maxn], b[maxn], s[maxn], root[maxn], val[maxm], lc[maxm], rc[maxm];

void modifySEG(int &u, int l, int r, int x, int v) {
	if (!u) u = ++pos;
	val[u] += v;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) modifySEG(lc[u], l, mid, x, v);
	else modifySEG(rc[u], mid + 1, r, x, v);
}

inline void modify(int k) {
	for (int i = k; i <= n; i += lowbit(i))
		modifySEG(root[i], 1, n, a[k], -1);
}

int querySEG(int u, int l, int r, int ql, int qr) {
	if (!u) return 0;
	if (ql == l && qr == r) return val[u];
	int mid = (l + r) >> 1;
	if (qr <= mid) return querySEG(lc[u], l, mid, ql, qr);
	else if (ql > mid) return querySEG(rc[u], mid + 1, r, ql, qr);
	else return querySEG(lc[u], l, mid, ql, mid) +
		querySEG(rc[u], mid + 1, r, mid + 1, qr);
}

inline int query(int l, int r, int ql, int qr) {
	if (l > r || ql > qr) return 0;
	ll sum = 0;
	for (int i = r; i; i -= lowbit(i))
		sum += querySEG(root[i], 1, n, ql, qr);
//	printf(": %d\n", sum);
	for (int i = l - 1; i; i -= lowbit(i))
		sum -= querySEG(root[i], 1, n, ql, qr);
//	printf(": %d\n", sum);
	return sum;
}

int main() {
//	freopen("INPUT", "r", stdin);
//	freopen("OUTPUT", "w", stdout);
	
	read(n), read(m);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		b[a[i]] = i;
	}
	
	for (int i = n; i >= 1; i--) {
		for (int j = a[i]; j; j -= lowbit(j))
			ans += s[j];
		for (int j = a[i]; j <= n; j += lowbit(j))
			s[j] += 1;
		for (int j = i; j <= n; j += lowbit(j))
			modifySEG(root[j], 1, n, a[i], 1);
	}
	
	for (int i = 1; i <= m; i++) {
		print(ans), putc('\n'), read(u);
		ans -= query(1, b[u] - 1, u + 1, n);
		ans -= query(b[u] + 1, n, 1, u - 1);
		modify(b[u]);
	}
	
 	flush();
	return 0;
}
