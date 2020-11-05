#include <bits/stdc++.h>
const int sum = 1 << 21;
char ibuf[sum], *iS, *iT, obuf[sum], *oS = obuf, *oT = oS + sum - 1;
#define flush() (fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void())
#define putchar(x) (*oS++ = (x), oS == oT ? flush() : void())
struct Flusher_ {
	~Flusher_() { flush(); }
} flusher_;
template<class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> inline void print(T x, char c) { print(x), putchar(c); }
const int N = 2e6 + 10;
int n;
long long k;
bool check(int mid) {
	long long sum = mid + k;
	for (int i = 1; i < mid; ++i) {
		--sum;
		if (sum >= i + 1)
			sum -= sum / (i + 1);
		else {
			return (sum <= 1) ? 1 : sum <= mid - i;
		}
	}
	return 0;
}
int main() {
#ifdef memset0
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	std::cin >> k;
	int l = 0, r = N;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	print(r, '\n');
	long long sum = 0;
	for (int i = 1; i <= r; ++i) {
		int x = (r + k - sum) % (i + 1);
		if (x < 0) x += i + 1;
		print(x, ' ');
		sum += x;
	}
}
