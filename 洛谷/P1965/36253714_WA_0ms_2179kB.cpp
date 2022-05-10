#include <bits/stdc++.h>
#define isnum(x) ('0' <= x && x <= '9')
#define gc() getchar()
#define read(x) { \
	x = 0, r::c = gc(), r::m = 1; \
	while (!isnum(r::c) && r::c != '-') r::c = gc(); \
	if (r::c == '-') r::m = -1, r::c = gc(); \
	while (isnum(r::c)) x = x * 10 + r::c - '0', r::c = gc(); \
	x *= r::m; \
}
using namespace std;
namespace r {
	char c;
	int m;
}
int n, m, k, x;

int main() {
//	freopen("1.txt", "r", stdin);
	
	read(n); read(m); read(k); read(x);

	int p = 10, q = 1;
	while (k) {
		if (k & 1) q = q * p % n;
		p *= p;
		k >>= 1;
	}
	k = p * q % m;
//	cout << k << endl; 
	
	for (int i = 1; i <= k; i++)
		x = (x + m) % n;
	printf("%d\n", x);
	
	return 0;
}