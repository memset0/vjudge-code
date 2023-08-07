#include<bits/stdc++.h>
#define Add(p,v) (t[p].s+=v*(t[p].r-t[p].l+1),t[p].tg+=v)
using namespace std;
const int N=1e5,L=17;
struct node{
	int l,r;
	long long s,tg;
}t[(N<<2)+10];
struct edge{
	int t,nxt;
}e[(N<<1)+10];
int n,Q,fa[N+10],be[N+10],cnt;
int dfn[N+10],sz[N+10],num[N+10][L+3];
int op,qi,qy,qk;
long long qv[N+10][L+3],tt;
queue<int>q;
void add(int x,int y){
	e[++cnt]=(edge){y,be[x]},be[x]=cnt;
}
void Upd(int x){
	t[x].s=t[x<<1].s+t[x<<1|1].s;
}
void Psd(int x){
	t[x].tg?Add(x<<1,t[x].tg),Add(x<<1|1,t[x].tg),t[x].tg=0:0;
}
void Build(int x,int l,int r){
	t[x].l=l,t[x].r=r;
	if(l==r)return;
	int mid=l+r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
void Modify(int x,int l,int r,long long vl){
	if(r<t[x].l||t[x].r<l)return;
	if(l<=t[x].l&&t[x].r<=r)return(void)Add(x,vl);
	Psd(x),Modify(x<<1,l,r,vl),Modify(x<<1|1,l,r,vl),Upd(x);
}
long long Query(int x,int l,int r){
	if(r<t[x].l||t[x].r<l)return 0;
	if(l<=t[x].l&&t[x].r<=r)return t[x].s;
	Psd(x);
	return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}
void dfs(int x){
	dfn[x]=++cnt,sz[x]=num[x][0]=1;
	for(int i=be[x];i;i=e[i].nxt){
		dfs(e[i].t),++num[x][1];
		sz[x]+=sz[e[i].t];
		for(int j=2;j<=L;++j)num[x][j]+=num[e[i].t][j-1];
	}
}
int main(){
	scanf("%d%d",&n,&Q);
	for(int i=2;i<=n;++i)scanf("%d",&fa[i]),add(fa[i],i);
	cnt=0,dfs(1),Build(1,1,n);
	while(Q--){
		scanf("%d%d",&op,&qi);
		if(op==1){
			scanf("%d%d",&qy,&qk);
			if(qk==1)Modify(1,dfn[qi],dfn[qi]+sz[qi]-1,qy);
			else{
				tt=0;
				for(int i=0;qy;++i,qy/=qk)qv[qi][i]+=qy,tt+=1ll*qy*num[qi][i];
				Modify(1,dfn[qi],dfn[qi],tt);
			}
		}else{
			tt=Query(1,dfn[qi],dfn[qi]+sz[qi]-1);
			for(int i=1,f=fa[qi];i<=L&&f;++i,f=fa[f]){
				for(int j=0;i+j<=L;++j)tt+=qv[f][i+j]*num[qi][j];
			}
			printf("%lld\n",tt);
		}
	}
	return 0;
}