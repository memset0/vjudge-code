#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
const int N = 100010;
struct node{
	int l, r, idx;
	bool operator < (const node&rhs)const{
		return r < rhs.r;
	}
}a[N];
int n, m, num[N], pre[N << 1], ans[N], j; 
struct SMT{
	int smax, hmax, tag, htag;
}d[N << 2];
inline SMT add(SMT a, SMT b){
	SMT ans;
	ans.smax = max(a.smax, b.smax);
	ans.hmax = max(a.hmax, b.hmax);
	ans.tag = ans.htag = 0;
	return ans;
}
inline void pushup(int p){
	d[p] = add(d[p << 1], d[p << 1 | 1]);
}
inline void pushdown(int p){
	int ls = p << 1, rs = p << 1 | 1;
	d[ls].hmax = max(d[ls].hmax, d[ls].smax + d[p].htag);
	d[ls].htag = max(d[ls].htag, d[ls].tag + d[p].htag);
	d[ls].smax += d[p].tag; d[ls].tag += d[p].tag;
	d[rs].hmax = max(d[rs].hmax, d[rs].smax + d[p].htag);
	d[rs].htag = max(d[rs].htag, d[rs].tag + d[p].htag);
	d[rs].smax += d[p].tag; d[rs].tag += d[p].tag;
	d[p].htag = d[p].tag = 0;
}
inline void change(int p, int l, int r, int x, int y, int z){
	if(x <= l && r <= y){
		d[p].smax += z; d[p].tag += z;
		d[p].hmax = max(d[p].hmax, d[p].smax);
		d[p].htag = max(d[p].htag, d[p].tag);
		return;
	} pushdown(p); dingyi;
	if(x <= mid) change(ls, l, mid, x, y, z);
	if(y > mid) change(rs, mid + 1, r, x, y, z);
	pushup(p);
}
inline SMT query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return d[p];
	pushdown(p); dingyi;
	if(y <= mid) return query(ls, l, mid, x, y);
	if(x > mid) return query(rs, mid + 1, r, x, y);
	return add(query(ls, l, mid, x, y), query(rs, mid + 1, r, x, y));
}
int main(){
	n = read();
	for(int i = 1; i <= n; ++i) num[i] = read();
	m = read();
	for(int i = 1; i <= m; ++i){
		a[i].l = read(); a[i].r = read();
		a[i].idx = i;
	}
	sort(a + (j = 1), a + m + 1);
	for(int i = 1; i <= n; ++i){
		change(1, 1, n, pre[num[i] + N] + 1, i, num[i]);
		pre[num[i] + N] = i;
		for(; j <= m && a[j].r == i; ++j) ans[a[j].idx] = query(1, 1, n, a[j].l, a[j].r).hmax;
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}