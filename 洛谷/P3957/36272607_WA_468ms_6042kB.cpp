#include <bits/stdc++.h>
using namespace std;
const int maxn = 500000;
int n, d, k, ll, rr, mid, l, r, j, dp[maxn], mark[maxn];
struct house {
    int x, s;
} a[maxn];
bool cmp(house a, house b) {
	return a.x < b.x;
}
bool check(int g) {
	memset(dp, -1, sizeof(dp));
	memset(mark, 0, sizeof(mark));
	if (g < d) {
		l = d - g;
		r = d + g;
	} else {
		l = 1;
		r = d + g;
	}
	dp[0] = 0; mark[0] = 1;
	for (int i = 0; i < n; i++) 
		if (mark[i]) {
			j = 1; while (a[j].x - a[i].x < l && j <= n) j++;
			if (a[j].x - a[i].x < l) break;
			while (a[j].x - a[i].x <= r && j <= n) {
//				cout << j << " ";
				if (dp[i] + a[i].s > dp[j]) dp[j] = dp[i] + a[i].s, mark[j] = 1;
				j++;
			}
//			cout << endl;
		}
//	for (int i = 1; i <= n; i++)
//		printf("%d ", dp[i]);
//	puts("");
//	printf("%d %d %d %d\n", g, dp[n], l, r);
//	puts("");
	if (dp[n] >= k) return true;
	else return false;
}
int main() {
    scanf("%d%d%d", &n, &d, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].s);
    int sum = 0;
    for (int i = 1; i <= n; i++)
        if (a[i].s > 0) sum += a[i].s;
    if (sum < k) {
        puts("-1");
        return 0;
    }
    a[0].x = 0, a[0].s = 0;
    sort(a, a + n + 1, cmp);
    ll = 1, rr = a[n].x, mid;
    while (ll + 3 < rr) {
        mid = (ll + rr) / 2;
        if (check(mid)) rr = mid;
        else ll = mid + 1;
    }
    for (int i = ll; i <= rr; i++)
        if (check(i)) {
            printf("%d\n", i);
            return 0;
        }
    return 0;
}



//考场敲的代码
//DFS + 二分答案 10分 
//#include <bits/stdc++.h>
//using namespace std;
//const int maxn = 500000;
//int n, d, k, ll, rr, mid, l, r, j, dp[maxn];
//bool mark;
//struct house {
//    int x, s;
//} a[maxn];
//void check(int u, int s, int l, int r) {
////	cout << u << " " << s << " " << l << " " << r << endl;
//    if (u == n && s >= k) {	
//        mark = true;
//        return ;
//    }
//    for (int j = u + 1; j <= n && a[j].x - a[u].x <= r; j++)
//        if (a[j].x - a[u].x < l) continue;
//        else {
////			cout << a[j].x - a[u].x << " ";
//            check(j, s + a[j].s, l, r);
//            if (mark) return;
//        }
//}
//bool check_(int g) {
//    int l, r;
//    if (g < d) {
//        l = d - g;
//        r = d + g;
//    } else {
//        l = 1;
//        r = d + g;
//    }
//    mark = false;
//    check(0, 0, l, r);
////	puts("");
//    return mark;
//}
////bool check(int g) {
////	memset(dp, -1, sizeof(dp));
////	memset(mark, 0, sizeof(mark));
////	if (g < d) {
////		l = d - g;
////		r = d + g;
////	} else {
////		l = 1;
////		r = d + g;
////	}
////	dp[0] = 0; mark[0] = 1;
////	for (int i = 0; i < n; i++) 
////		if (mark[i]) {
////			j = i + 1; while (a[j].x - a[i].x < l && j <= n) j++;
////			if (a[j].x - a[i].x < l) break;
////			while (a[j].x - a[i].x <= r && j <= n) {
////				cout << j << " ";
////				if (dp[i] + a[i].s > dp[j]) dp[j] = dp[i] + a[i].s, mark[j] = 1;
////				j++;
////			}
////			cout << endl;
////		}
////	for (int i = 1; i <= n; i++)
////		printf("%d ", dp[i]);
////	puts("");
////	printf("%d %d %d %d\n", g, dp[n], l, r);
////	puts("");
////	if (dp[n] >= k) return true;
////	else return false;
////}
//int main() {
//    scanf("%d%d%d", &n, &d, &k);
//    for (int i = 1; i <= n; i++)
//        scanf("%d%d", &a[i].x, &a[i].s);
//    int sum = 0;
//    for (int i = 1; i <= n; i++)
//        if (a[i].s > 0) sum += a[i].s;
//    if (sum < k) {
//        puts("-1");
//        return 0;
//    }
//    a[0].x = 0, a[0].s = 0;
//    ll = 1, rr = a[n].x, mid;
//    while (ll + 3 < rr) {
//        mid = (ll + rr) / 2;
//        if (check_(mid)) rr = mid;
//        else ll = mid + 1;
//    }
//    for (int i = ll; i <= rr; i++)
//        if (check_(i)) {
//            printf("%d\n", i);
//            return 0;
//        }
//    return 0;
//}