#include <bits/stdc++.h>
#define isnum(x) ('0' <= x && x <= '9')
#define read(x) do { \
	x = 0, r::c = getchar(), r::m = 1; \
	while (!isnum(r::c) && r::c != '-') r::c = getchar(); \
	if (r::c == '-') r::c = getchar(), r::m = -1; \
	while (isnum(r::c)) x = x * 10 + r::c - '0', r::c = getchar(); \
	x *= r::m; \
} while(false)
namespace r {
	char c;
	int m;
}
using namespace std;
const int maxn = 210;
int n, x, y, a[maxn], b[maxn];
int check[5][5] = {
    {0, 2, 1, 1, 2},
    {1, 0, 2, 1, 2},
    {2, 1, 0, 2, 1},
    {2, 2, 1, 0, 1},
    {1, 1, 2, 2, 0}
};
int main() {
//	freopen("rps.in", "r+", stdin);
//	freopen("rps.out", "w+", stdout);

    read(n); read(x); read(y);
    for (int i = 1; i <= x; i++)
        read(a[i]);
    for (int i = 1; i <= y; i++)
        read(b[i]);
    int ansA = 0, ansB = 0, nowA, nowB;
    for (int i = 1; i <= n; i++) {
        nowA = a[(i - 1) % x + 1];
        nowB = b[(i - 1) % y + 1];
        if (check[nowA][nowB] == 1)
            ansA++;
		else if (check[nowA][nowB] == 2)
            ansB++;
    }
    printf("%d %d\n", ansA, ansB);
    return 0;
}