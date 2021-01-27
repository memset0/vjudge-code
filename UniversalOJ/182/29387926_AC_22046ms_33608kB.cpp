#include <bits/stdc++.h>
template<class T> inline void read(T& x) {
	x = 0;
	char c = getchar();
	bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template<class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 1e5 + 10, mod = 998244353;
int n, m, val[N], ans[N];

struct z {
	int x;
	z(int x = 0) : x(x) {}
	friend inline z operator*(z a, z b) { return (long long)a.x * b.x % mod; }
	friend inline z operator-(z a, z b) {
		return (a.x -= b.x) < 0 ? a.x + mod : a.x;
	}
	friend inline z operator+(z a, z b) {
		return (a.x += b.x) >= mod ? a.x - mod : a.x;
	}
} qry[N], mul[N], pls[N], sl[N], sr[N];
inline z fpow(z a, int b) {
	z s = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) s = s * a;
	return s;
}

struct vet : std::vector<z> {
	using std::vector<z>::vector;
	inline void input(int n) {
		resize(n);
		for (int i = 0; i < n; i++) read(this->operator[](i).x);
	}
	inline void output() {
		for (int i = 0; i < size(); i++)
			print(this->operator[](i).x, " \n"[i + 1 == size()]);
	}
	inline z eval(z x) {
		z s = 0, p = 1;
		for (int i = 0; i < size(); i++)
			s = s + this->operator[](i) * p, p = p * x;
		return s;
	}
};

// ntt
int rev[N << 2];
z w[N << 2];
int init(int len) {
	int lim = 1, k = 0;
	while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (static int len = 1; len < lim; len <<= 1) {
		z wn = fpow(3, (mod - 1) / (len << 1));
		w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = w[i + len - 1] * wn;
	}
	return lim;
}

void dft(vet& a, int lim) {
	a.resize(lim);
	for (int i = 0; i < lim; i++)
		if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				z x = a[i + j], y = w[j + len] * a[i + j + len];
				a[i + j] = x + y, a[i + j + len] = x - y;
			}
}

void idft(vet& a, int lim) {
	dft(a, lim), std::reverse(&a[1], &a[lim]);
	z inv = fpow(lim, mod - 2);
	for (int i = 0; i < lim; i++) a[i] = a[i] * inv;
}

// poly
vet operator+(vet a, const vet& b) {
	a.resize(std::max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) a[i] = a[i] + b[i];
	return a;
}

vet operator-(vet a, const vet& b) {
	a.resize(std::max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) a[i] = a[i] - b[i];
	return a;
}

vet operator*(vet a, vet b) {
	if (a.size() < 10 || b.size() < 10 ||
		(long long)a.size() * b.size() < 1000) {
		vet c(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				c[i + j] = c[i + j] + a[i] * b[j];
		return c;
	}
	int len = a.size() + b.size() - 1, lim = init(len);
	dft(a, lim), dft(b, lim);
	for (int i = 0; i < lim; i++) a[i] = a[i] * b[i];
	idft(a, lim), a.resize(len);
	return a;
}

vet inv(const vet& f, int len = -1) {
	if ((len = ~len ? len : f.size()) == 1) return {fpow(f[0], mod - 2)};
	vet a(&f[0], &f[len]), b = inv(f, (len + 1) >> 1);
	int lim = init((len << 1) - 1);
	dft(a, lim), dft(b, lim);
	for (int i = 0; i < lim; i++) a[i] = b[i] * (2 - a[i] * b[i]);
	idft(a, lim), a.resize(len);
	return a;
}

vet operator%(vet a, vet b) {
	int len = (int)a.size() - b.size() + 1;
	if (len <= 0) return a;
	vet f = a;
	std::reverse(f.begin(), f.end()), f.resize(len);
	vet g = b;
	std::reverse(g.begin(), g.end()), g.resize(len);
	vet q = f * inv(g);
	q.resize(len), std::reverse(q.begin(), q.end());
	vet r = a - q * b;
	r.resize(b.size() - 1);
	return r;
}

// MPE
vet p[N << 2], res;
void mpeBuild(int u, int l, int r, z* g) {
	if (l == r) {
		p[u] = {0 - g[l], 1};
		return;
	}
	int mid = (l + r) >> 1;
	mpeBuild(u << 1, l, mid, g);
	mpeBuild(u << 1 | 1, mid + 1, r, g);
	p[u] = p[u << 1] * p[u << 1 | 1];
}

void mpeDivide(int u, int l, int r, const vet& a, z* res) {
	if (l == r) {
		res[l] = a[0];
		return;
	}
	int mid = (l + r) >> 1;
	mpeDivide(u << 1, l, mid, a % p[u << 1], res);
	mpeDivide(u << 1 | 1, mid + 1, r, a % p[u << 1 | 1], res);
}

struct pack {
	vet p, q;
};
pack divide(int l, int r) {
	if (l == r) return {{1}, {val[l], 1}};
	int mid = (l + r) >> 1;
	pack pl = divide(l, mid), pr = divide(mid + 1, r);
	return {pl.q * pr.p + pl.p * pr.q, pl.q * pr.q};
}

int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	memset(ans, -1, sizeof(ans));
	read(n), read(m);
	z a = 1, b, c, d = 1, sum;
	for (int i = 1; i <= n; i++) read(val[i]), sum = sum + val[i];
	for (int i = 1, o, x; i <= m; i++) {
		if (read(o), o == 1) {
			read(x), a = a + c * x, b = b + d * x;
		} else {
			std::swap(a, c), std::swap(b, d);
		}
		if (c.x) {
			qry[i] = d * fpow(c, mod - 2);
			pls[i] = n * a * fpow(c, mod - 2);
			mul[i] = (b * c - a * d) * fpow(c * c, mod - 2);
		} else {
			ans[i] = (fpow(d, mod - 2) * (b * n + a * sum)).x;
		}
	}
	pack s = divide(1, n);
	mpeBuild(1, 1, std::max(n, m), qry);
	mpeDivide(1, 1, std::max(n, m), s.p, sl);
	mpeDivide(1, 1, std::max(n, m), s.q, sr);
	for (int i = 1; i <= m; i++)
		if (!~ans[i])
			ans[i] = (sl[i] * fpow(sr[i], mod - 2) * mul[i] + pls[i]).x;
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}