#include<bits/stdc++.h>
#define Clr(x) (t[x].tg=1,t[x].mx=0)
using namespace std;
const int N=2e5;
struct node{
	int mx,tg;
}t[(N<<2)+10];
int n,tc,tu,tv,pos[N+10],opp[N+10],fl;
int sz[N+10],dfn[N+10],ms[N+10];
int q[N+10],nw,iq[N+10],ans,dp[N+10];
vector<int>e[N+10];
void Getsz(int x,int fa){
	sz[x]=1,dfn[x]=++nw;
	int mx=0;
	for(int i=0;i<e[x].size();++i)if(e[x][i]!=fa){
		Getsz(e[x][i],x),sz[x]+=sz[e[x][i]];
		if(sz[e[x][i]]>mx)mx=sz[e[x][i]],ms[x]=e[x][i];
	}
}
void Psd(int x){
	t[x].tg?Clr(x<<1),Clr(x<<1|1),t[x].tg=0:0;
}
void Modify(int x,int l,int r,int id,int v){
	//if(x==1)cout<<"MODIFY "<<id<<" "<<v<<"\n";
	t[x].mx=max(t[x].mx,v);
	if(l==r)return;
	int mid=(l+r>>1);
	Psd(x);
	id<=mid?Modify(x<<1,l,mid,id,v):Modify(x<<1|1,mid+1,r,id,v);
}
int Que(int x,int l,int r,int ql,int qr){
	if(ql>qr||r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr)return t[x].mx;
	Psd(x);
	int mid=(l+r>>1);
	return max(Que(x<<1,l,mid,ql,qr),Que(x<<1|1,mid+1,r,ql,qr));
}
void Add(int x,int fa){
	if(dp[x])Modify(1,1,n,dfn[opp[x]],dp[x]);
	for(int i=0;i<e[x].size();++i)if(e[x][i]!=fa)Add(e[x][i],x);
}
int End(int x){
	return dfn[x]+sz[x]-1;
}
void Solve(int x,int fa){
	iq[x]=++nw,q[nw]=x;
	for(int i=0;i<e[x].size();++i)if(e[x][i]!=fa&&e[x][i]!=ms[x])Solve(e[x][i],x),Clr(1);
	if(ms[x])Solve(ms[x],x);
	for(int i=0;i<e[x].size();++i)if(e[x][i]!=fa&&e[x][i]!=ms[x])Add(e[x][i],x);
	if(opp[x]&&iq[opp[x]]!=-1){
		if(!iq[opp[x]])dp[x]=1+Que(1,1,n,dfn[opp[x]],End(opp[x]));
		else{
			int tmp=q[iq[opp[x]]+1];
			dp[x]=1+max(Que(1,1,n,1,dfn[tmp]-1),Que(1,1,n,End(tmp)+1,n));
		}
		dp[opp[x]]=dp[x];
		Modify(1,1,n,dfn[opp[x]],dp[x]);
		//cout<<"DP "<<x<<"="<<dp[x]<<"\n";
	}else if(opp[x])Modify(1,1,n,dfn[opp[x]],dp[x]);
	--nw,iq[x]=-1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&tc);
		if(pos[tc])opp[i]=pos[tc],opp[pos[tc]]=i;
		else pos[tc]=i;
	}
	for(int i=1;i<n;++i){
		scanf("%d%d",&tu,&tv),e[tu].push_back(tv),e[tv].push_back(tu);
	}
	Getsz(1,0);
	nw=0,Solve(1,0);
	ans=1;
	for(int i=1;i<=n;++i)if(opp[i]){
		fl=1;
		for(int j=0;j<e[i].size();++j)fl&=(e[i][j]!=opp[i]);
		ans=max(ans,(dp[i]<<1)+fl);
	}
	printf("%d",ans);
	return 0;
}
/*
5
1 2 3 2 1
1 2
2 3
3 4
4 5
*/