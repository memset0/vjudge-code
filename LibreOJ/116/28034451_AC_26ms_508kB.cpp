#include<bits/stdc++.h>
const int N=210,M=21000;
int n,m,s,e,h,t,ss,ee,flow,q[N],dep[N],pre[N];
int tot,hed[N],to[M],val[M],nxt[M],cur[N];
inline void add(int u,int v,int w){
	nxt[tot]=hed[u],to[tot]=v,val[tot]=w,hed[u]=tot++;
	nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
}
void build(){
	q[h=t=1]=s,memset(dep+1,-1,e<<2),dep[s]=0;
	while(h<=t){
		int u=q[h++];
		for(int i=hed[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==-1)
			dep[to[i]]=dep[u]+1,q[++t]=to[i];
	}
}
int dinic(int u,int lim){
	if(u==e)return lim;
	for(int flow,&i=cur[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
		if(flow=dinic(to[i],std::min(lim,val[i]))){
			val[i]-=flow,val[i^1]+=flow;return flow;
		}
	return 0;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d%d%d",&n,&m,&ss,&ee),s=n+1,e=n+2,memset(hed+1,-1,e<<2);
	for(int u,v,l,r,i=1;i<=m;i++){
		scanf("%d%d%d%d",&u,&v,&l,&r);
		add(u,v,r-l),pre[v]+=l,pre[u]-=l;
	}
	for(int i=1;i<=n;i++){
		if(pre[i]>0)add(s,i,pre[i]);
		if(pre[i]<0)add(i,e,-pre[i]);
	}
	add(ee,ss,INT_MAX);
	while(build(),~dep[e]){
		for(int i=1;i<=e;i++)cur[i]=hed[i];
		while(dinic(s,INT_MAX));
	}
	for(int i=hed[s];~i;i=nxt[i])if(val[i]){puts("please go home to sleep");return 0;}
	flow=val[tot-1],val[tot-1]=val[tot-2]=0;
	for(int u=n+1;u<n+3;u++)for(int i=hed[u];~i;i=nxt[i])val[i]=val[i^1]=0;
	add(s,ss,INT_MAX),add(ee,e,INT_MAX);
	while(build(),~dep[e]){
		for(int i=1;i<=e;i++)cur[i]=hed[i];
		for(int t=0;t=dinic(s,INT_MAX);flow+=t);
	}
	// for(int i=0;i<tot;i+=2)printf("%d %d (%d / %d)\n",to[i^1],to[i],val[i^1],val[i]+val[i^1]);
	printf("%d\n",flow);
}
