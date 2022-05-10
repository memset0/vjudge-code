#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=2e4+10,M=2e5+10;
int n,m,tim,tot,hed[N],nxt[M],to[M],siz[N],cut[N],dfn[N],low[N];
void tarjan(int u,int rt){
	dfn[u]=low[u]=++tim;int cnt=0;
	for(int i=hed[u],v;v=to[i],~i;i=nxt[i])if(!dfn[v]){
		tarjan(v,rt),low[u]=std::min(low[u],low[v]),++cnt;
		if(u!=rt&&low[v]>=dfn[u])cut[u]=1;
	}else low[u]=std::min(low[u],dfn[v]);
	if(u!=rt&&cnt>1)cut[u]=1;
}
int main(){
	read(n),read(m),memset(hed+1,-1,n<<2);
	for(int u,v,i=1;i<=m;i++){
		read(u),read(v);
		nxt[tot]=hed[u],to[tot]=v,hed[u]=tot++;
		nxt[tot]=hed[v],to[tot]=u,hed[v]=tot++;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,i);
	printf("%d\n",std::accumulate(cut+1,cut+n+1,0));
	for(int i=1;i<=n;i++)if(cut[i])printf("%d\n",i);
}