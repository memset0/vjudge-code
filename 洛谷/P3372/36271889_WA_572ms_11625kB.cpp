#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int n, m, l, r;
char d;
long long a[maxn], s[maxn], c, ans;
struct Node {
    int l, r, mid;
    long long val, dt;
} p[maxn * 4];
void push_up(int u, long long x) {
    p[u].val += x * (p[u].r - p[u].l + 1);
    p[u].dt = x;
}
void push_down(int u) {
    if (p[u].dt) {
    	if (p[u].l < p[u].r) {
    		push_up(u << 1, p[u].dt);
        	push_up(u << 1 | 1, p[u].dt);
        }
        p[u].dt = 0;
    }
}
void build (int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) / 2, p[u].dt = 0;
    p[u].val = s[r] - s[l - 1]; //初始化数值 
    if (l == r) return ;
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
}
void update(int u, int l, int r, long long c) {
	push_down(u);
    if (l == p[u].l && r == p[u].r) push_up(u, c);
    else {
	    if (r <= p[u].mid) update(u << 1, l, r, c);
	    else if (l > p[u].mid) update(u << 1 | 1, l, r, c);
	    else {
	        update(u << 1, l, p[u].mid, c);
	        update(u << 1 | 1, p[u].mid + 1, r, c);
	    }
	    p[u].val = p[u << 1].val + p[u << 1 | 1].val;
		//回朔，不回朔的做法不能解决部分题目 
	}
}
void query(int u, int l, int r) {
	push_down(u);
    if (l == p[u].l && r == p[u].r) ans += p[u].val;
    else {
	    if (r <= p[u].mid) query(u << 1, l, r);
	    else if (l > p[u].mid) query(u << 1 | 1, l, r);
	    else {
	        query(u << 1, l, p[u].mid);
	        query(u << 1 | 1, p[u].mid + 1, r);
	    }
	}
}
int main() {
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &d);
        if (d == 1) {
        	scanf("%d%d%lld", &l, &r, &c);
            update(1, l, r, c);
        } else {
            scanf("%d%d", &l, &r);
            ans = 0; //全局变量存结果，少一点思考量 
            query(1, l, r);
            printf("%lld\n", ans);
        }
    }
    return 0;
}