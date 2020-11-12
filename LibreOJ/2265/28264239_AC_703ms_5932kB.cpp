#include <bits/stdc++.h>
using namespace std;

const int RLEN=1<<18|1;
inline char nc() {
	static char ibuf[RLEN],*ib,*ob;
	(ib==ob) && (ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
	return (ib==ob) ? -1 : *ib++;
}
inline int rd() {
	char ch=nc(); int i=0,f=1;
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=nc();}
	while(isdigit(ch)) {i=(i<<1)+(i<<3)+ch-'0'; ch=nc();}
	return i*f;
}
inline void W(int x) {
	static int buf[50];
	if(!x) {putchar('0'); return;}
	if(x<0) {putchar('-'); x=-x;}
	while(x) {buf[++buf[0]]=x%10; x/=10;}
	while(buf[0]) {putchar(buf[buf[0]--]+'0');}
}

const int N=50005, S=sqrt(N)+3;

int n,Q,a[N],ans[N*4];
struct qry {
	int pos, k, id;
	friend inline bool operator <(const qry &a,const qry &b) {return a.pos<b.pos;}
} q[N*4];

namespace A {
	int a[S][N];
	inline void ins(int v,int x=1,int y=n) {
		if(x>=S) return;
		y=min(y,a[x][0]);
		while(y && a[x][y]<v) --y; ++y;
		if(!a[x][y]) {
			++a[x][0]; a[x][y]=v;
		} else {
			ins(a[x][y],x+1,y);
			a[x][y]=v;
		}
	}
}
namespace B {
	int a[S][N], len[N];
	inline void inc(int pos) {for(int i=pos;i<=n;i+=(i&(-i))) ++len[i];}
	inline int ask(int pos) {int rs=0; for(int i=pos;i;i-=(i&(-i))) rs+=len[i]; return rs;}
	inline int ask(int l,int r) {return ask(r)-ask(l-1);}
	inline void ins(int v,int x=1,int y=n) {
		if(x>=S) return;
		y=min(y,a[x][0]);
		while(y && a[x][y]>=v) --y; ++y;
		if(!a[x][y]) {
			++a[x][0]; a[x][y]=v;	
			inc(y);
		} else {
			ins(a[x][y],x+1,y);
			a[x][y]=v;
		}
	}
}

inline int qry(int k,int rs=0) {
	if(k<S) {
		for(int i=1;i<=k && A::a[i][0];i++) rs+=A::a[i][0];
	} else {
		for(int i=1;i<S;i++) rs+=A::a[i][0];
		rs+=B::ask(S,k);
	} return rs;
}
int main() {
	n=rd(), Q=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=Q;i++) q[i].pos=rd(), q[i].k=rd(), q[i].id=i;
	sort(q+1,q+Q+1);
	for(int i=1,j=1;i<=n && j<=Q;++i) {
		A::ins(a[i]); B::ins(a[i]);
		while(j<=Q && q[j].pos==i) ans[q[j].id]=qry(q[j].k), ++j;
	}
	for(int i=1;i<=Q;i++) W(ans[i]), putchar('\n');
}