#include <bits/stdc++.h>
#define isnum(x) ('0' <= x && x <= '9')
#define read(x) do { \
	x = 0, r::c = getchar(), r::m = 1; \
	while (!isnum(r::c) && r::c != '-') r::c = getchar(); \
	if (r::c == '-') r::c = getchar(), r::m = -1; \
	while (isnum(r::c)) x = x * 10 + r::c - '0', r::c = getchar(); \
	x *= r::m; \
} while (false) 
namespace r { char c; int m; }
#define M1 1000000007
#define M2 999999997
#define M3 999989991
using namespace std;
const int maxn = 110;
const int maxm = 1000010;
int n, m, a[maxn], cnt = 0, ans[maxm];
long long sum;

bool cal(int x) {
    sum = 0;
    for (int i = n; i >= 0; i--)
        sum = ((sum * x) + a[i] + M1) % M1;
    if (sum) return 1;
    sum = 0;
    for (int i = n; i >= 0; i--)
        sum = ((sum * x) + a[i] + M2) % M2;
    if (sum) return 1;
    sum = 0;
    for (int i = n; i >= 0; i--)
        sum = ((sum * x) + a[i] + M3) % M3;
    if (sum) return 1;
}
int main() {
	
    read(n); read(m);
    for (int i = 0; i <= n; i++)
        read(a[i]);
    
    for (int i = 1; i <= m; i++)
        if (!cal(i)) ans[++cnt] = i;
    
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++)
        printf("%d\n", ans[i]);
    return 0;
}