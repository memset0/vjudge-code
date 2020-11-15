#include<bits/stdc++.h>
const int N=1e3+10,V=2.2e4+10,E=6.8e4+10;
int n,m,k,s,e,h,t,ss,ee,nod,il[N],ir[N];
int tot,q[V],id[E],cur[V],dep[V],hed[V],nxt[E],to[E],val[E];
std::vector<int> ans;
std::map<int,int> pl[N],pr[N];
inline void add(int u,int v,int w,int c=0){
	// printf("add %d %d %d\n",u,v,w);
	nxt[tot]=hed[u],to[tot]=v,val[tot]=w,id[tot]=c,hed[u]=tot++;
	nxt[tot]=hed[v],to[tot]=u,val[tot]=0,id[tot]=c,hed[v]=tot++;
}
void build(){
	q[h=t=1]=s,memset(dep+1,-1,nod<<2),dep[s]=0;
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
	scanf("%d%d%d",&n,&m,&k),memset(hed,-1,sizeof(hed));
	for(int i=1;i<=n;i++)il[i]=++nod;
	for(int i=1;i<=m;i++)ir[i]=++nod;
	for(int i=1,a,b,c;i<=k;i++){
		scanf("%d%d%d",&a,&b,&c);
		if(!pl[a][c])pl[a][c]=++nod,add(il[a],pl[a][c],1);
		if(!pr[b][c])pr[b][c]=++nod,add(pr[b][c],ir[b],1);
		add(pl[a][c],pr[b][c],1,i);
	}
	ss=++nod,ee=++nod,s=++nod,e=++nod,add(ee,ss,INT_MAX);
	for(int i=1;i<=n;i++)add(ss,il[i],INT_MAX),add(s,il[i],1); add(ss,e,n);
	for(int i=1;i<=m;i++)add(ir[i],ee,INT_MAX),add(ir[i],e,1); add(s,ee,m);
	while(build(),~dep[e]){memcpy(cur+1,hed+1,nod<<2);while(dinic(s,INT_MAX));}
	for(int i=hed[s];~i;i=nxt[i])if(val[i])return puts("-1"),0;
	// for(int i=0;i<tot;i+=2)printf("%d %d %d : %d / %d\n",to[i^1],to[i],id[i],val[i^1],val[i]+val[i^1]);
	for(int i=0;i<tot;i+=2)if(val[i^1]&&id[i])ans.push_back(id[i]);
	printf("%lu\n",ans.size());
	for(int x:ans)printf("%d ",x);
}
