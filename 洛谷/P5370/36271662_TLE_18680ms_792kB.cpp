// luogu-judger-enable-o2
// test judgement config
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int g[300],a[N],b[N],c[N],d[N],e[N],A=0;
char s[N];
void I() {
	g['T']=6,g['J']=7,g['Q']=8,g['K']=9,g['A']=10,g['2']=11,g['w']=12,g['W']=13;
}
int V(char c) {
	if('4'<=c&&c<='9') return c-'4';
	return g[c];	
}
int B(int o,int p) {
	for(int i=0;i<=o;i++) {
		int x=o+p-i,y=i;
		for(int j=0;j<14;j++) d[j]=c[j];
		for(int j=13;~j;j--) {
			while(y&&d[j]>=2) d[j]-=2,--y;
			while(x&&d[j]) --d[j],--x;
		}
		if(x|y) continue;
		for(int j=0;j<14;j++) e[j]=a[j];
		x=o+p-i,y=i;
		for(int j=0;j<14;j++) {
			while(y&&e[j]>=2) e[j]-=2,--y;
			while(x&&e[j]) --e[j],--x;	
		}
		if(x|y) continue;
		x=0,y=1;
		for(int j=0;j<14;j++) {
			if(e[j]>x) y=0;
			x+=d[j]-e[j];
		}
		if(y) return 1;
	}
	return 0;
}
int C(int x,int o,int p,int q,int r) {
	if(x==14) return !q&&!r&&B(o,p);
	int f;
	if(c[x]>=4) {
		c[x]-=4,f=C(x+1,o,p+2,q,r+1),c[x]+=4;
		if(f) return 1;
	}
	if(c[x]>=3) {
		c[x]-=3,f=C(x+1,o+1,p,q+1,r),c[x]+=3;
		if(f) return 1;
	}
	if(a[x]>=4&&r) {
		a[x]-=4,f=C(x+1,o,p,q,r-1),a[x]+=4;
		if(f) return 1;	
	}
	if(a[x]>=3&&q) {
		a[x]-=3,f=C(x+1,o,p,q-1,r),a[x]+=3;
		if(f) return 1;
	}
	return C(x+1,o,p,q,r);
}
void D(int x,int s) {
	if(x==14) { if(!s&&C(0,0,0,0,0)) ++A; return; }
	for(int i=0;i<=s&&i<=b[x];i++) c[x]=i,D(x+1,s-i);
}
int main() {
	scanf("%s",s),I();
	for(int i=0;i<12;i++) b[i]=4; b[12]=b[13]=1;
	for(int i=0,v;i<17;i++) v=V(s[i]),++a[v],--b[v];
	D(0,17),printf("%d\n",A);
	return 0;
}