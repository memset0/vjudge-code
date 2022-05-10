#include <bits/stdc++.h>
#define isNum(c) ('0'<=c&&c<='9')
using namespace std;
const int maxn = 100010;
int ret; char chr; bool mrk;
inline int read() {
	chr = getchar(), ret = 0;
	while (!isNum(chr) && chr != '-') chr = getchar();
	if (chr == '-') mrk = true, chr = getchar(); else mrk = false;
	while (isNum(chr)) ret = ret * 10 + chr - '0', chr = getchar();
	if (mrk) return (-ret); else return ret;
}
inline int rand() {
    static int seed = 233333;
    return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
}
struct Node {
	int l, r, val, siz, rnd, cnt;
} d[maxn];
int n, rt = 0, len = 0;
void update(int &p) {
	d[p].siz = d[d[p].l].siz + d[d[p].r].siz + d[p].cnt;
}
void lturn(int &p) {
	int t = d[p].r; 
	d[p].r = d[t].l;
	d[t].l = p;
	d[t].siz = d[p].siz;
	update(p);
	p = t;
}
void rturn(int &p) {
	int t = d[p].l; 
	d[p].l = d[t].r;
	d[t].r = p;
	d[t].siz = d[p].siz;
	update(p);
	p = t;
}
void ins(int &p, int x) {
	if (p == 0) {
		d[p = ++len].rnd = rand(), d[p].val = x, d[p].siz = d[p].cnt = 1;
		return ;
	}
	d[p].siz ++;
    if (d[p].val == x) {
		d[p].cnt++;
	}
	else if (x > d[p].val) {
		ins(d[p].r, x);
		if (d[d[p].r].rnd < d[p].rnd) lturn(p);
	} else {
		ins(d[p].l, x);
		if (d[d[p].l].rnd < d[p].rnd) rturn(p);
	}
}
//void del(int &p,int x)
//{
//    if (p==0) return;
//    if (d[p].val==x)
//    {
//        if (d[p].cnt>1) d[p].cnt--,d[p].siz--;//如果有多个直接减一即可。
//        else
//        {
//            if (d[p].l==0||d[p].r==0) p=d[p].l+d[p].r;//单节点或者空的话直接儿子移上来或者删去即可。
//            else if (d[d[p].l].rnd<d[d[p].r].rnd) rturn(p),del(p,x);
//            else lturn(p),del(p,x); 
//        }
//    }
//    else if (x>d[p].val) d[p].siz--,del(d[p].r,x);
//    else d[p].siz--,del(d[p].l,x);
//}
void del(int &p, int x) {
	if (p == 0) return ;
	if (x < d[p].val) {
		d[p].siz--, del(d[p].l, x);
	} else if (x > d[p].val) {
		d[p].siz--, del(d[p].r, x);
	} else {
		if (d[p].cnt > 1) d[p].cnt--, d[p].siz--;
		else {
			if (!d[p].l || !d[p].r) p = d[p].l + d[p].r;
			else {
				if (d[d[p].l].rnd < d[d[p].r].rnd) {
					rturn(p);
					del(p, x);
				} else {
					lturn(p);
					del(p, x);
				}
			}
		} 
	}
}
void dfs(int &u) {
	if (u == 0) return ;
	dfs(d[u].l);
	for (int i = 1; i <= d[u].cnt; i++)
		printf("%d ", d[u].val);
	dfs(d[u].r);
}
int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		ins(rt, x);
	}
	for (int i = 1; i <= 100; i++)
		ins(rt, i), del(rt, i);
	dfs(rt);
}
