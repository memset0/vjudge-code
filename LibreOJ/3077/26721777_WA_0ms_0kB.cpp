#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e4+10,M=2e6+10;
int n,m,tim,dfn[N],low[N];
int tot=2,hed[N],nxt[M],to[M],bridge[M];
std::set<int> G[N];
void tarjan(int u,int f=-1){
	dfn[u]=low[u]=++tim;
	for(int i=hed[u];~i;i=nxt[i]){
		if(i==(f^1))continue;
		int v=to[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=std::min(low[u],low[v]);
			if(dfn[u]<low[v])bridge[i]=bridge[i^1]=1;
		}else{
			low[u]=std::min(low[u],dfn[v]);
		}
	}
}
int main(){
	memset(hed,-1,sizeof(hed));
	read(n),read(m);
	for(int u,v,i=1;i<=n;i++){
		read(u),read(v);
		nxt[tot]=hed[u],to[tot]=v,hed[u]=tot++;
		nxt[tot]=hed[v],to[tot]=u,hed[v]=tot++;
	}
	tarjan(1);
	for(int i=1;i<=n;i++){

	}
}