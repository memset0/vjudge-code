#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
struct Line{
	int k;
	long long b;
	long long F(int x){
		return 1ll*k*x+b;
	}
}q[N+10];
int n,y;
int m,num[N+10],nw,sz;
long long sum[N+10],dp[N+10];
char s[N+10];
bool Cov(Line l1,Line l2,Line l3){
	return 1ll*(l2.b-l1.b)*(l1.k-l3.k)>=(l3.b-l1.b)*(l1.k-l2.k);
}
void Ins(Line l){
	if(sz<nw)return(void)(q[++sz]=l);
	if(q[sz].k==l.k){
		if(q[sz].b>=l.b)q[sz]=l;
		return;
	}
	while(sz>nw&&Cov(l,q[sz-1],q[sz]))--sz;
	q[++sz]=l;
}
int main(){
	scanf("%d%d",&n,&y);
	scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		if(s[i]=='?')++m,num[m]=nw,sum[m]=sum[m-1]+nw;
		else ++nw;
	}
	nw=1;
	Ins((Line){0,0});
	for(int i=0;i<=m;++i){
		while(nw<sz&&q[nw].F(i)>=q[nw+1].F(i))++nw;
		dp[i]=q[nw].F(i)+sum[i]+y;
		if(i<m)Ins((Line){-num[i+1],1ll*i*num[i+1]-sum[i]+dp[i]});
	}
	printf("%lld",dp[m]-y);
	return 0;
}